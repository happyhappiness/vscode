                 s = sdscatprintf(s,"%c",*p);
             else
                 s = sdscatprintf(s,"\\x%02x",(unsigned char)*p);
             break;
         }
         p++;
-        if (s == NULL) return NULL;
     }
     return sdscatlen(s,"\"",1);
 }
 
+/* Helper function for sdssplitargs() that returns non zero if 'c'
+ * is a valid hex digit. */
+int is_hex_digit(char c) {
+    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
+           (c >= 'A' && c <= 'F');
+}
+
+/* Helper function for sdssplitargs() that converts an hex digit into an
+ * integer from 0 to 15 */
+int hex_digit_to_int(char c) {
+    switch(c) {
+    case '0': return 0;
+    case '1': return 1;
+    case '2': return 2;
+    case '3': return 3;
+    case '4': return 4;
+    case '5': return 5;
+    case '6': return 6;
+    case '7': return 7;
+    case '8': return 8;
+    case '9': return 9;
+    case 'a': case 'A': return 10;
+    case 'b': case 'B': return 11;
+    case 'c': case 'C': return 12;
+    case 'd': case 'D': return 13;
+    case 'e': case 'E': return 14;
+    case 'f': case 'F': return 15;
+    default: return 0;
+    }
+}
+
 /* Split a line into arguments, where every argument can be in the
  * following programming-language REPL-alike form:
  *
  * foo bar "newline are supported\n" and "\xff\x00otherstuff"
  *
  * The number of arguments is stored into *argc, and an array
- * of sds is returned. The caller should sdsfree() all the returned
- * strings and finally free() the array itself.
+ * of sds is returned.
+ *
+ * The caller should free the resulting array of sds strings with
+ * sdsfreesplitres().
  *
  * Note that sdscatrepr() is able to convert back a string into
  * a quoted string in the same format sdssplitargs() is able to parse.
+ *
+ * The function returns the allocated tokens on success, even when the
+ * input string is empty, or NULL if the input contains unbalanced
+ * quotes or closed quotes followed by non space characters
+ * as in: "foo"bar or "foo'
  */
-sds *sdssplitargs(char *line, int *argc) {
-    char *p = line;
+sds *sdssplitargs(const char *line, int *argc) {
+    const char *p = line;
     char *current = NULL;
-    char **vector = NULL, **_vector = NULL;
+    char **vector = NULL;
 
     *argc = 0;
     while(1) {
         /* skip blanks */
         while(*p && isspace(*p)) p++;
         if (*p) {
             /* get a token */
-            int inq=0; /* set to 1 if we are in "quotes" */
+            int inq=0;  /* set to 1 if we are in "quotes" */
+            int insq=0; /* set to 1 if we are in 'single quotes' */
             int done=0;
 
-            if (current == NULL) {
-                current = sdsempty();
-                if (current == NULL) goto err;
-            }
-
+            if (current == NULL) current = sdsempty();
             while(!done) {
                 if (inq) {
-                    if (*p == '\\' && *(p+1)) {
+                    if (*p == '\\' && *(p+1) == 'x' &&
+                                             is_hex_digit(*(p+2)) &&
+                                             is_hex_digit(*(p+3)))
+                    {
+                        unsigned char byte;
+
+                        byte = (hex_digit_to_int(*(p+2))*16)+
+                                hex_digit_to_int(*(p+3));
+                        current = sdscatlen(current,(char*)&byte,1);
+                        p += 3;
+                    } else if (*p == '\\' && *(p+1)) {
                         char c;
 
                         p++;
                         switch(*p) {
                         case 'n': c = '\n'; break;
                         case 'r': c = '\r'; break;
