@@ -33,7 +33,6 @@
 #include "sds.h"
 #include <stdio.h>
 #include <stdlib.h>
-#include <stdarg.h>
 #include <string.h>
 #include <ctype.h>
 #include "zmalloc.h"
@@ -156,8 +155,8 @@ sds sdscpy(sds s, char *t) {
     return sdscpylen(s, t, strlen(t));
 }
 
-sds sdscatprintf(sds s, const char *fmt, ...) {
-    va_list ap;
+sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
+    va_list cpy;
     char *buf, *t;
     size_t buflen = 16;
 
@@ -169,9 +168,8 @@ sds sdscatprintf(sds s, const char *fmt, ...) {
         if (buf == NULL) return NULL;
 #endif
         buf[buflen-2] = '\0';
-        va_start(ap, fmt);
-        vsnprintf(buf, buflen, fmt, ap);
-        va_end(ap);
+        va_copy(cpy,ap);
+        vsnprintf(buf, buflen, fmt, cpy);
         if (buf[buflen-2] != '\0') {
             zfree(buf);
             buflen *= 2;
@@ -184,6 +182,15 @@ sds sdscatprintf(sds s, const char *fmt, ...) {
     return t;
 }
 
+sds sdscatprintf(sds s, const char *fmt, ...) {
+    va_list ap;
+    char *t;
+    va_start(ap, fmt);
+    t = sdscatvprintf(s,fmt,ap);
+    va_end(ap);
+    return t;
+}
+
 sds sdstrim(sds s, const char *cset) {
     struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
     char *start, *end, *sp, *ep;