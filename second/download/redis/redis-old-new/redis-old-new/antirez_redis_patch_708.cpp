@@ -295,7 +295,7 @@ sds sdscpy(sds s, const char *t) {
  * conversion. 's' must point to a string with room for at least
  * SDS_LLSTR_SIZE bytes.
  *
- * The function returns the lengh of the null-terminated string
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