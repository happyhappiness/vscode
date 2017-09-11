@@ -31,6 +31,8 @@
 #ifndef __SDS_H
 #define __SDS_H
 
+#define SDS_MAX_PREALLOC (1024*1024)
+
 #include <sys/types.h>
 #include <stdarg.h>
 
@@ -54,16 +56,17 @@ static inline size_t sdsavail(const sds s) {
 
 sds sdsnewlen(const void *init, size_t initlen);
 sds sdsnew(const char *init);
-sds sdsempty(void);
+sds sdsempty();
 size_t sdslen(const sds s);
 sds sdsdup(const sds s);
 void sdsfree(sds s);
-size_t sdsavail(sds s);
+size_t sdsavail(const sds s);
 sds sdsgrowzero(sds s, size_t len);
 sds sdscatlen(sds s, const void *t, size_t len);
 sds sdscat(sds s, const char *t);
-sds sdscpylen(sds s, char *t, size_t len);
-sds sdscpy(sds s, char *t);
+sds sdscatsds(sds s, const sds t);
+sds sdscpylen(sds s, const char *t, size_t len);
+sds sdscpy(sds s, const char *t);
 
 sds sdscatvprintf(sds s, const char *fmt, va_list ap);
 #ifdef __GNUC__
@@ -74,15 +77,24 @@ sds sdscatprintf(sds s, const char *fmt, ...);
 #endif
 
 sds sdstrim(sds s, const char *cset);
-sds sdsrange(sds s, int start, int end);
+void sdsrange(sds s, int start, int end);
 void sdsupdatelen(sds s);
-int sdscmp(sds s1, sds s2);
-sds *sdssplitlen(char *s, int len, char *sep, int seplen, int *count);
+void sdsclear(sds s);
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
+sds sdsmapchars(sds s, const char *from, const char *to, size_t setlen);
+sds sdsjoin(char **argv, int argc, char *sep);
+
+/* Low level functions exposed to the user API */
+sds sdsMakeRoomFor(sds s, size_t addlen);
+void sdsIncrLen(sds s, int incr);
+sds sdsRemoveFreeSpace(sds s);
+size_t sdsAllocSize(sds s);
 
 #endif