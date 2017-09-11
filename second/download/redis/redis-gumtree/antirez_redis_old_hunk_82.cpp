    test_format_commands();
    test_reply_reader();
    test_blocking_connection_errors();

    printf("\nTesting against TCP connection (%s:%d):\n", cfg.tcp.host, cfg.tcp.port);
    cfg.type = CONN_TCP;
    test_blocking_connection(cfg);
    test_blocking_io_errors(cfg);
    if (throughput) test_throughput(cfg);

    printf("\nTesting against Unix socket connection (%s):\n", cfg.unix.path);
    cfg.type = CONN_UNIX;
    test_blocking_connection(cfg);
    test_blocking_io_errors(cfg);
    if (throughput) test_throughput(cfg);

    if (fails) {
        printf("*** %d TESTS FAILED ***\n", fails);
        return 1;
