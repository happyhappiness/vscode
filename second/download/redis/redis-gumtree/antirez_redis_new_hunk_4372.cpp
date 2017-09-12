sds sdscat(sds s, char *t);
sds sdscpylen(sds s, char *t, size_t len);
sds sdscpy(sds s, char *t);

#ifdef __GNUC__
sds sdscatprintf(sds s, const char *fmt, ...)
    __attribute__((format(printf, 2, 3)));
#else
sds sdscatprintf(sds s, const char *fmt, ...);
#endif

sds sdstrim(sds s, const char *cset);
sds sdsrange(sds s, long start, long end);
void sdsupdatelen(sds s);
