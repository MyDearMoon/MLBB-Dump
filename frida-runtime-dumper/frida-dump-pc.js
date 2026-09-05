// Frida In-Memory Dumper for Windows Unity Games
// Usage: frida -n Game.exe -l frida-dump-pc.js

console.log('[+] PC Il2Cpp Dumper script loaded.');

function searchMetadata() {
    var SANITY = 0xFAB11BAF;
    Process.enumerateRanges('r--').forEach(function(range) {
        try {
            if (range.size < 0x1000) return;
            var magic = range.base.readU32();
            if (magic === SANITY) {
                var version = range.base.add(4).readS32();
                console.log('[+] Found global-metadata.dat in memory at: ' + range.base + ' (version: ' + version + ')');
            }
        } catch(e) {}
    });
}

var mod = Process.findModuleByName('GameAssembly.dll');
if (mod) {
    console.log('[+] Found GameAssembly.dll at: ' + mod.base + ' (size: ' + mod.size + ')');
    searchMetadata();
} else {
    console.log('[-] GameAssembly.dll not found in current process.');
}
