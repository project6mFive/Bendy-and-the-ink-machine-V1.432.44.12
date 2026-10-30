#include <windows.h>
#include <stdio.h>

typedef int (*fn_bool)(void);
typedef int (*fn_bool_u32)(unsigned int);
typedef int (*fn_bool_str)(const char*);
typedef int (*fn_getach)(const char*, int*);
typedef void* (*fn_void)(void);

static int failures = 0;

static int exception_filter(EXCEPTION_POINTERS* info)
{
    printf("  !! EXCEPTION code=0x%08lX at %p\n",
        (unsigned long)info->ExceptionRecord->ExceptionCode,
        info->ExceptionRecord->ExceptionAddress);
    CONTEXT* ctx = info->ContextRecord;
    printf("     EIP=%08X ESP=%08X EAX=%08X EBX=%08X ECX=%08X EDX=%08X\n",
        ctx->Eip, ctx->Esp, ctx->Eax, ctx->Ebx, ctx->Ecx, ctx->Edx);
    return EXCEPTION_EXECUTE_HANDLER;
}

static void check(const char* label, int got, int expected)
{
    int ok = (got == expected);
    printf("%-48s got=%-8d expected=%-8d %s\n", label, got, expected, ok ? "OK" : "FAIL");
    if (!ok) {
        failures++;
    }
}

int main(int argc, char** argv)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    char path[MAX_PATH];
    const char* dir = (argc > 1) ? argv[1] : ".";
    sprintf(path, "%s\\CSteamworks.dll", dir);

    HMODULE cs = LoadLibraryExA(path, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
    if (!cs) {
        printf("LoadLibrary failed: %lu\n", GetLastError());
        return 2;
    }
    printf("CSteamworks.dll loaded: %p\n", (void*)cs);

    HMODULE stub = LoadLibraryExA("steam_api.dll", NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
    printf("steam_api.dll loaded: %p (err=%lu)\n", (void*)stub, GetLastError());
    if (!stub) {
        failures++;
    }

    {
        unsigned long base = (unsigned long)cs;
        unsigned long* iat = (unsigned long*)(base + 0x1314c);
        void* ctxinit = (void*)GetProcAddress(stub, "SteamInternal_ContextInit");
        void* createif = (void*)GetProcAddress(stub, "SteamInternal_CreateInterface");
        printf("IAT[0x1314c] = %p | ContextInit=%p | CreateInterface=%p\n",
            (void*)*iat, ctxinit, createif);
    }
    fn_bool Init = (fn_bool)GetProcAddress(cs, "Init");
    fn_bool_u32 Restart = (fn_bool_u32)GetProcAddress(cs, "RestartAppIfNecessary");
    fn_void SteamClient = (fn_void)GetProcAddress(cs, "SteamClient_");
    fn_bool BLoggedOn = (fn_bool)GetProcAddress(cs, "ISteamUser_BLoggedOn");
    fn_bool RequestCurrentStats = (fn_bool)GetProcAddress(cs, "ISteamUserStats_RequestCurrentStats");
    fn_getach GetAchievement = (fn_getach)GetProcAddress(cs, "ISteamUserStats_GetAchievement");
    fn_bool_str SetAchievement = (fn_bool_str)GetProcAddress(cs, "ISteamUserStats_SetAchievement");
    fn_bool_str ClearAchievement = (fn_bool_str)GetProcAddress(cs, "ISteamUserStats_ClearAchievement");
    fn_bool StoreStats = (fn_bool)GetProcAddress(cs, "ISteamUserStats_StoreStats");
    fn_bool_u32 DlcInstalled = (fn_bool_u32)GetProcAddress(cs, "ISteamApps_BIsDlcInstalled");
    fn_bool GetAppID = (fn_bool)GetProcAddress(cs, "ISteamUtils_GetAppID");
    fn_bool RunCallbacks = (fn_bool)GetProcAddress(cs, "RunCallbacks");
    fn_bool Shutdown = (fn_bool)GetProcAddress(cs, "Shutdown");

    check("Init()", Init(), 1);
    check("RestartAppIfNecessary()", Restart(622650), 0);
    check("SteamClient_() != NULL", SteamClient() != NULL, 1);

    /* dump the context object produced by our stub */
    typedef void* (*fn_ctxinit)(const char*, void*);
    fn_ctxinit CtxInit = (fn_ctxinit)GetProcAddress(stub, "SteamInternal_ContextInit");
    void* ctx = CtxInit ? CtxInit("SteamAPI", NULL) : NULL;
    printf("ctx = %p\n", ctx);
    if (ctx) {
        unsigned char* bytes = (unsigned char*)ctx;
        void* slot00 = NULL;
        void* slot04 = NULL;
        void* slot14 = NULL;
        void* slot18 = NULL;
        memcpy(&slot00, bytes + 0x00, sizeof(void*));
        memcpy(&slot04, bytes + 0x04, sizeof(void*));
        memcpy(&slot14, bytes + 0x14, sizeof(void*));
        memcpy(&slot18, bytes + 0x18, sizeof(void*));
        printf("  +0x00 (ISteamClient) = %p\n", slot00);
        printf("  +0x04 (ISteamUser)   = %p\n", slot04);
        printf("  +0x14 (ISteamUserStats) = %p\n", slot14);
        printf("  +0x18 (ISteamApps)   = %p\n", slot18);
        if (slot04) {
            void** holder = (void**)slot04;
            void** arr = (void**)holder[0];
            printf("  arr       = %p  arr[0] = %p  arr[1] = %p\n", (void*)arr, arr[0], arr[1]);
            fn_bool direct = (fn_bool)arr[1];
            printf("  calling arr[1] directly...\n");
            fflush(stdout);
            int r = direct();
            printf("  direct call returned %d\n", r);
        }
    }

    printf("calling ISteamUser_BLoggedOn through shim...\n");
    fflush(stdout);
    __try {
        check("ISteamUser_BLoggedOn()", BLoggedOn(), 0);
    } __except (exception_filter(GetExceptionInformation())) {
        printf("  !! BLoggedOn call trapped\n");
        failures++;
    }
    check("ISteamUserStats_RequestCurrentStats()", RequestCurrentStats(), 0);

    int achieved = 1;
    check("ISteamUserStats_GetAchievement() rc", GetAchievement("TEST_ACHIEVEMENT", &achieved), 0);
    check("ISteamUserStats_GetAchievement() flag", achieved, 0);

    check("ISteamUserStats_SetAchievement()", SetAchievement("TEST_ACHIEVEMENT"), 0);
    check("ISteamUserStats_ClearAchievement()", ClearAchievement("TEST_ACHIEVEMENT"), 0);
    check("ISteamUserStats_StoreStats()", StoreStats(), 0);
    check("ISteamApps_BIsDlcInstalled()", DlcInstalled(622650), 1);
    check("ISteamUtils_GetAppID()", GetAppID(), 622650);
    RunCallbacks();
    printf("%-48s %s\n", "RunCallbacks() (no crash)", "OK");
    Shutdown();
    printf("%-48s %s\n", "Shutdown() (no crash)", "OK");

    printf("\n%s\n", failures ? "FAILURES PRESENT" : "ALL CHECKS PASSED");
    return failures ? 1 : 0;
}
