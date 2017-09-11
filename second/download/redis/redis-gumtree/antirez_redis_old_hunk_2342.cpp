    return s;
}

sds sdscpy(sds s, const char *t) {
    return sdscpylen(s, t, strlen(t));
}

sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
    va_list cpy;
    char *buf, *t;
