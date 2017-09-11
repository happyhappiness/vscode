    rewriteConfigNumericalOption(state,"hz",server.hz,REDIS_DEFAULT_HZ);
    rewriteConfigYesNoOption(state,"aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync,REDIS_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC);
    rewriteConfigYesNoOption(state,"aof-load-truncated",server.aof_load_truncated,REDIS_DEFAULT_AOF_LOAD_TRUNCATED);
    rewriteConfigEnumOption(state,"supervised",server.supervised_mode,
        "upstart", REDIS_SUPERVISED_UPSTART,
        "systemd", REDIS_SUPERVISED_SYSTEMD,
        "auto", REDIS_SUPERVISED_AUTODETECT,
        "no", REDIS_SUPERVISED_NONE,
        NULL, REDIS_SUPERVISED_NONE);
    if (server.sentinel_mode) rewriteConfigSentinelOption(state);

    /* Step 3: remove all the orphaned lines in the old file, that is, lines
