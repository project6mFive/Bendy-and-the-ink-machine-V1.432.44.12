/*
 * steam_api.dll - clean offline stub for Bendy and the Dark Revival
 *
 * Replaces the unsigned, custom-packed ALI213 'Steam emulator' crack that shipped
 * with the game. The original DLL was packed with encrypted sections, imported
 * WS2_32/WINHTTP/ADVAPI32(RegSetValueEx)/PSAPI and carried registry/persistence
 * and network capability - i.e. it was the malware carrier in the release.
 *
 * This stub implements only the small ABI surface that CSteamworks.dll (the
 * legitimate Valve Steamworks.NET shim) actually calls, returns benign values,
 * performs no network I/O, no registry writes and no file writes.
 */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string.h>

typedef void (*fn_t)(void);

/* generic __stdcall stubs: each pops exactly its own argument count */
static int __stdcall stub0(void)
{
    return 0;
}

static int __stdcall stub1(void* a0)
{
    (void)a0;
    return 0;
}

static int __stdcall stub2(void* a0, void* a1)
{
    (void)a0;
    (void)a1;
    return 0;
}

static int __stdcall stub3(void* a0, void* a1, void* a2)
{
    (void)a0;
    (void)a1;
    (void)a2;
    return 0;
}

static int __stdcall stub4(void* a0, void* a1, void* a2, void* a3)
{
    (void)a0;
    (void)a1;
    (void)a2;
    (void)a3;
    return 0;
}

static int __stdcall stub5(void* a0, void* a1, void* a2, void* a3, void* a4)
{
    (void)a0;
    (void)a1;
    (void)a2;
    (void)a3;
    (void)a4;
    return 0;
}

static int __stdcall stub6(void* a0, void* a1, void* a2, void* a3, void* a4, void* a5)
{
    (void)a0;
    (void)a1;
    (void)a2;
    (void)a3;
    (void)a4;
    (void)a5;
    return 0;
}

static int __stdcall stub7(void* a0, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6)
{
    (void)a0;
    (void)a1;
    (void)a2;
    (void)a3;
    (void)a4;
    (void)a5;
    (void)a6;
    return 0;
}

static int __stdcall stub8(void* a0, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7)
{
    (void)a0;
    (void)a1;
    (void)a2;
    (void)a3;
    (void)a4;
    (void)a5;
    (void)a6;
    (void)a7;
    return 0;
}

static int __stdcall stub9(void* a0, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8)
{
    (void)a0;
    (void)a1;
    (void)a2;
    (void)a3;
    (void)a4;
    (void)a5;
    (void)a6;
    (void)a7;
    (void)a8;
    return 0;
}

/* --- behaviour the game actually observes ------------------------------- */
static int __stdcall fn_getachievement(const char* name, int* achieved)
{
    (void)name;
    if (achieved != NULL) {
        *achieved = 0;
    }
    return 0;
}

static int __stdcall fn_dlcinstalled(int appid)
{
    (void)appid;
    return 1;
}

static int __stdcall fn_getappid(void)
{
    return 622650;
}

static fn_t vtbl_00[36] = {
    (fn_t)stub0 /* ISteamClient_CreateSteamPipe */,
    (fn_t)stub1 /* ISteamClient_BReleaseSteamPipe */,
    (fn_t)stub1 /* ISteamClient_ConnectToGlobalUser */,
    (fn_t)stub2 /* ISteamClient_CreateLocalUser */,
    (fn_t)stub2 /* ISteamClient_ReleaseUser */,
    (fn_t)stub3 /* ISteamClient_GetISteamUser */,
    (fn_t)stub3 /* ISteamClient_GetISteamGameServer */,
    (fn_t)stub2 /* ISteamClient_SetLocalIPBinding */,
    (fn_t)stub3 /* ISteamClient_GetISteamFriends */,
    (fn_t)stub2 /* ISteamClient_GetISteamUtils */,
    (fn_t)stub3 /* ISteamClient_GetISteamMatchmaking */,
    (fn_t)stub3 /* ISteamClient_GetISteamMatchmakingServers */,
    (fn_t)stub3 /* ISteamClient_GetISteamGenericInterface */,
    (fn_t)stub3 /* ISteamClient_GetISteamUserStats */,
    (fn_t)stub3 /* ISteamClient_GetISteamGameServerStats */,
    (fn_t)stub3 /* ISteamClient_GetISteamApps */,
    (fn_t)stub3 /* ISteamClient_GetISteamNetworking */,
    (fn_t)stub3 /* ISteamClient_GetISteamRemoteStorage */,
    (fn_t)stub3 /* ISteamClient_GetISteamScreenshots */,
    (fn_t)stub0 /* unused */,
    (fn_t)stub0 /* ISteamClient_GetIPCCallCount */,
    (fn_t)stub1 /* ISteamClient_SetWarningMessageHook */,
    (fn_t)stub0 /* ISteamClient_BShutdownIfAllPipesClosed */,
    (fn_t)stub3 /* ISteamClient_GetISteamHTTP */,
    (fn_t)stub3 /* ISteamClient_GetISteamUnifiedMessages */,
    (fn_t)stub3 /* ISteamClient_GetISteamController */,
    (fn_t)stub3 /* ISteamClient_GetISteamUGC */,
    (fn_t)stub3 /* ISteamClient_GetISteamAppList */,
    (fn_t)stub3 /* ISteamClient_GetISteamMusic */,
    (fn_t)stub3 /* ISteamClient_GetISteamMusicRemote */,
    (fn_t)stub3 /* ISteamClient_GetISteamHTMLSurface */,
    (fn_t)stub0 /* unused */,
    (fn_t)stub0 /* unused */,
    (fn_t)stub0 /* unused */,
    (fn_t)stub3 /* ISteamClient_GetISteamInventory */,
    (fn_t)stub3 /* ISteamClient_GetISteamVideo */
};
static fn_t* p_vtbl_00 = vtbl_00;

static fn_t vtbl_04[29] = {
    (fn_t)stub0 /* ISteamUser_GetHSteamUser */,
    (fn_t)stub0 /* ISteamUser_BLoggedOn */,
    (fn_t)stub1 /* ISteamUser_GetSteamID */,
    (fn_t)stub7 /* ISteamUser_InitiateGameConnection */,
    (fn_t)stub2 /* ISteamUser_TerminateGameConnection */,
    (fn_t)stub4 /* ISteamUser_TrackAppUsageEvent */,
    (fn_t)stub2 /* ISteamUser_GetUserDataFolder */,
    (fn_t)stub0 /* ISteamUser_StartVoiceRecording */,
    (fn_t)stub0 /* ISteamUser_StopVoiceRecording */,
    (fn_t)stub3 /* ISteamUser_GetAvailableVoice */,
    (fn_t)stub9 /* ISteamUser_GetVoice */,
    (fn_t)stub6 /* ISteamUser_DecompressVoice */,
    (fn_t)stub0 /* ISteamUser_GetVoiceOptimalSampleRate */,
    (fn_t)stub3 /* ISteamUser_GetAuthSessionTicket */,
    (fn_t)stub4 /* ISteamUser_BeginAuthSession */,
    (fn_t)stub2 /* ISteamUser_EndAuthSession */,
    (fn_t)stub1 /* ISteamUser_CancelAuthTicket */,
    (fn_t)stub3 /* ISteamUser_UserHasLicenseForApp */,
    (fn_t)stub0 /* ISteamUser_BIsBehindNAT */,
    (fn_t)stub4 /* ISteamUser_AdvertiseGame */,
    (fn_t)stub2 /* ISteamUser_RequestEncryptedAppTicket */,
    (fn_t)stub3 /* ISteamUser_GetEncryptedAppTicket */,
    (fn_t)stub2 /* ISteamUser_GetGameBadgeLevel */,
    (fn_t)stub0 /* ISteamUser_GetPlayerSteamLevel */,
    (fn_t)stub1 /* ISteamUser_RequestStoreAuthURL */,
    (fn_t)stub0 /* ISteamUser_BIsPhoneVerified */,
    (fn_t)stub0 /* ISteamUser_BIsTwoFactorEnabled */,
    (fn_t)stub0 /* ISteamUser_BIsPhoneIdentifying */,
    (fn_t)stub0 /* ISteamUser_BIsPhoneRequiringVerification */
};
static fn_t* p_vtbl_04 = vtbl_04;

static fn_t vtbl_08[70] = {
    (fn_t)stub0 /* ISteamFriends_GetPersonaName */,
    (fn_t)stub1 /* ISteamFriends_SetPersonaName */,
    (fn_t)stub0 /* ISteamFriends_GetPersonaState */,
    (fn_t)stub1 /* ISteamFriends_GetFriendCount */,
    (fn_t)stub3 /* ISteamFriends_GetFriendByIndex */,
    (fn_t)stub2 /* ISteamFriends_GetFriendRelationship */,
    (fn_t)stub2 /* ISteamFriends_GetFriendPersonaState */,
    (fn_t)stub2 /* ISteamFriends_GetFriendPersonaName */,
    (fn_t)stub3 /* ISteamFriends_GetFriendGamePlayed */,
    (fn_t)stub3 /* ISteamFriends_GetFriendPersonaNameHistory */,
    (fn_t)stub2 /* ISteamFriends_GetFriendSteamLevel */,
    (fn_t)stub2 /* ISteamFriends_GetPlayerNickname */,
    (fn_t)stub0 /* ISteamFriends_GetFriendsGroupCount */,
    (fn_t)stub1 /* ISteamFriends_GetFriendsGroupIDByIndex */,
    (fn_t)stub1 /* ISteamFriends_GetFriendsGroupName */,
    (fn_t)stub1 /* ISteamFriends_GetFriendsGroupMembersCount */,
    (fn_t)stub3 /* ISteamFriends_GetFriendsGroupMembersList */,
    (fn_t)stub3 /* ISteamFriends_HasFriend */,
    (fn_t)stub0 /* ISteamFriends_GetClanCount */,
    (fn_t)stub2 /* ISteamFriends_GetClanByIndex */,
    (fn_t)stub2 /* ISteamFriends_GetClanName */,
    (fn_t)stub2 /* ISteamFriends_GetClanTag */,
    (fn_t)stub5 /* ISteamFriends_GetClanActivityCounts */,
    (fn_t)stub2 /* ISteamFriends_DownloadClanActivityCounts */,
    (fn_t)stub2 /* ISteamFriends_GetFriendCountFromSource */,
    (fn_t)stub4 /* ISteamFriends_GetFriendFromSourceByIndex */,
    (fn_t)stub4 /* ISteamFriends_IsUserInSource */,
    (fn_t)stub3 /* ISteamFriends_SetInGameVoiceSpeaking */,
    (fn_t)stub1 /* ISteamFriends_ActivateGameOverlay */,
    (fn_t)stub3 /* ISteamFriends_ActivateGameOverlayToUser */,
    (fn_t)stub1 /* ISteamFriends_ActivateGameOverlayToWebPage */,
    (fn_t)stub2 /* ISteamFriends_ActivateGameOverlayToStore */,
    (fn_t)stub2 /* ISteamFriends_SetPlayedWith */,
    (fn_t)stub2 /* ISteamFriends_ActivateGameOverlayInviteDialog */,
    (fn_t)stub2 /* ISteamFriends_GetSmallFriendAvatar */,
    (fn_t)stub2 /* ISteamFriends_GetMediumFriendAvatar */,
    (fn_t)stub2 /* ISteamFriends_GetLargeFriendAvatar */,
    (fn_t)stub3 /* ISteamFriends_RequestUserInformation */,
    (fn_t)stub2 /* ISteamFriends_RequestClanOfficerList */,
    (fn_t)stub3 /* ISteamFriends_GetClanOwner */,
    (fn_t)stub2 /* ISteamFriends_GetClanOfficerCount */,
    (fn_t)stub4 /* ISteamFriends_GetClanOfficerByIndex */,
    (fn_t)stub0 /* ISteamFriends_GetUserRestrictions */,
    (fn_t)stub2 /* ISteamFriends_SetRichPresence */,
    (fn_t)stub0 /* ISteamFriends_ClearRichPresence */,
    (fn_t)stub3 /* ISteamFriends_GetFriendRichPresence */,
    (fn_t)stub2 /* ISteamFriends_GetFriendRichPresenceKeyCount */,
    (fn_t)stub3 /* ISteamFriends_GetFriendRichPresenceKeyByIndex */,
    (fn_t)stub2 /* ISteamFriends_RequestFriendRichPresence */,
    (fn_t)stub3 /* ISteamFriends_InviteUserToGame */,
    (fn_t)stub0 /* ISteamFriends_GetCoplayFriendCount */,
    (fn_t)stub2 /* ISteamFriends_GetCoplayFriend */,
    (fn_t)stub2 /* ISteamFriends_GetFriendCoplayTime */,
    (fn_t)stub2 /* ISteamFriends_GetFriendCoplayGame */,
    (fn_t)stub2 /* ISteamFriends_JoinClanChatRoom */,
    (fn_t)stub2 /* ISteamFriends_LeaveClanChatRoom */,
    (fn_t)stub2 /* ISteamFriends_GetClanChatMemberCount */,
    (fn_t)stub4 /* ISteamFriends_GetChatMemberByIndex */,
    (fn_t)stub3 /* ISteamFriends_SendClanChatMessage */,
    (fn_t)stub7 /* ISteamFriends_GetClanChatMessage */,
    (fn_t)stub4 /* ISteamFriends_IsClanChatAdmin */,
    (fn_t)stub2 /* ISteamFriends_IsClanChatWindowOpenInSteam */,
    (fn_t)stub2 /* ISteamFriends_OpenClanChatWindowInSteam */,
    (fn_t)stub2 /* ISteamFriends_CloseClanChatWindowInSteam */,
    (fn_t)stub1 /* ISteamFriends_SetListenForFriendsMessages */,
    (fn_t)stub3 /* ISteamFriends_ReplyToFriendMessage */,
    (fn_t)stub6 /* ISteamFriends_GetFriendMessage */,
    (fn_t)stub2 /* ISteamFriends_GetFollowerCount */,
    (fn_t)stub2 /* ISteamFriends_IsFollowing */,
    (fn_t)stub1 /* ISteamFriends_EnumerateFollowingList */
};
static fn_t* p_vtbl_08 = vtbl_08;

static fn_t vtbl_0c[28] = {
    (fn_t)stub0 /* ISteamUtils_GetSecondsSinceAppActive */,
    (fn_t)stub0 /* ISteamUtils_GetSecondsSinceComputerActive */,
    (fn_t)stub0 /* ISteamUtils_GetConnectedUniverse */,
    (fn_t)stub0 /* ISteamUtils_GetServerRealTime */,
    (fn_t)stub0 /* ISteamUtils_GetIPCountry */,
    (fn_t)stub3 /* ISteamUtils_GetImageSize */,
    (fn_t)stub3 /* ISteamUtils_GetImageRGBA */,
    (fn_t)stub2 /* ISteamUtils_GetCSERIPPort */,
    (fn_t)stub0 /* ISteamUtils_GetCurrentBatteryPower */,
    (fn_t)fn_getappid /* ISteamUtils_GetAppID */,
    (fn_t)stub1 /* ISteamUtils_SetOverlayNotificationPosition */,
    (fn_t)stub3 /* ISteamUtils_IsAPICallCompleted */,
    (fn_t)stub2 /* ISteamUtils_GetAPICallFailureReason */,
    (fn_t)stub6 /* ISteamUtils_GetAPICallResult */,
    (fn_t)stub0 /* unused */,
    (fn_t)stub0 /* ISteamUtils_GetIPCCallCount */,
    (fn_t)stub1 /* ISteamUtils_SetWarningMessageHook */,
    (fn_t)stub0 /* ISteamUtils_IsOverlayEnabled */,
    (fn_t)stub0 /* ISteamUtils_BOverlayNeedsPresent */,
    (fn_t)stub1 /* ISteamUtils_CheckFileSignature */,
    (fn_t)stub5 /* ISteamUtils_ShowGamepadTextInput */,
    (fn_t)stub0 /* ISteamUtils_GetEnteredGamepadTextLength */,
    (fn_t)stub2 /* ISteamUtils_GetEnteredGamepadTextInput */,
    (fn_t)stub0 /* ISteamUtils_GetSteamUILanguage */,
    (fn_t)stub0 /* ISteamUtils_IsSteamRunningInVR */,
    (fn_t)stub2 /* ISteamUtils_SetOverlayNotificationInset */,
    (fn_t)stub0 /* ISteamUtils_IsSteamInBigPictureMode */,
    (fn_t)stub0 /* ISteamUtils_StartVRDashboard */
};
static fn_t* p_vtbl_0c = vtbl_0c;

static fn_t vtbl_10[38] = {
    (fn_t)stub0 /* ISteamMatchmaking_GetFavoriteGameCount */,
    (fn_t)stub7 /* ISteamMatchmaking_GetFavoriteGame */,
    (fn_t)stub6 /* ISteamMatchmaking_AddFavoriteGame */,
    (fn_t)stub5 /* ISteamMatchmaking_RemoveFavoriteGame */,
    (fn_t)stub0 /* ISteamMatchmaking_RequestLobbyList */,
    (fn_t)stub3 /* ISteamMatchmaking_AddRequestLobbyListStringFilter */,
    (fn_t)stub3 /* ISteamMatchmaking_AddRequestLobbyListNumericalFilter */,
    (fn_t)stub2 /* ISteamMatchmaking_AddRequestLobbyListNearValueFilter */,
    (fn_t)stub1 /* ISteamMatchmaking_AddRequestLobbyListFilterSlotsAvailable */,
    (fn_t)stub1 /* ISteamMatchmaking_AddRequestLobbyListDistanceFilter */,
    (fn_t)stub1 /* ISteamMatchmaking_AddRequestLobbyListResultCountFilter */,
    (fn_t)stub2 /* ISteamMatchmaking_AddRequestLobbyListCompatibleMembersFilter */,
    (fn_t)stub2 /* ISteamMatchmaking_GetLobbyByIndex */,
    (fn_t)stub2 /* ISteamMatchmaking_CreateLobby */,
    (fn_t)stub2 /* ISteamMatchmaking_JoinLobby */,
    (fn_t)stub2 /* ISteamMatchmaking_LeaveLobby */,
    (fn_t)stub4 /* ISteamMatchmaking_InviteUserToLobby */,
    (fn_t)stub2 /* ISteamMatchmaking_GetNumLobbyMembers */,
    (fn_t)stub4 /* ISteamMatchmaking_GetLobbyMemberByIndex */,
    (fn_t)stub3 /* ISteamMatchmaking_GetLobbyData */,
    (fn_t)stub4 /* ISteamMatchmaking_SetLobbyData */,
    (fn_t)stub2 /* ISteamMatchmaking_GetLobbyDataCount */,
    (fn_t)stub7 /* ISteamMatchmaking_GetLobbyDataByIndex */,
    (fn_t)stub3 /* ISteamMatchmaking_DeleteLobbyData */,
    (fn_t)stub5 /* ISteamMatchmaking_GetLobbyMemberData */,
    (fn_t)stub4 /* ISteamMatchmaking_SetLobbyMemberData */,
    (fn_t)stub4 /* ISteamMatchmaking_SendLobbyChatMsg */,
    (fn_t)stub7 /* ISteamMatchmaking_GetLobbyChatEntry */,
    (fn_t)stub2 /* ISteamMatchmaking_RequestLobbyData */,
    (fn_t)stub6 /* ISteamMatchmaking_SetLobbyGameServer */,
    (fn_t)stub5 /* ISteamMatchmaking_GetLobbyGameServer */,
    (fn_t)stub3 /* ISteamMatchmaking_SetLobbyMemberLimit */,
    (fn_t)stub2 /* ISteamMatchmaking_GetLobbyMemberLimit */,
    (fn_t)stub3 /* ISteamMatchmaking_SetLobbyType */,
    (fn_t)stub3 /* ISteamMatchmaking_SetLobbyJoinable */,
    (fn_t)stub3 /* ISteamMatchmaking_GetLobbyOwner */,
    (fn_t)stub4 /* ISteamMatchmaking_SetLobbyOwner */,
    (fn_t)stub4 /* ISteamMatchmaking_SetLinkedLobby */
};
static fn_t* p_vtbl_10 = vtbl_10;

static fn_t vtbl_14[43] = {
    (fn_t)stub0 /* ISteamUserStats_RequestCurrentStats */,
    (fn_t)stub2 /* ISteamUserStats_GetStat_ */,
    (fn_t)stub2 /* ISteamUserStats_GetStat */,
    (fn_t)stub1 /* ISteamUserStats_SetStat_ */,
    (fn_t)stub2 /* ISteamUserStats_SetStat */,
    (fn_t)stub1 /* ISteamUserStats_UpdateAvgRateStat */,
    (fn_t)fn_getachievement /* ISteamUserStats_GetAchievement */,
    (fn_t)stub1 /* ISteamUserStats_SetAchievement */,
    (fn_t)stub1 /* ISteamUserStats_ClearAchievement */,
    (fn_t)stub3 /* ISteamUserStats_GetAchievementAndUnlockTime */,
    (fn_t)stub0 /* ISteamUserStats_StoreStats */,
    (fn_t)stub1 /* ISteamUserStats_GetAchievementIcon */,
    (fn_t)stub2 /* ISteamUserStats_GetAchievementDisplayAttribute */,
    (fn_t)stub3 /* ISteamUserStats_IndicateAchievementProgress */,
    (fn_t)stub0 /* ISteamUserStats_GetNumAchievements */,
    (fn_t)stub1 /* ISteamUserStats_GetAchievementName */,
    (fn_t)stub2 /* ISteamUserStats_RequestUserStats */,
    (fn_t)stub4 /* ISteamUserStats_GetUserStat_ */,
    (fn_t)stub4 /* ISteamUserStats_GetUserStat */,
    (fn_t)stub4 /* ISteamUserStats_GetUserAchievement */,
    (fn_t)stub5 /* ISteamUserStats_GetUserAchievementAndUnlockTime */,
    (fn_t)stub1 /* ISteamUserStats_ResetAllStats */,
    (fn_t)stub3 /* ISteamUserStats_FindOrCreateLeaderboard */,
    (fn_t)stub1 /* ISteamUserStats_FindLeaderboard */,
    (fn_t)stub2 /* ISteamUserStats_GetLeaderboardName */,
    (fn_t)stub2 /* ISteamUserStats_GetLeaderboardEntryCount */,
    (fn_t)stub2 /* ISteamUserStats_GetLeaderboardSortMethod */,
    (fn_t)stub2 /* ISteamUserStats_GetLeaderboardDisplayType */,
    (fn_t)stub5 /* ISteamUserStats_DownloadLeaderboardEntries */,
    (fn_t)stub4 /* ISteamUserStats_DownloadLeaderboardEntriesForUsers */,
    (fn_t)stub6 /* ISteamUserStats_GetDownloadedLeaderboardEntry */,
    (fn_t)stub6 /* ISteamUserStats_UploadLeaderboardScore */,
    (fn_t)stub4 /* ISteamUserStats_AttachLeaderboardUGC */,
    (fn_t)stub0 /* ISteamUserStats_GetNumberOfCurrentPlayers */,
    (fn_t)stub0 /* ISteamUserStats_RequestGlobalAchievementPercentages */,
    (fn_t)stub4 /* ISteamUserStats_GetMostAchievedAchievementInfo */,
    (fn_t)stub5 /* ISteamUserStats_GetNextMostAchievedAchievementInfo */,
    (fn_t)stub2 /* ISteamUserStats_GetAchievementAchievedPercent */,
    (fn_t)stub1 /* ISteamUserStats_RequestGlobalStats */,
    (fn_t)stub2 /* ISteamUserStats_GetGlobalStat_ */,
    (fn_t)stub2 /* ISteamUserStats_GetGlobalStat */,
    (fn_t)stub3 /* ISteamUserStats_GetGlobalStatHistory_ */,
    (fn_t)stub3 /* ISteamUserStats_GetGlobalStatHistory */
};
static fn_t* p_vtbl_14 = vtbl_14;

static fn_t vtbl_18[26] = {
    (fn_t)stub0 /* ISteamApps_BIsSubscribed */,
    (fn_t)stub0 /* ISteamApps_BIsLowViolence */,
    (fn_t)stub0 /* ISteamApps_BIsCybercafe */,
    (fn_t)stub0 /* ISteamApps_BIsVACBanned */,
    (fn_t)stub0 /* ISteamApps_GetCurrentGameLanguage */,
    (fn_t)stub0 /* ISteamApps_GetAvailableGameLanguages */,
    (fn_t)stub1 /* ISteamApps_BIsSubscribedApp */,
    (fn_t)fn_dlcinstalled /* ISteamApps_BIsDlcInstalled */,
    (fn_t)stub1 /* ISteamApps_GetEarliestPurchaseUnixTime */,
    (fn_t)stub0 /* ISteamApps_BIsSubscribedFromFreeWeekend */,
    (fn_t)stub0 /* ISteamApps_GetDLCCount */,
    (fn_t)stub5 /* ISteamApps_BGetDLCDataByIndex */,
    (fn_t)stub1 /* ISteamApps_InstallDLC */,
    (fn_t)stub1 /* ISteamApps_UninstallDLC */,
    (fn_t)stub1 /* ISteamApps_RequestAppProofOfPurchaseKey */,
    (fn_t)stub2 /* ISteamApps_GetCurrentBetaName */,
    (fn_t)stub1 /* ISteamApps_MarkContentCorrupt */,
    (fn_t)stub3 /* ISteamApps_GetInstalledDepots */,
    (fn_t)stub3 /* ISteamApps_GetAppInstallDir */,
    (fn_t)stub1 /* ISteamApps_BIsAppInstalled */,
    (fn_t)stub1 /* ISteamApps_GetAppOwner */,
    (fn_t)stub1 /* ISteamApps_GetLaunchQueryParam */,
    (fn_t)stub3 /* ISteamApps_GetDlcDownloadProgress */,
    (fn_t)stub0 /* ISteamApps_GetAppBuildId */,
    (fn_t)stub0 /* ISteamApps_RequestAllProofOfPurchaseKeys */,
    (fn_t)stub1 /* ISteamApps_GetFileDetails */
};
static fn_t* p_vtbl_18 = vtbl_18;

static fn_t vtbl_1c[17] = {
    (fn_t)stub4 /* ISteamMatchmakingServers_RequestInternetServerList */,
    (fn_t)stub2 /* ISteamMatchmakingServers_RequestLANServerList */,
    (fn_t)stub4 /* ISteamMatchmakingServers_RequestFriendsServerList */,
    (fn_t)stub4 /* ISteamMatchmakingServers_RequestFavoritesServerList */,
    (fn_t)stub4 /* ISteamMatchmakingServers_RequestHistoryServerList */,
    (fn_t)stub4 /* ISteamMatchmakingServers_RequestSpectatorServerList */,
    (fn_t)stub1 /* ISteamMatchmakingServers_ReleaseRequest */,
    (fn_t)stub2 /* ISteamMatchmakingServers_GetServerDetails */,
    (fn_t)stub1 /* ISteamMatchmakingServers_CancelQuery */,
    (fn_t)stub1 /* ISteamMatchmakingServers_RefreshQuery */,
    (fn_t)stub1 /* ISteamMatchmakingServers_IsRefreshing */,
    (fn_t)stub1 /* ISteamMatchmakingServers_GetServerCount */,
    (fn_t)stub2 /* ISteamMatchmakingServers_RefreshServer */,
    (fn_t)stub3 /* ISteamMatchmakingServers_PingServer */,
    (fn_t)stub3 /* ISteamMatchmakingServers_PlayerDetails */,
    (fn_t)stub3 /* ISteamMatchmakingServers_ServerRules */,
    (fn_t)stub1 /* ISteamMatchmakingServers_CancelServerQuery */
};
static fn_t* p_vtbl_1c = vtbl_1c;

static fn_t vtbl_20[22] = {
    (fn_t)stub6 /* ISteamNetworking_SendP2PPacket */,
    (fn_t)stub2 /* ISteamNetworking_IsP2PPacketAvailable */,
    (fn_t)stub5 /* ISteamNetworking_ReadP2PPacket */,
    (fn_t)stub2 /* ISteamNetworking_AcceptP2PSessionWithUser */,
    (fn_t)stub2 /* ISteamNetworking_CloseP2PSessionWithUser */,
    (fn_t)stub3 /* ISteamNetworking_CloseP2PChannelWithUser */,
    (fn_t)stub3 /* ISteamNetworking_GetP2PSessionState */,
    (fn_t)stub1 /* ISteamNetworking_AllowP2PPacketRelay */,
    (fn_t)stub4 /* ISteamNetworking_CreateListenSocket */,
    (fn_t)stub5 /* ISteamNetworking_CreateP2PConnectionSocket */,
    (fn_t)stub3 /* ISteamNetworking_CreateConnectionSocket */,
    (fn_t)stub2 /* ISteamNetworking_DestroySocket */,
    (fn_t)stub2 /* ISteamNetworking_DestroyListenSocket */,
    (fn_t)stub4 /* ISteamNetworking_SendDataOnSocket */,
    (fn_t)stub2 /* ISteamNetworking_IsDataAvailableOnSocket */,
    (fn_t)stub4 /* ISteamNetworking_RetrieveDataFromSocket */,
    (fn_t)stub3 /* ISteamNetworking_IsDataAvailable */,
    (fn_t)stub5 /* ISteamNetworking_RetrieveData */,
    (fn_t)stub5 /* ISteamNetworking_GetSocketInfo */,
    (fn_t)stub3 /* ISteamNetworking_GetListenSocketInfo */,
    (fn_t)stub1 /* ISteamNetworking_GetSocketConnectionType */,
    (fn_t)stub1 /* ISteamNetworking_GetMaxPacketSize */
};
static fn_t* p_vtbl_20 = vtbl_20;

static fn_t vtbl_24[55] = {
    (fn_t)stub3 /* ISteamRemoteStorage_FileWrite */,
    (fn_t)stub3 /* ISteamRemoteStorage_FileRead */,
    (fn_t)stub3 /* ISteamRemoteStorage_FileWriteAsync */,
    (fn_t)stub3 /* ISteamRemoteStorage_FileReadAsync */,
    (fn_t)stub4 /* ISteamRemoteStorage_FileReadAsyncComplete */,
    (fn_t)stub1 /* ISteamRemoteStorage_FileForget */,
    (fn_t)stub1 /* ISteamRemoteStorage_FileDelete */,
    (fn_t)stub1 /* ISteamRemoteStorage_FileShare */,
    (fn_t)stub2 /* ISteamRemoteStorage_SetSyncPlatforms */,
    (fn_t)stub1 /* ISteamRemoteStorage_FileWriteStreamOpen */,
    (fn_t)stub4 /* ISteamRemoteStorage_FileWriteStreamWriteChunk */,
    (fn_t)stub2 /* ISteamRemoteStorage_FileWriteStreamClose */,
    (fn_t)stub2 /* ISteamRemoteStorage_FileWriteStreamCancel */,
    (fn_t)stub1 /* ISteamRemoteStorage_FileExists */,
    (fn_t)stub1 /* ISteamRemoteStorage_FilePersisted */,
    (fn_t)stub1 /* ISteamRemoteStorage_GetFileSize */,
    (fn_t)stub1 /* ISteamRemoteStorage_GetFileTimestamp */,
    (fn_t)stub1 /* ISteamRemoteStorage_GetSyncPlatforms */,
    (fn_t)stub0 /* ISteamRemoteStorage_GetFileCount */,
    (fn_t)stub2 /* ISteamRemoteStorage_GetFileNameAndSize */,
    (fn_t)stub2 /* ISteamRemoteStorage_GetQuota */,
    (fn_t)stub0 /* ISteamRemoteStorage_IsCloudEnabledForAccount */,
    (fn_t)stub0 /* ISteamRemoteStorage_IsCloudEnabledForApp */,
    (fn_t)stub1 /* ISteamRemoteStorage_SetCloudEnabledForApp */,
    (fn_t)stub3 /* ISteamRemoteStorage_UGCDownload */,
    (fn_t)stub4 /* ISteamRemoteStorage_GetUGCDownloadProgress */,
    (fn_t)stub6 /* ISteamRemoteStorage_GetUGCDetails */,
    (fn_t)stub6 /* ISteamRemoteStorage_UGCRead */,
    (fn_t)stub0 /* ISteamRemoteStorage_GetCachedUGCCount */,
    (fn_t)stub1 /* ISteamRemoteStorage_GetCachedUGCHandle */,
    (fn_t)stub8 /* ISteamRemoteStorage_PublishWorkshopFile */,
    (fn_t)stub2 /* ISteamRemoteStorage_CreatePublishedFileUpdateRequest */,
    (fn_t)stub3 /* ISteamRemoteStorage_UpdatePublishedFileFile */,
    (fn_t)stub3 /* ISteamRemoteStorage_UpdatePublishedFilePreviewFile */,
    (fn_t)stub3 /* ISteamRemoteStorage_UpdatePublishedFileTitle */,
    (fn_t)stub3 /* ISteamRemoteStorage_UpdatePublishedFileDescription */,
    (fn_t)stub3 /* ISteamRemoteStorage_UpdatePublishedFileVisibility */,
    (fn_t)stub3 /* ISteamRemoteStorage_UpdatePublishedFileTags */,
    (fn_t)stub2 /* ISteamRemoteStorage_CommitPublishedFileUpdate */,
    (fn_t)stub3 /* ISteamRemoteStorage_GetPublishedFileDetails */,
    (fn_t)stub2 /* ISteamRemoteStorage_DeletePublishedFile */,
    (fn_t)stub1 /* ISteamRemoteStorage_EnumerateUserPublishedFiles */,
    (fn_t)stub2 /* ISteamRemoteStorage_SubscribePublishedFile */,
    (fn_t)stub1 /* ISteamRemoteStorage_EnumerateUserSubscribedFiles */,
    (fn_t)stub2 /* ISteamRemoteStorage_UnsubscribePublishedFile */,
    (fn_t)stub3 /* ISteamRemoteStorage_UpdatePublishedFileSetChangeDescription */,
    (fn_t)stub2 /* ISteamRemoteStorage_GetPublishedItemVoteDetails */,
    (fn_t)stub3 /* ISteamRemoteStorage_UpdateUserPublishedItemVote */,
    (fn_t)stub2 /* ISteamRemoteStorage_GetUserPublishedItemVoteDetails */,
    (fn_t)stub5 /* ISteamRemoteStorage_EnumerateUserSharedWorkshopFiles */,
    (fn_t)stub9 /* ISteamRemoteStorage_PublishVideo */,
    (fn_t)stub3 /* ISteamRemoteStorage_SetUserPublishedFileAction */,
    (fn_t)stub2 /* ISteamRemoteStorage_EnumeratePublishedFilesByUserAction */,
    (fn_t)stub6 /* ISteamRemoteStorage_EnumeratePublishedWorkshopFiles */,
    (fn_t)stub4 /* ISteamRemoteStorage_UGCDownloadToLocation */
};
static fn_t* p_vtbl_24 = vtbl_24;

static fn_t vtbl_28[9] = {
    (fn_t)stub4 /* ISteamScreenshots_WriteScreenshot */,
    (fn_t)stub4 /* ISteamScreenshots_AddScreenshotToLibrary */,
    (fn_t)stub0 /* ISteamScreenshots_TriggerScreenshot */,
    (fn_t)stub1 /* ISteamScreenshots_HookScreenshots */,
    (fn_t)stub2 /* ISteamScreenshots_SetLocation */,
    (fn_t)stub3 /* ISteamScreenshots_TagUser */,
    (fn_t)stub3 /* ISteamScreenshots_TagPublishedFile */,
    (fn_t)stub0 /* ISteamScreenshots_IsScreenshotsHooked */,
    (fn_t)stub3 /* ISteamScreenshots_AddVRScreenshotToLibrary */
};
static fn_t* p_vtbl_28 = vtbl_28;

static fn_t vtbl_2c[25] = {
    (fn_t)stub2 /* ISteamHTTP_CreateHTTPRequest */,
    (fn_t)stub3 /* ISteamHTTP_SetHTTPRequestContextValue */,
    (fn_t)stub2 /* ISteamHTTP_SetHTTPRequestNetworkActivityTimeout */,
    (fn_t)stub3 /* ISteamHTTP_SetHTTPRequestHeaderValue */,
    (fn_t)stub3 /* ISteamHTTP_SetHTTPRequestGetOrPostParameter */,
    (fn_t)stub2 /* ISteamHTTP_SendHTTPRequest */,
    (fn_t)stub2 /* ISteamHTTP_SendHTTPRequestAndStreamResponse */,
    (fn_t)stub1 /* ISteamHTTP_DeferHTTPRequest */,
    (fn_t)stub1 /* ISteamHTTP_PrioritizeHTTPRequest */,
    (fn_t)stub3 /* ISteamHTTP_GetHTTPResponseHeaderSize */,
    (fn_t)stub4 /* ISteamHTTP_GetHTTPResponseHeaderValue */,
    (fn_t)stub2 /* ISteamHTTP_GetHTTPResponseBodySize */,
    (fn_t)stub3 /* ISteamHTTP_GetHTTPResponseBodyData */,
    (fn_t)stub4 /* ISteamHTTP_GetHTTPStreamingResponseBodyData */,
    (fn_t)stub1 /* ISteamHTTP_ReleaseHTTPRequest */,
    (fn_t)stub2 /* ISteamHTTP_GetHTTPDownloadProgressPct */,
    (fn_t)stub4 /* ISteamHTTP_SetHTTPRequestRawPostBody */,
    (fn_t)stub1 /* ISteamHTTP_CreateCookieContainer */,
    (fn_t)stub1 /* ISteamHTTP_ReleaseCookieContainer */,
    (fn_t)stub4 /* ISteamHTTP_SetCookie */,
    (fn_t)stub2 /* ISteamHTTP_SetHTTPRequestCookieContainer */,
    (fn_t)stub2 /* ISteamHTTP_SetHTTPRequestUserAgentInfo */,
    (fn_t)stub2 /* ISteamHTTP_SetHTTPRequestRequiresVerifiedCertificate */,
    (fn_t)stub2 /* ISteamHTTP_SetHTTPRequestAbsoluteTimeoutMS */,
    (fn_t)stub2 /* ISteamHTTP_GetHTTPRequestWasTimedOut */
};
static fn_t* p_vtbl_2c = vtbl_2c;

static fn_t vtbl_30[5] = {
    (fn_t)stub5 /* ISteamUnifiedMessages_SendMethod */,
    (fn_t)stub4 /* ISteamUnifiedMessages_GetMethodResponseInfo */,
    (fn_t)stub5 /* ISteamUnifiedMessages_GetMethodResponseData */,
    (fn_t)stub2 /* ISteamUnifiedMessages_ReleaseMethod */,
    (fn_t)stub3 /* ISteamUnifiedMessages_SendNotification */
};
static fn_t* p_vtbl_30 = vtbl_30;

static fn_t vtbl_34[26] = {
    (fn_t)stub0 /* ISteamController_Init */,
    (fn_t)stub0 /* ISteamController_Shutdown */,
    (fn_t)stub0 /* ISteamController_RunFrame */,
    (fn_t)stub1 /* ISteamController_GetConnectedControllers */,
    (fn_t)stub2 /* ISteamController_ShowBindingPanel */,
    (fn_t)stub1 /* ISteamController_GetActionSetHandle */,
    (fn_t)stub4 /* ISteamController_ActivateActionSet */,
    (fn_t)stub2 /* ISteamController_GetCurrentActionSet */,
    (fn_t)stub1 /* ISteamController_GetDigitalActionHandle */,
    (fn_t)stub5 /* ISteamController_GetDigitalActionData */,
    (fn_t)stub7 /* ISteamController_GetDigitalActionOrigins */,
    (fn_t)stub1 /* ISteamController_GetAnalogActionHandle */,
    (fn_t)stub0 /* unused */,
    (fn_t)stub7 /* ISteamController_GetAnalogActionOrigins */,
    (fn_t)stub4 /* ISteamController_StopAnalogActionMomentum */,
    (fn_t)stub4 /* ISteamController_TriggerHapticPulse */,
    (fn_t)stub7 /* ISteamController_TriggerRepeatedHapticPulse */,
    (fn_t)stub4 /* ISteamController_TriggerVibration */,
    (fn_t)stub6 /* ISteamController_SetLEDColor */,
    (fn_t)stub2 /* ISteamController_GetGamepadIndexForController */,
    (fn_t)stub1 /* ISteamController_GetControllerForGamepadIndex */,
    (fn_t)stub3 /* ISteamController_GetMotionData */,
    (fn_t)stub4 /* ISteamController_ShowDigitalActionOrigins */,
    (fn_t)stub4 /* ISteamController_ShowAnalogActionOrigins */,
    (fn_t)stub1 /* ISteamController_GetStringForActionOrigin */,
    (fn_t)stub1 /* ISteamController_GetGlyphForActionOrigin */
};
static fn_t* p_vtbl_34 = vtbl_34;

static fn_t vtbl_38[67] = {
    (fn_t)stub7 /* ISteamUGC_CreateQueryUserUGCRequest */,
    (fn_t)stub5 /* ISteamUGC_CreateQueryAllUGCRequest */,
    (fn_t)stub2 /* ISteamUGC_CreateQueryUGCDetailsRequest */,
    (fn_t)stub2 /* ISteamUGC_SendQueryUGCRequest */,
    (fn_t)stub4 /* ISteamUGC_GetQueryUGCResult */,
    (fn_t)stub5 /* ISteamUGC_GetQueryUGCPreviewURL */,
    (fn_t)stub5 /* ISteamUGC_GetQueryUGCMetadata */,
    (fn_t)stub5 /* ISteamUGC_GetQueryUGCChildren */,
    (fn_t)stub5 /* ISteamUGC_GetQueryUGCStatistic */,
    (fn_t)stub3 /* ISteamUGC_GetQueryUGCNumAdditionalPreviews */,
    (fn_t)stub9 /* ISteamUGC_GetQueryUGCAdditionalPreview */,
    (fn_t)stub3 /* ISteamUGC_GetQueryUGCNumKeyValueTags */,
    (fn_t)stub8 /* ISteamUGC_GetQueryUGCKeyValueTag */,
    (fn_t)stub2 /* ISteamUGC_ReleaseQueryUGCRequest */,
    (fn_t)stub3 /* ISteamUGC_AddRequiredTag */,
    (fn_t)stub3 /* ISteamUGC_AddExcludedTag */,
    (fn_t)stub3 /* ISteamUGC_SetReturnOnlyIDs */,
    (fn_t)stub3 /* ISteamUGC_SetReturnKeyValueTags */,
    (fn_t)stub3 /* ISteamUGC_SetReturnLongDescription */,
    (fn_t)stub3 /* ISteamUGC_SetReturnMetadata */,
    (fn_t)stub3 /* ISteamUGC_SetReturnChildren */,
    (fn_t)stub3 /* ISteamUGC_SetReturnAdditionalPreviews */,
    (fn_t)stub3 /* ISteamUGC_SetReturnTotalOnly */,
    (fn_t)stub3 /* ISteamUGC_SetLanguage */,
    (fn_t)stub3 /* ISteamUGC_SetAllowCachedResponse */,
    (fn_t)stub3 /* ISteamUGC_SetCloudFileNameFilter */,
    (fn_t)stub3 /* ISteamUGC_SetMatchAnyTag */,
    (fn_t)stub3 /* ISteamUGC_SetSearchText */,
    (fn_t)stub3 /* ISteamUGC_SetRankedByTrendDays */,
    (fn_t)stub4 /* ISteamUGC_AddRequiredKeyValueTag */,
    (fn_t)stub3 /* ISteamUGC_RequestUGCDetails */,
    (fn_t)stub2 /* ISteamUGC_CreateItem */,
    (fn_t)stub3 /* ISteamUGC_StartItemUpdate */,
    (fn_t)stub3 /* ISteamUGC_SetItemTitle */,
    (fn_t)stub3 /* ISteamUGC_SetItemDescription */,
    (fn_t)stub3 /* ISteamUGC_SetItemUpdateLanguage */,
    (fn_t)stub3 /* ISteamUGC_SetItemMetadata */,
    (fn_t)stub3 /* ISteamUGC_SetItemVisibility */,
    (fn_t)stub3 /* ISteamUGC_SetItemTags */,
    (fn_t)stub3 /* ISteamUGC_SetItemContent */,
    (fn_t)stub3 /* ISteamUGC_SetItemPreview */,
    (fn_t)stub3 /* ISteamUGC_RemoveItemKeyValueTags */,
    (fn_t)stub4 /* ISteamUGC_AddItemKeyValueTag */,
    (fn_t)stub4 /* ISteamUGC_AddItemPreviewFile */,
    (fn_t)stub3 /* ISteamUGC_AddItemPreviewVideo */,
    (fn_t)stub4 /* ISteamUGC_UpdateItemPreviewFile */,
    (fn_t)stub4 /* ISteamUGC_UpdateItemPreviewVideo */,
    (fn_t)stub3 /* ISteamUGC_RemoveItemPreview */,
    (fn_t)stub3 /* ISteamUGC_SubmitItemUpdate */,
    (fn_t)stub4 /* ISteamUGC_GetItemUpdateProgress */,
    (fn_t)stub3 /* ISteamUGC_SetUserItemVote */,
    (fn_t)stub2 /* ISteamUGC_GetUserItemVote */,
    (fn_t)stub3 /* ISteamUGC_AddItemToFavorites */,
    (fn_t)stub3 /* ISteamUGC_RemoveItemFromFavorites */,
    (fn_t)stub2 /* ISteamUGC_SubscribeItem */,
    (fn_t)stub2 /* ISteamUGC_UnsubscribeItem */,
    (fn_t)stub0 /* ISteamUGC_GetNumSubscribedItems */,
    (fn_t)stub2 /* ISteamUGC_GetSubscribedItems */,
    (fn_t)stub2 /* ISteamUGC_GetItemState */,
    (fn_t)stub6 /* ISteamUGC_GetItemInstallInfo */,
    (fn_t)stub4 /* ISteamUGC_GetItemDownloadInfo */,
    (fn_t)stub3 /* ISteamUGC_DownloadItem */,
    (fn_t)stub2 /* ISteamUGC_BInitWorkshopForGameServer */,
    (fn_t)stub1 /* ISteamUGC_SuspendDownloads */,
    (fn_t)stub2 /* ISteamUGC_StartPlaytimeTracking */,
    (fn_t)stub2 /* ISteamUGC_StopPlaytimeTracking */,
    (fn_t)stub0 /* ISteamUGC_StopPlaytimeTrackingForAllItems */
};
static fn_t* p_vtbl_38 = vtbl_38;

static fn_t vtbl_3c[5] = {
    (fn_t)stub0 /* ISteamAppList_GetNumInstalledApps */,
    (fn_t)stub2 /* ISteamAppList_GetInstalledApps */,
    (fn_t)stub3 /* ISteamAppList_GetAppName */,
    (fn_t)stub3 /* ISteamAppList_GetAppInstallDir */,
    (fn_t)stub1 /* ISteamAppList_GetAppBuildId */
};
static fn_t* p_vtbl_3c = vtbl_3c;

static fn_t vtbl_40[9] = {
    (fn_t)stub0 /* ISteamMusic_BIsEnabled */,
    (fn_t)stub0 /* ISteamMusic_BIsPlaying */,
    (fn_t)stub0 /* ISteamMusic_GetPlaybackStatus */,
    (fn_t)stub0 /* ISteamMusic_Play */,
    (fn_t)stub0 /* ISteamMusic_Pause */,
    (fn_t)stub0 /* ISteamMusic_PlayPrevious */,
    (fn_t)stub0 /* ISteamMusic_PlayNext */,
    (fn_t)stub0 /* ISteamMusic_SetVolume */,
    (fn_t)stub0 /* ISteamMusic_GetVolume */
};
static fn_t* p_vtbl_40 = vtbl_40;

static fn_t vtbl_44[32] = {
    (fn_t)stub1 /* ISteamMusicRemote_RegisterSteamMusicRemote */,
    (fn_t)stub0 /* ISteamMusicRemote_DeregisterSteamMusicRemote */,
    (fn_t)stub0 /* ISteamMusicRemote_BIsCurrentMusicRemote */,
    (fn_t)stub1 /* ISteamMusicRemote_BActivationSuccess */,
    (fn_t)stub1 /* ISteamMusicRemote_SetDisplayName */,
    (fn_t)stub2 /* ISteamMusicRemote_SetPNGIcon_64x64 */,
    (fn_t)stub1 /* ISteamMusicRemote_EnablePlayPrevious */,
    (fn_t)stub1 /* ISteamMusicRemote_EnablePlayNext */,
    (fn_t)stub1 /* ISteamMusicRemote_EnableShuffled */,
    (fn_t)stub1 /* ISteamMusicRemote_EnableLooped */,
    (fn_t)stub1 /* ISteamMusicRemote_EnableQueue */,
    (fn_t)stub1 /* ISteamMusicRemote_EnablePlaylists */,
    (fn_t)stub1 /* ISteamMusicRemote_UpdatePlaybackStatus */,
    (fn_t)stub1 /* ISteamMusicRemote_UpdateShuffled */,
    (fn_t)stub1 /* ISteamMusicRemote_UpdateLooped */,
    (fn_t)stub0 /* ISteamMusicRemote_UpdateVolume */,
    (fn_t)stub0 /* ISteamMusicRemote_CurrentEntryWillChange */,
    (fn_t)stub1 /* ISteamMusicRemote_CurrentEntryIsAvailable */,
    (fn_t)stub1 /* ISteamMusicRemote_UpdateCurrentEntryText */,
    (fn_t)stub1 /* ISteamMusicRemote_UpdateCurrentEntryElapsedSeconds */,
    (fn_t)stub2 /* ISteamMusicRemote_UpdateCurrentEntryCoverArt */,
    (fn_t)stub0 /* ISteamMusicRemote_CurrentEntryDidChange */,
    (fn_t)stub0 /* ISteamMusicRemote_QueueWillChange */,
    (fn_t)stub0 /* ISteamMusicRemote_ResetQueueEntries */,
    (fn_t)stub3 /* ISteamMusicRemote_SetQueueEntry */,
    (fn_t)stub1 /* ISteamMusicRemote_SetCurrentQueueEntry */,
    (fn_t)stub0 /* ISteamMusicRemote_QueueDidChange */,
    (fn_t)stub0 /* ISteamMusicRemote_PlaylistWillChange */,
    (fn_t)stub0 /* ISteamMusicRemote_ResetPlaylistEntries */,
    (fn_t)stub3 /* ISteamMusicRemote_SetPlaylistEntry */,
    (fn_t)stub1 /* ISteamMusicRemote_SetCurrentPlaylistEntry */,
    (fn_t)stub0 /* ISteamMusicRemote_PlaylistDidChange */
};
static fn_t* p_vtbl_44 = vtbl_44;

static fn_t vtbl_48[36] = {
    (fn_t)stub0 /* unused */,
    (fn_t)stub0 /* ISteamHTMLSurface_Init */,
    (fn_t)stub0 /* ISteamHTMLSurface_Shutdown */,
    (fn_t)stub2 /* ISteamHTMLSurface_CreateBrowser */,
    (fn_t)stub1 /* ISteamHTMLSurface_RemoveBrowser */,
    (fn_t)stub3 /* ISteamHTMLSurface_LoadURL */,
    (fn_t)stub3 /* ISteamHTMLSurface_SetSize */,
    (fn_t)stub1 /* ISteamHTMLSurface_StopLoad */,
    (fn_t)stub1 /* ISteamHTMLSurface_Reload */,
    (fn_t)stub1 /* ISteamHTMLSurface_GoBack */,
    (fn_t)stub1 /* ISteamHTMLSurface_GoForward */,
    (fn_t)stub3 /* ISteamHTMLSurface_AddHeader */,
    (fn_t)stub2 /* ISteamHTMLSurface_ExecuteJavascript */,
    (fn_t)stub2 /* ISteamHTMLSurface_MouseUp */,
    (fn_t)stub2 /* ISteamHTMLSurface_MouseDown */,
    (fn_t)stub2 /* ISteamHTMLSurface_MouseDoubleClick */,
    (fn_t)stub3 /* ISteamHTMLSurface_MouseMove */,
    (fn_t)stub2 /* ISteamHTMLSurface_MouseWheel */,
    (fn_t)stub3 /* ISteamHTMLSurface_KeyDown */,
    (fn_t)stub3 /* ISteamHTMLSurface_KeyUp */,
    (fn_t)stub3 /* ISteamHTMLSurface_KeyChar */,
    (fn_t)stub2 /* ISteamHTMLSurface_SetHorizontalScroll */,
    (fn_t)stub2 /* ISteamHTMLSurface_SetVerticalScroll */,
    (fn_t)stub2 /* ISteamHTMLSurface_SetKeyFocus */,
    (fn_t)stub1 /* ISteamHTMLSurface_ViewSource */,
    (fn_t)stub1 /* ISteamHTMLSurface_CopyToClipboard */,
    (fn_t)stub1 /* ISteamHTMLSurface_PasteFromClipboard */,
    (fn_t)stub4 /* ISteamHTMLSurface_Find */,
    (fn_t)stub1 /* ISteamHTMLSurface_StopFind */,
    (fn_t)stub3 /* ISteamHTMLSurface_GetLinkAtPosition */,
    (fn_t)stub7 /* ISteamHTMLSurface_SetCookie */,
    (fn_t)stub4 /* ISteamHTMLSurface_SetPageScaleFactor */,
    (fn_t)stub2 /* ISteamHTMLSurface_SetBackgroundMode */,
    (fn_t)stub2 /* ISteamHTMLSurface_AllowStartRequest */,
    (fn_t)stub2 /* ISteamHTMLSurface_JSDialogResponse */,
    (fn_t)stub2 /* ISteamHTMLSurface_FileLoadDialogResponse */
};
static fn_t* p_vtbl_48 = vtbl_48;

static fn_t vtbl_4c[24] = {
    (fn_t)stub1 /* ISteamInventory_GetResultStatus */,
    (fn_t)stub3 /* ISteamInventory_GetResultItems */,
    (fn_t)stub1 /* ISteamInventory_GetResultTimestamp */,
    (fn_t)stub3 /* ISteamInventory_CheckResultSteamID */,
    (fn_t)stub1 /* ISteamInventory_DestroyResult */,
    (fn_t)stub1 /* ISteamInventory_GetAllItems */,
    (fn_t)stub3 /* ISteamInventory_GetItemsByID */,
    (fn_t)stub3 /* ISteamInventory_SerializeResult */,
    (fn_t)stub4 /* ISteamInventory_DeserializeResult */,
    (fn_t)stub4 /* ISteamInventory_GenerateItems */,
    (fn_t)stub1 /* ISteamInventory_GrantPromoItems */,
    (fn_t)stub2 /* ISteamInventory_AddPromoItem */,
    (fn_t)stub3 /* ISteamInventory_AddPromoItems */,
    (fn_t)stub4 /* ISteamInventory_ConsumeItem */,
    (fn_t)stub7 /* ISteamInventory_ExchangeItems */,
    (fn_t)stub6 /* ISteamInventory_TransferItemQuantity */,
    (fn_t)stub0 /* ISteamInventory_SendItemDropHeartbeat */,
    (fn_t)stub2 /* ISteamInventory_TriggerItemDrop */,
    (fn_t)stub9 /* ISteamInventory_TradeItems */,
    (fn_t)stub0 /* ISteamInventory_LoadItemDefinitions */,
    (fn_t)stub2 /* ISteamInventory_GetItemDefinitionIDs */,
    (fn_t)stub4 /* ISteamInventory_GetItemDefinitionProperty */,
    (fn_t)stub2 /* ISteamInventory_RequestEligiblePromoItemDefinitionsIDs */,
    (fn_t)stub4 /* ISteamInventory_GetEligiblePromoItemDefinitionIDs */
};
static fn_t* p_vtbl_4c = vtbl_4c;

static fn_t vtbl_50[2] = {
    (fn_t)stub1 /* ISteamVideo_GetVideoURL */,
    (fn_t)stub1 /* ISteamVideo_IsBroadcasting */
};
static fn_t* p_vtbl_50 = vtbl_50;

/* context object: CSteamworks reads interface wrappers from fixed BYTE offsets */
#define CTX_SLOTS 0x60
static unsigned char g_ctx[CTX_SLOTS];
static char g_empty_path[1] = { 0 };
static int g_dummy = 0;

static void ctx_put(unsigned int offset, void* value)
{
    memcpy(g_ctx + offset, &value, sizeof(value));
}

static void BuildContext(void)
{
    unsigned int i;
    for (i = 0; i + sizeof(void*) <= CTX_SLOTS; i += sizeof(void*)) {
        ctx_put(i, (void*)&g_dummy);
    }
    ctx_put(0x00, (void*)&p_vtbl_00);
    ctx_put(0x04, (void*)&p_vtbl_04);
    ctx_put(0x08, (void*)&p_vtbl_08);
    ctx_put(0x0C, (void*)&p_vtbl_0c);
    ctx_put(0x10, (void*)&p_vtbl_10);
    ctx_put(0x14, (void*)&p_vtbl_14);
    ctx_put(0x18, (void*)&p_vtbl_18);
    ctx_put(0x1C, (void*)&p_vtbl_1c);
    ctx_put(0x20, (void*)&p_vtbl_20);
    ctx_put(0x24, (void*)&p_vtbl_24);
    ctx_put(0x28, (void*)&p_vtbl_28);
    ctx_put(0x2C, (void*)&p_vtbl_2c);
    ctx_put(0x30, (void*)&p_vtbl_30);
    ctx_put(0x34, (void*)&p_vtbl_34);
    ctx_put(0x38, (void*)&p_vtbl_38);
    ctx_put(0x3C, (void*)&p_vtbl_3c);
    ctx_put(0x40, (void*)&p_vtbl_40);
    ctx_put(0x44, (void*)&p_vtbl_44);
    ctx_put(0x48, (void*)&p_vtbl_48);
    ctx_put(0x4C, (void*)&p_vtbl_4c);
    ctx_put(0x50, (void*)&p_vtbl_50);
}

BOOL WINAPI DllMain(HINSTANCE inst, DWORD reason, LPVOID reserved)
{
    (void)reserved;
    if (reason == DLL_PROCESS_ATTACH) {
        BuildContext();
    }
    return TRUE;
}

int __cdecl SteamAPI_Init(void)
{
    return 1;
}

void __cdecl SteamAPI_Shutdown(void)
{
}

int __cdecl SteamAPI_RestartAppIfNecessary(unsigned int appId)
{
    (void)appId;
    return 0;
}

void __cdecl SteamAPI_ReleaseCurrentThreadMemory(void)
{
}

void __cdecl SteamAPI_RunCallbacks(void)
{
}

int __cdecl SteamAPI_IsSteamRunning(void)
{
    return 0;
}

const char* __cdecl SteamAPI_GetSteamInstallPath(void)
{
    return g_empty_path;
}

unsigned int __cdecl SteamAPI_GetHSteamPipe(void)
{
    return 0;
}

unsigned int __cdecl SteamAPI_GetHSteamUser(void)
{
    return 0;
}

void __cdecl SteamAPI_SetTryCatchCallbacks(int enabled)
{
    (void)enabled;
}

void __cdecl SteamAPI_RegisterCallback(void* callback, int id)
{
    (void)callback;
    (void)id;
}

void __cdecl SteamAPI_UnregisterCallback(void* callback)
{
    (void)callback;
}

void __cdecl SteamAPI_RegisterCallResult(void* result, unsigned long long call)
{
    (void)result;
    (void)call;
}

void __cdecl SteamAPI_UnregisterCallResult(void* result, unsigned long long call)
{
    (void)result;
    (void)call;
}

int __cdecl SteamAPI_WriteMiniDump(unsigned int code, void* info, unsigned int build)
{
    (void)code;
    (void)info;
    (void)build;
    return 0;
}

void __cdecl SteamAPI_SetMiniDumpComment(const char* comment)
{
    (void)comment;
}

int __cdecl SteamAPI_UseBreakpadCrashHandler(const char* ver, const char* date, const char* time, int full, void* ctx, void* cb)
{
    (void)ver;
    (void)date;
    (void)time;
    (void)full;
    (void)ctx;
    (void)cb;
    return 0;
}

void __cdecl SteamAPI_SetBreakpadAppID(unsigned int appId)
{
    (void)appId;
}

unsigned int __cdecl Steam_GetHSteamUserCurrent(void)
{
    return 0;
}

void __cdecl Steam_RunCallbacks(void)
{
}

int __cdecl Steam_RegisterInterfaceFuncs(void* module)
{
    (void)module;
    return 1;
}

void* __cdecl SteamInternal_CreateInterface(const char* version, const char* iface, void** out)
{
    (void)version;
    (void)iface;
    (void)out;
    return (&g_dummy);
}

void* __cdecl SteamInternal_ContextInit(const char* name, void* callback)
{
    (void)name;
    (void)callback;
    return g_ctx;
}

int __cdecl SteamInternal_GameServer_Init(unsigned int ip, unsigned short port, unsigned short mode, const char* ver)
{
    (void)ip;
    (void)port;
    (void)mode;
    (void)ver;
    return 0;
}

int __cdecl SteamGameServer_Init(unsigned int ip, unsigned short sport, unsigned short gport, unsigned short qport, int mode, const char* ver)
{
    (void)ip;
    (void)sport;
    (void)gport;
    (void)qport;
    (void)mode;
    (void)ver;
    return 0;
}

void __cdecl SteamGameServer_Shutdown(void)
{
}

void __cdecl SteamGameServer_RunCallbacks(void)
{
}

void __cdecl SteamGameServer_ReleaseCurrentThreadMemory(void)
{
}

int __cdecl SteamGameServer_BSecure(void)
{
    return 0;
}

unsigned long long __cdecl SteamGameServer_GetSteamID(void)
{
    return 0;
}

unsigned int __cdecl SteamGameServer_GetHSteamPipe(void)
{
    return 0;
}

unsigned int __cdecl SteamGameServer_GetHSteamUser(void)
{
    return 0;
}
