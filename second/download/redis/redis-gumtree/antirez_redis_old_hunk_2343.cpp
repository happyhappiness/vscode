    return t;
}

sds sdscatprintf(sds s, const char *fmt, ...) {
    va_list ap;
    char *t;
