sds sdscpylen(sds s, char *t, size_t len);
sds sdscpy(sds s, char *t);

#ifdef __GNUC__
sds sdscatprintf(sds s, const char *fmt, ...)
    __attribute__((format(printf, 2, 3)));
