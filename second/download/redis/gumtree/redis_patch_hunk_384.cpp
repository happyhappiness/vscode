     char buf[SDS_LLSTR_SIZE];
     int len = sdsll2str(buf,value);
 
     return sdsnewlen(buf,len);
 }
 
-/* Like sdscatpritf() but gets va_list instead of being variadic. */
+/* Like sdscatprintf() but gets va_list instead of being variadic. */
 sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
     va_list cpy;
     char staticbuf[1024], *buf = staticbuf, *t;
     size_t buflen = strlen(fmt)*2;
 
     /* We try to start using a static buffer for speed.
      * If not possible we revert to heap allocation. */
     if (buflen > sizeof(staticbuf)) {
-        buf = zmalloc(buflen);
+        buf = s_malloc(buflen);
         if (buf == NULL) return NULL;
     } else {
         buflen = sizeof(staticbuf);
     }
 
     /* Try with buffers two times bigger every time we fail to
      * fit the string in the current buffer size. */
     while(1) {
         buf[buflen-2] = '\0';
         va_copy(cpy,ap);
         vsnprintf(buf, buflen, fmt, cpy);
-        va_end(ap);
+        va_end(cpy);
         if (buf[buflen-2] != '\0') {
-            if (buf != staticbuf) zfree(buf);
+            if (buf != staticbuf) s_free(buf);
             buflen *= 2;
-            buf = zmalloc(buflen);
+            buf = s_malloc(buflen);
             if (buf == NULL) return NULL;
             continue;
         }
         break;
     }
 
     /* Finally concat the obtained string to the SDS string and return it. */
     t = sdscat(s, buf);
-    if (buf != staticbuf) zfree(buf);
+    if (buf != staticbuf) s_free(buf);
     return t;
 }
 
 /* Append to the sds string 's' a string obtained using printf-alike format
  * specifier.
  *
  * After the call, the modified sds string is no longer valid and all the
  * references must be substituted with the new pointer returned by the call.
  *
  * Example:
  *
- * s = sdsempty("Sum is: ");
+ * s = sdsnew("Sum is: ");
  * s = sdscatprintf(s,"%d+%d = %d",a,b,a+b).
  *
  * Often you need to create a string from scratch with the printf-alike
  * format. When this is the need, just use sdsempty() as the target string:
  *
  * s = sdscatprintf(sdsempty(), "... your format ...", args);
