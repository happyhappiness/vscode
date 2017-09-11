@@ -388,6 +388,7 @@ sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
         buf[buflen-2] = '\0';
         va_copy(cpy,ap);
         vsnprintf(buf, buflen, fmt, cpy);
+        va_end(ap);
         if (buf[buflen-2] != '\0') {
             if (buf != staticbuf) zfree(buf);
             buflen *= 2;