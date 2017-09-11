@@ -292,25 +292,37 @@ sds sdscpy(sds s, const char *t) {
 /* Like sdscatpritf() but gets va_list instead of being variadic. */
 sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
     va_list cpy;
-    char *buf, *t;
-    size_t buflen = strlen(fmt)*4;
+    char staticbuf[1024], *buf = staticbuf, *t;
+    size_t buflen = strlen(fmt)*2;
 
-    if (buflen < 32) buflen = 32;
-    while(1) {
+    /* We try to start using a static buffer for speed.
+     * If not possible we revert to heap allocation. */
+    if (buflen > sizeof(staticbuf)) {
         buf = zmalloc(buflen);
         if (buf == NULL) return NULL;
+    } else {
+        buflen = sizeof(staticbuf);
+    }
+
+    /* Try with buffers two times bigger every time we fail to
+     * fit the string in the current buffer size. */
+    while(1) {
         buf[buflen-2] = '\0';
         va_copy(cpy,ap);
         vsnprintf(buf, buflen, fmt, cpy);
         if (buf[buflen-2] != '\0') {
-            zfree(buf);
+            if (buf != staticbuf) zfree(buf);
             buflen *= 2;
+            buf = zmalloc(buflen);
+            if (buf == NULL) return NULL;
             continue;
         }
         break;
     }
+
+    /* Finally concat the obtained string to the SDS string and return it. */
     t = sdscat(s, buf);
-    zfree(buf);
+    if (buf != staticbuf) zfree(buf);
     return t;
 }
 