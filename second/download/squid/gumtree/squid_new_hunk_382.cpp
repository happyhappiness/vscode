    } else if (strncmp(token, "net", 3) == 0) {
        Config.onoff.memory_cache_first = 1;
        Config.onoff.memory_cache_disk = 0;
    } else if (strcmp(token, "never") == 0) {
        Config.onoff.memory_cache_first = 0;
        Config.onoff.memory_cache_disk = 0;
    } else {
        debugs(0, DBG_PARSE_NOTE(2), "ERROR: Invalid option '" << token << "': 'memory_cache_mode' accepts 'always', 'disk', 'network', and 'never'.");
        self_destruct();
    }
}

static void
dump_memcachemode(StoreEntry * entry, const char *name, SquidConfig &config)
{
    storeAppendPrintf(entry, "%s ", name);
