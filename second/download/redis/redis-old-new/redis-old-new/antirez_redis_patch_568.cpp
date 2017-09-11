@@ -71,7 +71,7 @@ sds sdsempty(void) {
     return sdsnewlen("",0);
 }
 
-/* Create a new sds string starting from a null termined C string. */
+/* Create a new sds string starting from a null terminated C string. */
 sds sdsnew(const char *init) {
     size_t initlen = (init == NULL) ? 0 : strlen(init);
     return sdsnewlen(init, initlen);
@@ -557,7 +557,7 @@ sds sdscatfmt(sds s, char const *fmt, ...) {
  * Example:
  *
  * s = sdsnew("AA...AA.a.aa.aHelloWorld     :::");
- * s = sdstrim(s,"A. :");
+ * s = sdstrim(s,"Aa. :");
  * printf("%s\n", s);
  *
  * Output will be just "Hello World".
@@ -1098,6 +1098,7 @@ int sdsTest(int argc, char *argv[]) {
             unsigned int oldfree;
 
             sdsfree(x);
+            sdsfree(y);
             x = sdsnew("0");
             sh = (void*) (x-(sizeof(struct sdshdr)));
             test_cond("sdsnew() free/len buffers", sh->len == 1 && sh->free == 0);
@@ -1110,6 +1111,8 @@ int sdsTest(int argc, char *argv[]) {
             test_cond("sdsIncrLen() -- content", x[0] == '0' && x[1] == '1');
             test_cond("sdsIncrLen() -- len", sh->len == 2);
             test_cond("sdsIncrLen() -- free", sh->free == oldfree-1);
+
+            sdsfree(x);
         }
     }
     test_report()