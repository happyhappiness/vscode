sds sdscat(sds s, char *t);
sds sdscpylen(sds s, char *t, size_t len);
sds sdscpy(sds s, char *t);
sds sdssetbit(sds s, size_t bit, int on);

sds sdscatvprintf(sds s, const char *fmt, va_list ap);
#ifdef __GNUC__
