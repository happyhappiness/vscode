@@ -32,6 +32,7 @@
 #define __SDS_H
 
 #include <sys/types.h>
+#include <stdarg.h>
 
 typedef char *sds;
 
@@ -53,6 +54,7 @@ sds sdscat(sds s, char *t);
 sds sdscpylen(sds s, char *t, size_t len);
 sds sdscpy(sds s, char *t);
 
+sds sdscatvprintf(sds s, const char *fmt, va_list ap);
 #ifdef __GNUC__
 sds sdscatprintf(sds s, const char *fmt, ...)
     __attribute__((format(printf, 2, 3)));
@@ -70,5 +72,6 @@ void sdstolower(sds s);
 void sdstoupper(sds s);
 sds sdsfromlonglong(long long value);
 sds sdscatrepr(sds s, char *p, size_t len);
+sds *sdssplitargs(char *line, int *argc);
 
 #endif