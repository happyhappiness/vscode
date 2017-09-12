    return sdscpylen(s, t, strlen(t));
}

sds sdscatprintf(sds s, const char *fmt, ...) {
    va_list ap;
    char *buf, *t;
    size_t buflen = 16;

