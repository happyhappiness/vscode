        debugs(0, DBG_PARSE_NOTE(2), "ERROR: Invalid option '" << token << "': 'memory_cache_mode' accepts 'always', 'disk', 'network', and 'never'.");
        self_destruct();
    }
}

static void
dump_memcachemode(StoreEntry * entry, const char *name, SquidConfig &)
{
    storeAppendPrintf(entry, "%s ", name);
    if (Config.onoff.memory_cache_first && Config.onoff.memory_cache_disk)
        storeAppendPrintf(entry, "always");
    else if (!Config.onoff.memory_cache_first && Config.onoff.memory_cache_disk)
        storeAppendPrintf(entry, "disk");
