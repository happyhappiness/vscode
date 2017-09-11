}

/* RDB check main: called form redis.c when Redis is executed with the
 * redis-check-rdb alias, on during RDB loading errors.
 *
 * The function works in two ways: can be called with argc/argv as a
 * standalone executable, or called with a non NULL 'fp' argument if we
 * already have an open file to check. This happens when the function
 * is used to check an RDB preamble inside an AOF file.
 *
 * When called with fp = NULL, the function never returns, but exits with the
 * status code according to success (RDB is sane) or error (RDB is corrupted).
 * Otherwise if called with a non NULL fp, the function returns C_OK or
 * C_ERR depending on the success or failure. */
int redis_check_rdb_main(int argc, char **argv, FILE *fp) {
    if (argc != 2 && fp == NULL) {
        fprintf(stderr, "Usage: %s <rdb-file-name>\n", argv[0]);
        exit(1);
    }
