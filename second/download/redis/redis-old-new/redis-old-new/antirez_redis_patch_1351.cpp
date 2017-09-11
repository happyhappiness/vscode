@@ -60,13 +60,13 @@ sds sdsempty();
 size_t sdslen(const sds s);
 sds sdsdup(const sds s);
 void sdsfree(sds s);
-size_t sdsavail(sds s);
+size_t sdsavail(const sds s);
 sds sdsgrowzero(sds s, size_t len);
-sds sdscatlen(sds s, void *t, size_t len);
-sds sdscat(sds s, char *t);
-sds sdscatsds(sds s, sds t);
-sds sdscpylen(sds s, char *t, size_t len);
-sds sdscpy(sds s, char *t);
+sds sdscatlen(sds s, const void *t, size_t len);
+sds sdscat(sds s, const char *t);
+sds sdscatsds(sds s, const sds t);
+sds sdscpylen(sds s, const char *t, size_t len);
+sds sdscpy(sds s, const char *t);
 
 sds sdscatvprintf(sds s, const char *fmt, va_list ap);
 #ifdef __GNUC__
@@ -80,16 +80,16 @@ sds sdstrim(sds s, const char *cset);
 sds sdsrange(sds s, int start, int end);
 void sdsupdatelen(sds s);
 void sdsclear(sds s);
-int sdscmp(sds s1, sds s2);
-sds *sdssplitlen(char *s, int len, char *sep, int seplen, int *count);
+int sdscmp(const sds s1, const sds s2);
+sds *sdssplitlen(const char *s, int len, const char *sep, int seplen, int *count);
 void sdsfreesplitres(sds *tokens, int count);
 void sdstolower(sds s);
 void sdstoupper(sds s);
 sds sdsfromlonglong(long long value);
-sds sdscatrepr(sds s, char *p, size_t len);
-sds *sdssplitargs(char *line, int *argc);
+sds sdscatrepr(sds s, const char *p, size_t len);
+sds *sdssplitargs(const char *line, int *argc);
 void sdssplitargs_free(sds *argv, int argc);
-sds sdsmapchars(sds s, char *from, char *to, size_t setlen);
+sds sdsmapchars(sds s, const char *from, const char *to, size_t setlen);
 
 /* Low level functions exposed to the user API */
 sds sdsMakeRoomFor(sds s, size_t addlen);