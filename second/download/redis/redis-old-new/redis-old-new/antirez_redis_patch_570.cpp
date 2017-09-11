@@ -557,7 +557,7 @@ sds sdscatfmt(sds s, char const *fmt, ...) {
  * Example:
  *
  * s = sdsnew("AA...AA.a.aa.aHelloWorld     :::");
- * s = sdstrim(s,"A. :");
+ * s = sdstrim(s,"Aa. :");
  * printf("%s\n", s);
  *
  * Output will be just "Hello World".