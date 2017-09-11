@@ -109,9 +109,11 @@ robj *createStringObjectFromLongLong(long long value) {
     return o;
 }
 
-/* Note: this function is defined into object.c since here it is where it
- * belongs but it is actually designed to be used just for INCRBYFLOAT */
-robj *createStringObjectFromLongDouble(long double value) {
+/* Create a string object from a long double. If humanfriendly is non-zero
+ * it does not use exponential format and trims trailing zeroes at the end,
+ * however this result in loss of precision. Otherwise exp format is used
+ * and the output of snprintf() is not modified. */
+robj *createStringObjectFromLongDouble(long double value, int humanfriendly) {
     char buf[256];
     int len;
 
@@ -120,15 +122,19 @@ robj *createStringObjectFromLongDouble(long double value) {
      * that is "non surprising" for the user (that is, most small decimal
      * numbers will be represented in a way that when converted back into
      * a string are exactly the same as what the user typed.) */
-    len = snprintf(buf,sizeof(buf),"%.17Lf", value);
-    /* Now remove trailing zeroes after the '.' */
-    if (strchr(buf,'.') != NULL) {
-        char *p = buf+len-1;
-        while(*p == '0') {
-            p--;
-            len--;
+    if (humanfriendly) {
+        len = snprintf(buf,sizeof(buf),"%.17Lf", value);
+        /* Now remove trailing zeroes after the '.' */
+        if (strchr(buf,'.') != NULL) {
+            char *p = buf+len-1;
+            while(*p == '0') {
+                p--;
+                len--;
+            }
+            if (*p == '.') len--;
         }
-        if (*p == '.') len--;
+    } else {
+        len = snprintf(buf,sizeof(buf),"%.17Lg", value);
     }
     return createStringObject(buf,len);
 }