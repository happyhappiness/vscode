        "noeviction", REDIS_MAXMEMORY_NO_EVICTION,
        NULL, REDIS_DEFAULT_MAXMEMORY_POLICY);
    rewriteConfigNumericalOption(state,"maxmemory-samples",server.maxmemory_samples,REDIS_DEFAULT_MAXMEMORY_SAMPLES);
    rewriteConfigYesNoOption(state,"appendonly",server.aof_state != REDIS_AOF_OFF,0);
    rewriteConfigStringOption(state,"appendfilename",server.aof_filename,REDIS_DEFAULT_AOF_FILENAME);
    rewriteConfigEnumOption(state,"appendfsync",server.aof_fsync,
        "everysec", AOF_FSYNC_EVERYSEC,
        "always", AOF_FSYNC_ALWAYS,
