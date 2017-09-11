        fprintf(stderr, "Usage: %s <rdb-file-name>\n", argv[0]);
        exit(1);
    }
    /* In order to call the loading functions we need to create the shared
     * integer objects, however since this function may be called from
     * an already initialized Redis instance, check if we really need to. */
    if (shared.integers[0] == NULL)
        createSharedObjects();
    server.loading_process_events_interval_bytes = 0;
    rdbCheckMode = 1;
    rdbCheckInfo("Checking RDB file %s", argv[1]);
