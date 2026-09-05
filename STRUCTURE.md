# MLBB Architecture & Symbol Structure

A detailed technical breakdown of Mobile Legends: Bang Bang (ARM64) disassembled internals, partitioned assemblies, subsystem mappings, and symbol registries.

---

## 1. Partition Map

MLBB divides its code into three distinct metadata partitions to optimize loading and support Moonton's HybridCLR execution model:

| Partition | Source Metadata | Target Assembly | Types | Methods | Primary Role |
| :---: | :--- | :--- | :---: | :---: | :--- |
| **1** | `global-metadata.dat` | `UnityEngine.CoreModule.dll` | 5,440 | 36,409 | Unity Engine base types, math, serialization, components |
| **2** | `global-first-metadata.dat` | `Assembly-CSharp-firstpass.dll` | 1,561 | 11,218 | Native third-party plugins, platform SDKs, native bindings |
| **3** | `global-csharp-metadata.dat` | `Assembly-CSharp.dll` | 21,907 | 174,097 | Game logic, hero definitions, combat state machine, UI, networking |

---

## 2. Core Subsystems & Key Classes

### Networking & Packet Transport
The game implements a custom network transport layer wrapped over RakNet and standard socket polling with zstandard compression and crypto utilities:
* `RakNetWrapperLib`: Low-level RakNet communication bridge.
* `MultiNetworkLib`: Multi-path network routing and failover.
* `NetCryptoUtilLib`: Packet encryption and session handshake primitives.
* `NetZstdUtilLib`: Stream compression for game state synchronization packets.
* `NetOptSocketPollLib`: Optimized non-blocking socket polling.
* `NetworkState`: Central connectivity state tracker.

### Battle & Combat Systems
The combat subsystem manages state synchronization, skill casting, health/damage computation, and hero entities:
* `BattleData`: Central match state, entity tracking, and participant metrics.
* `BattleAHKLIb`: Automation and input handler bindings for combat triggers.
* `IShowStruct_EventProxy_GMServer_PlayerMakeSkill`: Server-validated skill execution dispatch.
* `IShowStruct_EventProxy_GM_OnSkillCastSuccess`: Client skill execution acknowledgment and visual FX trigger.
* `IShowStruct_EventProxy_CollectPlayerDeadPosDataWarnBattle`: Combat positioning and death telemetry.

### Event Proxy System
MLBB utilizes an extensive `IShowStruct_EventProxy_*` event broker architecture to decouple battle events from visual rendering:
* `IShowStruct_EventProxy_GUIDE_CREATE_ENTITY_SHOW`: Spawns battlefield visual entities.
* `IShowStruct_EventProxy_GUIDE_CREATE_TOWER_SHOW`: Tower structure state machine events.
* `IShowStruct_EventProxy_GUIDE_FIGHTER_RELIVE_SHOW`: Hero respawn state synchronization.
* `IShowStruct_EventProxy_GUIDE_REMOVE_FIGHTER_SHOW`: Hero despawn / death state.
* `IShowStruct_EventProxy_GUIDE_SET_FIGHTER_POS_SHOW`: Position synchronization updates.

### Video & Media Players
* `NativeVideoPlayerLib`: Platform native video rendering pipeline.
* `NativeVideoPlayerEntryLib`: Bridge between Unity canvas and hardware video decoder.
* `GMVideoPlayerAOT`: Ahead-of-time compiled video playback routines.

---

## 3. Tooling Integration & Symbols

### Symbol Database (`script.json`)
Contains 221,724 entries mapping addresses in `libcsharp.so` to high-level signatures:
* `Address`: Relative Virtual Address (RVA) in the native ELF binary.
* `Name`: Fully qualified method signature with parameters and declaring class.
* `Signature`: Type descriptor string.

### String Literals (`stringliteral.json`)
Contains 86,844 extracted strings from all three partitions, indexed by their token ID and partition identifier.

### Disassembler Scripts
* **IDA Pro (`ida.py`)**: Executes in IDAPython to label functions, set method prototypes, and create struct definitions.
* **Ghidra (`ghidra.py`)**: Ghidra script to bulk-rename functions in the Symbol Tree.
* **Binary Ninja (`binja.py`)**: Script using Binary Ninja's Python API to label symbols.

---

## 4. Assembly Inspection (`DummyDll/`)

The stripped assemblies in `DummyDll/` contain full type definitions, properties, method signatures, and field offsets without method IL bodies:
* `Assembly-CSharp.dll` (12.7 MB)
* `Assembly-CSharp-firstpass.dll` (787 KB)
* `UnityEngine.CoreModule.dll` (2.3 MB)

These assemblies can be referenced directly in reverse engineering environments, decompilers (dnSpy, ILSpy), or custom analysis harnesses.