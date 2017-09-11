@@ -385,7 +385,7 @@ int string2l(const char *s, size_t slen, long *lval) {
 }
 
 /* Convert a double to a string representation. Returns the number of bytes
- * required. The representation should always be parsable by stdtod(3). */
+ * required. The representation should always be parsable by strtod(3). */
 int d2string(char *buf, size_t len, double value) {
     if (isnan(value)) {
         len = snprintf(buf,len,"nan");