     s[len] = '\0';
     sh->len = len;
     sh->free = totlen-len;
     return s;
 }
 
-sds sdscpy(sds s, char *t) {
+/* Like sdscpylen() but 't' must be a null-termined string so that the length
+ * of the string is obtained with strlen(). */
+sds sdscpy(sds s, const char *t) {
     return sdscpylen(s, t, strlen(t));
 }
 
+/* Like sdscatpritf() but gets va_list instead of being variadic. */
 sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
     va_list cpy;
     char *buf, *t;
     size_t buflen = 16;
 
     while(1) {
-        buf = malloc(buflen);
-#ifdef SDS_ABORT_ON_OOM
-        if (buf == NULL) sdsOomAbort();
-#else
+        buf = zmalloc(buflen);
         if (buf == NULL) return NULL;
-#endif
         buf[buflen-2] = '\0';
         va_copy(cpy,ap);
         vsnprintf(buf, buflen, fmt, cpy);
         if (buf[buflen-2] != '\0') {
-            free(buf);
+            zfree(buf);
             buflen *= 2;
             continue;
         }
         break;
     }
     t = sdscat(s, buf);
-    free(buf);
+    zfree(buf);
     return t;
 }
 
+/* Append to the sds string 's' a string obtained using printf-alike format
+ * specifier.
+ *
+ * After the call, the modified sds string is no longer valid and all the
+ * references must be substituted with the new pointer returned by the call.
+ *
+ * Example:
+ *
+ * s = sdsempty("Sum is: ");
+ * s = sdscatprintf(s,"%d+%d = %d",a,b,a+b).
+ *
+ * Often you need to create a string from scratch with the printf-alike
+ * format. When this is the need, just use sdsempty() as the target string:
+ *
+ * s = sdscatprintf(sdsempty(), "... your format ...", args);
+ */
 sds sdscatprintf(sds s, const char *fmt, ...) {
     va_list ap;
     char *t;
     va_start(ap, fmt);
     t = sdscatvprintf(s,fmt,ap);
     va_end(ap);
     return t;
 }
 
+/* Remove the part of the string from left and from right composed just of
+ * contiguous characters found in 'cset', that is a null terminted C string.
+ *
+ * After the call, the modified sds string is no longer valid and all the
+ * references must be substituted with the new pointer returned by the call.
+ *
+ * Example:
+ *
+ * s = sdsnew("AA...AA.a.aa.aHelloWorld     :::");
+ * s = sdstrim(s,"A. :");
+ * printf("%s\n", s);
+ *
+ * Output will be just "Hello World".
+ */
 sds sdstrim(sds s, const char *cset) {
     struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
     char *start, *end, *sp, *ep;
     size_t len;
 
     sp = start = s;
