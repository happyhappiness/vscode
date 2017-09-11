@@ -76,6 +76,7 @@ sds sdscatprintf(sds s, const char *fmt, ...)
 sds sdscatprintf(sds s, const char *fmt, ...);
 #endif
 
+sds sdscatfmt(sds s, char const *fmt, ...);
 sds sdstrim(sds s, const char *cset);
 void sdsrange(sds s, int start, int end);
 void sdsupdatelen(sds s);