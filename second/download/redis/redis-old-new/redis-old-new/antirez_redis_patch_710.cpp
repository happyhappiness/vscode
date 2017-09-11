@@ -295,7 +295,7 @@ sds sdscpy(sds s, const char *t) {
  * conversion. 's' must point to a string with room for at least
  * SDS_LLSTR_SIZE bytes.
  *
- * The function returns the lenght of the null-terminated string
+ * The function returns the lengh of the null-terminated string
  * representation stored at 's'. */
 #define SDS_LLSTR_SIZE 21
 int sdsll2str(char *s, long long value) {
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