static void
dump_CpuAffinityMap(StoreEntry *const entry, const char *const name, const CpuAffinityMap *const cpuAffinityMap)
{
    if (cpuAffinityMap) {
        storeAppendPrintf(entry, "%s process_numbers=", name);
        for (size_t i = 0; i < cpuAffinityMap->processes().size(); ++i) {
            storeAppendPrintf(entry, "%s%i", (i ? "," : ""),
                              cpuAffinityMap->processes()[i]);
        }
        storeAppendPrintf(entry, " cores=");
        for (size_t i = 0; i < cpuAffinityMap->cores().size(); ++i) {
            storeAppendPrintf(entry, "%s%i", (i ? "," : ""),
                              cpuAffinityMap->cores()[i]);
        }
        storeAppendPrintf(entry, "\n");
    }
}