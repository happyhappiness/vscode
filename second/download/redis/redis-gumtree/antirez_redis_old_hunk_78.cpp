sds sdscatprintf(sds s, const char *fmt, ...);
#endif

sds sdstrim(sds s, const char *cset);
sds sdsrange(sds s, int start, int end);
void sdsupdatelen(sds s);
int sdscmp(sds s1, sds s2);
sds *sdssplitlen(char *s, int len, char *sep, int seplen, int *count);
void sdsfreesplitres(sds *tokens, int count);
void sdstolower(sds s);
void sdstoupper(sds s);
sds sdsfromlonglong(long long value);
sds sdscatrepr(sds s, char *p, size_t len);
sds *sdssplitargs(char *line, int *argc);

#endif
