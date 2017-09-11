 *
 * The function never returns, but exits with the status code according
 * to success (RDB is sane) or error (RDB is corrupted). */
int redis_check_rdb_main(char **argv, int argc) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <rdb-file-name>\n", argv[0]);
        exit(1);
    }
    createSharedObjects(); /* Needed for loading. */
    server.loading_process_events_interval_bytes = 0;
    rdbCheckInfo("Checking RDB file %s", argv[1]);
    rdbCheckSetupSignals();
    int retval = redis_check_rdb(argv[1]);
    if (retval == 0) {
        rdbCheckInfo("\\o/ RDB looks OK! \\o/");
    }
    exit(retval);
}
