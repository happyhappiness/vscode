    rewriteConfigNumericalOption(state,"hz",server.hz,REDIS_DEFAULT_HZ);
    rewriteConfigYesNoOption(state,"aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync,REDIS_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC);
    rewriteConfigYesNoOption(state,"aof-load-truncated",server.aof_load_truncated,REDIS_DEFAULT_AOF_LOAD_TRUNCATED);
    rewriteConfigEnumOption(state,"supervised",server.supervised_mode,supervised_mode_enum,REDIS_SUPERVISED_NONE);

    /* Rewrite Sentinel config if in Sentinel mode. */
    if (server.sentinel_mode) rewriteConfigSentinelOption(state);

    /* Step 3: remove all the orphaned lines in the old file, that is, lines
