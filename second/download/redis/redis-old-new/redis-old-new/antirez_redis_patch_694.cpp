@@ -295,7 +295,7 @@ sds sdscpy(sds s, const char *t) {
  * conversion. 's' must point to a string with room for at least
  * SDS_LLSTR_SIZE bytes.
  *
- * The function returns the lenght of the null-terminated string
+ * The function returns the length of the null-terminated string
  * representation stored at 's'. */
 #define SDS_LLSTR_SIZE 21
 int sdsll2str(char *s, long long value) {
@@ -369,7 +369,7 @@ sds sdsfromlonglong(long long value) {
     return sdsnewlen(buf,len);
 }
 
-/* Like sdscatpritf() but gets va_list instead of being variadic. */
+/* Like sdscatprintf() but gets va_list instead of being variadic. */
 sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
     va_list cpy;
     char staticbuf[1024], *buf = staticbuf, *t;
@@ -390,7 +390,7 @@ sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
         buf[buflen-2] = '\0';
         va_copy(cpy,ap);
         vsnprintf(buf, buflen, fmt, cpy);
-        va_end(ap);
+        va_end(cpy);
         if (buf[buflen-2] != '\0') {
             if (buf != staticbuf) zfree(buf);
             buflen *= 2;
@@ -415,7 +415,7 @@ sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
  *
  * Example:
  *
- * s = sdsempty("Sum is: ");
+ * s = sdsnew("Sum is: ");
  * s = sdscatprintf(s,"%d+%d = %d",a,b,a+b).
  *
  * Often you need to create a string from scratch with the printf-alike
@@ -643,8 +643,8 @@ void sdstoupper(sds s) {
  *
  * Return value:
  *
- *     1 if s1 > s2.
- *    -1 if s1 < s2.
+ *     positive if s1 > s2.
+ *     negative if s1 < s2.
  *     0 if s1 and s2 are exactly the same binary string.
  *
  * If two strings share exactly the same prefix, but one of the two has