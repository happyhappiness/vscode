sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
    va_list cpy;
    char *buf, *t;
    size_t buflen = 16;

    while(1) {
        buf = zmalloc(buflen);
        if (buf == NULL) return NULL;
