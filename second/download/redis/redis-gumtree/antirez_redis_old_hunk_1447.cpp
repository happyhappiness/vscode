sds sdscpylen(sds s, const char *t, size_t len);
sds sdscpy(sds s, const char *t);

/* we can add a reference count on top of any 
 * existing sds. (max up to 63 references) */
void sdsIncRefcount(sds s);
void sdsDecRefcount(sds s);

sds sdscatvprintf(sds s, const char *fmt, va_list ap);
#ifdef __GNUC__
sds sdscatprintf(sds s, const char *fmt, ...)
