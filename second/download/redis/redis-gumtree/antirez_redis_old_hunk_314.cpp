        fprintf(stderr, "Usage: %s <rdb-file-name>\n", argv[0]);
        exit(1);
    }
    createSharedObjects(); /* Needed for loading. */
    server.loading_process_events_interval_bytes = 0;
    rdbCheckMode = 1;
    rdbCheckInfo("Checking RDB file %s", argv[1]);
