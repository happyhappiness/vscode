        "noeviction", REDIS_MAXMEMORY_NO_EVICTION,
        NULL, REDIS_DEFAULT_MAXMEMORY_POLICY);
    rewriteConfigNumericalOption(state,"maxmemory-samples",server.maxmemory_samples,REDIS_DEFAULT_MAXMEMORY_SAMPLES);
    rewriteConfigAppendonlyOption(state);
    rewriteConfigEnumOption(state,"appendfsync",server.aof_fsync,
        "everysec", AOF_FSYNC_EVERYSEC,
        "always", AOF_FSYNC_ALWAYS,
