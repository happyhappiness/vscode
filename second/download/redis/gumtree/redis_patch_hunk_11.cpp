     } while(v);
     if (value < 0) *p-- = '-';
     p++;
     return sdsnewlen(p,32-(p-buf));
 }
 
-sds sdscatrepr(sds s, char *p, size_t len) {
+/* Append to the sds string "s" an escaped string representation where
+ * all the non-printable characters (tested with isprint()) are turned into
+ * escapes in the form "\n\r\a...." or "\x<hex-number>".
+ *
+ * After the call, the modified sds string is no longer valid and all the
+ * references must be substituted with the new pointer returned by the call. */
+sds sdscatrepr(sds s, const char *p, size_t len) {
     s = sdscatlen(s,"\"",1);
-    if (s == NULL) return NULL;
-
     while(len--) {
         switch(*p) {
         case '\\':
         case '"':
             s = sdscatprintf(s,"\\%c",*p);
             break;
