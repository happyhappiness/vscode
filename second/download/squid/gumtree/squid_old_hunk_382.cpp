    } else if (strncmp(token, "net", 3) == 0) {
        Config.onoff.memory_cache_first = 1;
        Config.onoff.memory_cache_disk = 0;
    } else if (strcmp(token, "never") == 0) {
        Config.onoff.memory_cache_first = 0;
        Config.onoff.memory_cache_disk = 0;
    } else
        self_destruct();
}

static void
dump_memcachemode(StoreEntry * entry, const char *name, SquidConfig &config)
{
    storeAppendPrintf(entry, "%s ", name);
