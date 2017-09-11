            rdbstate.rio->processed_bytes : 0), msg);
}

/* Used inside rdb.c in order to log specific errors happening inside
 * the RDB loading internals. */
void rdbCheckSetError(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    vsnprintf(rdbstate.error, sizeof(rdbstate.error), fmt, ap);
    va_end(ap);
    rdbstate.error_set = 1;
}

/* During RDB check we setup a special signal handler for memory violations
 * and similar conditions, so that we can log the offending part of the RDB
 * if the crash is due to broken content. */
