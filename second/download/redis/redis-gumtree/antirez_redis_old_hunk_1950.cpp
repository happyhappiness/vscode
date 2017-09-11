    cfg.type = CONN_TCP;
    test_blocking_connection(cfg);
    test_blocking_io_errors(cfg);
    if (throughput) test_throughput(cfg);

    printf("\nTesting against Unix socket connection (%s):\n", cfg.unix.path);
