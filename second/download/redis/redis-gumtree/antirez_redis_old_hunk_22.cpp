}

/* RDB check main: called form redis.c when Redis is executed with the
 * redis-check-rdb alias.
 *
 * The function never returns, but exits with the status code according
 * to success (RDB is sane) or error (RDB is corrupted). */
int redis_check_rdb_main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <rdb-file-name>\n", argv[0]);
        exit(1);
    }
