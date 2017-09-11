    test_blocking_io_errors(cfg);
    if (throughput) test_throughput(cfg);

    if (fails) {
        printf("*** %d TESTS FAILED ***\n", fails);
        return 1;
