# Big Globe LeviLamina Port — v0.1.4 build source

> **BUILD SOURCE ONLY. Do not import this ZIP into LeviLauncher.** It deliberately has no `manifest.json` and no DLL. A valid import ZIP is produced only after the Windows workflow builds the DLL and verifies that the generated manifest points to it.

## Target

- Minecraft Bedrock client 1.26.20.4
- LeviLamina 26.20.x
- Windows x64, client DLL
- Reference: Big Globe 6.4.0 for Java/Fabric, Minecraft 26.2

## Build

The xmake setup follows the current official LeviLamina mod template: `levilamina` plus `levibuildscript`, with the `linkrule` and `modpacker` rules. The project targets `client` and Windows x64 using `clang-cl`.

### GitHub Actions (recommended)

1. Create a GitHub repository and add the contents of this folder to its root (include the hidden `.github` folder).
2. Push the files to GitHub.
3. Open **Actions → Build LeviLamina client mod → Run workflow**.
4. Download the artifact `BigGlobe_Port_Client_26.20.x_Windows_x64` from the completed run. **That generated artifact ZIP**, not this source ZIP, is the one to import.

The workflow creates the manifest from `manifest.json.in`, builds the client mod, then fails unless there is exactly one generated manifest under `bin/`, its entry resolves to an existing DLL, and the DLL exports `ll_memory_operator_overrided`, which LeviLamina requires to load a native mod. It packages the verified DLL, manifest, and empty pack folders at the ZIP root.

### Local Windows build

Requires Git, xmake 3.0+, LLVM 22 (`clang-cl`), and Visual Studio 2022 C++ Build Tools with Windows SDK.

```powershell
Copy-Item manifest.json.in manifest.json
xmake repo -u
xmake f -c -y -p windows -a x64 -m release --target_type=client
xmake -v -y
```

Do not import this project folder or source ZIP. Use a build-generated package only after verifying its manifest entry DLL exists.

## Functionality status

This is a native-mod build scaffold, not a Big Globe world-generation port. The mod lifecycle logs load/enable. `noise.cpp` and `terrain.cpp` contain a placeholder procedural height function and are not connected to Bedrock chunk generation. Big Globe-compatible noise, biomes, caves, structures, and in-game worldgen are not implemented. `main.cpp` is a separate CLI preview and is not part of the DLL.

The Java JAR is reference material and is not bundled. It cannot be converted directly into a Bedrock native DLL.

## Verification status

- Source ZIP contents and workflow structure: checked locally.
- Windows DLL build: not run in this environment (xmake, LLVM, Visual Studio C++ Build Tools unavailable).
- GitHub Actions: not run.
- Manifest/DLL import package: not yet produced.
- LeviLauncher and in-game verification: not done.
