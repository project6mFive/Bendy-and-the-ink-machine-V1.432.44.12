import os
import sys

import UnityPy


def dump_build_settings(data_dir):
    path = os.path.join(data_dir, "globalgamemanagers")
    env = UnityPy.load(path)
    print("### Build settings:", data_dir)
    for obj in env.objects:
        if obj.type.name in ("BuildSettings",):
            tree = obj.read_typetree()
            scenes = tree.get("scenes") or tree.get("m_Scenes") or []
            for idx, scene in enumerate(scenes):
                print("   [%d] %s" % (idx, scene))
        elif obj.type.name in ("PlayerSettings",):
            tree = obj.read_typetree()
            print("   productName:", tree.get("productName"), "| company:", tree.get("companyName"), "| version:", tree.get("bundleVersion"))


def dump_bundle(path):
    print("### Bundle:", path, "size:", os.path.getsize(path))
    try:
        env = UnityPy.load(path)
    except Exception as exc:
        print("   load failed:", exc)
        return
    counts = {}
    names = []
    for obj in env.objects:
        counts[obj.type.name] = counts.get(obj.type.name, 0) + 1
        if obj.type.name in ("SceneAsset", "GameObject", "Texture2D", "TextAsset", "MonoBehaviour"):
            try:
                tree = obj.read_typetree()
                name = tree.get("m_Name")
                if name and len(names) < 40:
                    names.append("%s:%s" % (obj.type.name, name))
            except Exception:
                pass
    print("   object counts:", counts)
    for name in names:
        print("     ", name)


def dump_level(path):
    print("### Level:", path, "size:", os.path.getsize(path))
    env = UnityPy.load(path)
    counts = {}
    for obj in env.objects:
        counts[obj.type.name] = counts.get(obj.type.name, 0) + 1
    print("   object counts:", counts)


if __name__ == "__main__":
    mode = sys.argv[1]
    target = sys.argv[2]
    if mode == "build":
        dump_build_settings(target)
    elif mode == "bundle":
        dump_bundle(target)
    elif mode == "level":
        dump_level(target)
    elif mode == "bundles":
        for fname in sorted(os.listdir(target)):
            full = os.path.join(target, fname)
            if os.path.isfile(full) and not fname.endswith(".manifest"):
                dump_bundle(full)
