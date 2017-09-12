sds sdscatprintf(sds s, const char *fmt, ...) {
    va_list ap;
    char *buf, *t;
    size_t buflen = 32;

    while(1) {
        buf = zmalloc(buflen);
