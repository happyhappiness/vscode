static void
dump_memcachemode(StoreEntry * entry, const char *name, SquidConfig &config)
{
    storeAppendPrintf(entry, "%s ", name);
    if (Config.onoff.memory_cache_first && Config.onoff.memory_cache_disk)
        storeAppendPrintf(entry, "always");
    else if (!Config.onoff.memory_cache_first && Config.onoff.memory_cache_disk)
        storeAppendPrintf(entry, "disk");
    else if (Config.onoff.memory_cache_first && !Config.onoff.memory_cache_disk)
        storeAppendPrintf(entry, "network");
    else if (!Config.onoff.memory_cache_first && !Config.onoff.memory_cache_disk)
        storeAppendPrintf(entry, "none");
    storeAppendPrintf(entry, "\n");
}