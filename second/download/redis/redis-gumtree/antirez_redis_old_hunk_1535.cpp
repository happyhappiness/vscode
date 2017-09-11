    rewriteConfigStringOption(state,"requirepass",server.requirepass,NULL);
    rewriteConfigNumericalOption(state,"maxclients",server.maxclients,REDIS_MAX_CLIENTS);
    rewriteConfigBytesOption(state,"maxmemory",server.maxmemory,REDIS_DEFAULT_MAXMEMORY);
    rewriteConfigEnumOption(state,"maxmemory-policy",server.maxmemory_policy,
        "volatile-lru", REDIS_MAXMEMORY_VOLATILE_LRU,
        "allkeys-lru", REDIS_MAXMEMORY_ALLKEYS_LRU,
        "volatile-random", REDIS_MAXMEMORY_VOLATILE_RANDOM,
        "allkeys-random", REDIS_MAXMEMORY_ALLKEYS_RANDOM,
        "volatile-ttl", REDIS_MAXMEMORY_VOLATILE_TTL,
        "noeviction", REDIS_MAXMEMORY_NO_EVICTION,
        NULL, REDIS_DEFAULT_MAXMEMORY_POLICY);
    rewriteConfigNumericalOption(state,"maxmemory-samples",server.maxmemory_samples,REDIS_DEFAULT_MAXMEMORY_SAMPLES);
    rewriteConfigYesNoOption(state,"appendonly",server.aof_state != REDIS_AOF_OFF,0);
    rewriteConfigStringOption(state,"appendfilename",server.aof_filename,REDIS_DEFAULT_AOF_FILENAME);
    rewriteConfigEnumOption(state,"appendfsync",server.aof_fsync,
        "everysec", AOF_FSYNC_EVERYSEC,
        "always", AOF_FSYNC_ALWAYS,
        "no", AOF_FSYNC_NO,
        NULL, REDIS_DEFAULT_AOF_FSYNC);
    rewriteConfigYesNoOption(state,"no-appendfsync-on-rewrite",server.aof_no_fsync_on_rewrite,REDIS_DEFAULT_AOF_NO_FSYNC_ON_REWRITE);
    rewriteConfigNumericalOption(state,"auto-aof-rewrite-percentage",server.aof_rewrite_perc,REDIS_AOF_REWRITE_PERC);
    rewriteConfigBytesOption(state,"auto-aof-rewrite-min-size",server.aof_rewrite_min_size,REDIS_AOF_REWRITE_MIN_SIZE);
