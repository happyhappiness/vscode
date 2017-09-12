void rdbCheckInfo(const char *fmt, ...) {
    char msg[1024];
    va_list ap;

    va_start(ap, fmt);
    vsnprintf(msg, sizeof(msg), fmt, ap);
    va_end(ap);

    printf("[offset %llu] %s\n",
        (unsigned long long) (rdbstate.rio ?
            rdbstate.rio->processed_bytes : 0), msg);
}