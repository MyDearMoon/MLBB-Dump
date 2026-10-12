# Mobile Legends: Bang Bang (MLBB) IL2CPP Dump

Extracted types, methods, fields, and symbols from Mobile Legends: Bang Bang (Android ARM64).

Generated using [Il2CppDumper](https://github.com/MyDearMoon/il2cpp-Dumper) with native Moonton Partitioned Metadata support.

---

## Dump Overview

| Metric | Value |
| :--- | :--- |
| **Package ID** | `com.mobile.legends` |
| **Game Version** | `v2.2.16.12322` (Build `211812322`) |
| **Engine / Runtime** | Unity 2019.4.33f1 (Moonton / MLBB HybridCLR) |
| **Target Architecture** | ARM64 (`arm64-v8a`) |
| **Binary Format** | ELF (`libcsharp.so`, `libfirst.so`, `liblogic.so`) |
| **Metadata Version** | v24.3 (Moonton Version 1024 Partitioned) |
| **Assemblies Extracted** | 3 (`Assembly-CSharp.dll`, `Assembly-CSharp-firstpass.dll`, `UnityEngine.CoreModule.dll`) |
| **Total Types** | 28,139 |
| **Total Methods** | 204,374 |
| **Total Fields** | 190,387 |
| **Total String Literals** | 88,303 |
| **Dump Date** | 2026-10-12 |

---

## Repository Contents

| Path | Description |
| :--- | :--- |
| `dump.cs` | Human-readable C# pseudo-code containing class hierarchies, field memory offsets, and method RVAs |
| `script.json` | Symbol table mapping methods, tokens, and signatures for disassemblers |
| `stringliteral.json` | Index of 88,303 string literals extracted across all partitions (with credentials redacted) |
| `dump-manifest.json` | Execution metadata, input file SHA-256 hashes, analysis mode, and exporter results |
| `DummyDll/` | Stripped .NET assemblies (`Assembly-CSharp.dll`, `Assembly-CSharp-firstpass.dll`, `UnityEngine.CoreModule.dll`) for browsing in dnSpy / ILSpy |
| `cpp-sdk/` | C++ headers (`il2cpp.h`, `il2cpp-init.h`, `dllmain.cpp`) with struct layouts and hook scaffolding |
| `ida.py` | One-click symbol loader and function renamer for IDA Pro |
| `ghidra.py` | Automated symbol restoration script for Ghidra |
| `binja.py` | Automated symbol restoration script for Binary Ninja |
| `frida-runtime-dumper/` | Standalone Frida scripts for runtime memory extraction |

---

## Technical Architecture

### Moonton Partitioned Metadata Structure

Mobile Legends: Bang Bang does not use a single monolithic `global-metadata.dat`. Instead, Moonton partitions the metadata tables across three distinct modules:

1. **Partition 1 (`global-metadata.dat`)**:
   - Engine and base framework definitions (`UnityEngine.CoreModule.dll`).
   - 6,063 types, 41,758 methods.
2. **Partition 2 (`global-first-metadata.dat`)**:
   - First-pass plugins and third-party native wrappers (`Assembly-CSharp-firstpass.dll`).
   - 1,701 types, 11,846 methods.
3. **Partition 3 (`global-csharp-metadata.dat`)**:
   P,375 types, 150,770 methods.

### Cross-Partition Token Resolution

References between assemblies encode the target partition index in the upper byte of the token:
- High byte `0x01`: Resolved against Partition 1 string pool.
- High byte `0x02`: Resolved against Partition 2 string pool.
- High byte `0x03`: Resolved against Partition 3 string pool.

Our dumper dynamically links these partitioned tables in-memory to resolve all cross-partition type signatures and method declarations.

---

## How to Inspect & Analyze

### Browsing Assemblies in dnSpy / ILSpy
1. Open [dnSpy](https://github.com/dnSpy/dnSpy) or [ILSpy](https://github.com/icsharpcode/ILSpy).
2. Drag and drop the `DummyDll/` folder into the assembly explorer.
3. Browse `Assembly-CSharp.dll` to view all class hierarchies, namespaces, fields, and method signatures.

### Loading Symbols in IDA Pro / Ghidra
1. Open `libcsharp.so` in IDA Pro or Ghidra.
2. Run `ida.py` (File -> Script file in IDA) or `ghidra.py` (Script Manager in Ghidra).
3. Select `script.json` when prompted to auto-rename all subroutines to their corresponding C# method signatures.

---

## Disclaimer

This repository and its contents are provided strictly for educational, security analysis, and reverse engineering research purposes. All trademarks, copyrights, and game assets belong to Moonton and their respective owners.