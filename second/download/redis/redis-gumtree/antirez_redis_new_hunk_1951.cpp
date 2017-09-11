    test_blocking_io_errors(cfg);
    if (throughput) test_throughput(cfg);

    if (test_inherit_fd) {
        printf("\nTesting against inherited fd (%s):\n", cfg.unix.path);
        cfg.type = CONN_FD;
        test_blocking_connection(cfg);
    }

    if (fails) {
        printf("*** %d TESTS FAILED ***\n", fails);
        return 1;
