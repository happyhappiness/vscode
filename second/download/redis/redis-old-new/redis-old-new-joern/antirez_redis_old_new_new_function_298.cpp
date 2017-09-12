void rdbCheckSetError(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    vsnprintf(rdbstate.error, sizeof(rdbstate.error), fmt, ap);
    va_end(ap);
    rdbstate.error_set = 1;
}