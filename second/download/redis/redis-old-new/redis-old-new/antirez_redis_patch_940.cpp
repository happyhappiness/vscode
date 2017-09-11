@@ -293,8 +293,9 @@ sds sdscpy(sds s, const char *t) {
 sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
     va_list cpy;
     char *buf, *t;
-    size_t buflen = 16;
+    size_t buflen = strlen(fmt)*4;
 
+    if (buflen < 32) buflen = 32;
     while(1) {
         buf = zmalloc(buflen);
         if (buf == NULL) return NULL;