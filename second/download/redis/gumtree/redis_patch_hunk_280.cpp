  * After the call, the modified sds string is no longer valid and all the
  * references must be substituted with the new pointer returned by the call.
  *
  * Example:
  *
  * s = sdsnew("AA...AA.a.aa.aHelloWorld     :::");
- * s = sdstrim(s,"Aa. :");
+ * s = sdstrim(s,"A. :");
  * printf("%s\n", s);
  *
  * Output will be just "Hello World".
  */
 sds sdstrim(sds s, const char *cset) {
     struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
