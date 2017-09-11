// }

int main(int argc, char **argv) {
    if (argc > 1) {
        if (strcmp(argv[1],"-s") == 0)
            use_unix = 1;
    }

    signal(SIGPIPE, SIG_IGN);
    test_format_commands();
    test_blocking_connection();
    test_reply_reader();
    // test_nonblocking_connection();
    test_throughput();
    cleanup();

    if (fails == 0) {
        printf("ALL TESTS PASSED\n");
    } else {
        printf("*** %d TESTS FAILED ***\n", fails);
    }
    return 0;
}
