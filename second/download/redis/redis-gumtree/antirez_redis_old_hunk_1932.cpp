sds sdscatprintf(sds s, const char *fmt, ...);
#endif

void sdstrim(sds s, const char *cset);
void sdsrange(sds s, int start, int end);
void sdsupdatelen(sds s);
void sdsclear(sds s);
