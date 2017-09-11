@@ -48,7 +48,7 @@ robj *createStringObjectFromLongLong(long long value) {
 /* Note: this function is defined into object.c since here it is where it
  * belongs but it is actually designed to be used just for INCRBYFLOAT */
 robj *createStringObjectFromLongDouble(long double value) {
-    char buf[256], *p;
+    char buf[256];
     int len;
 
     /* We use 17 digits precision since with 128 bit floats that precision
@@ -58,8 +58,8 @@ robj *createStringObjectFromLongDouble(long double value) {
      * a string are exactly the same as what the user typed.) */
     len = snprintf(buf,sizeof(buf),"%.17Lf", value);
     /* Now remove trailing zeroes after the '.' */
-    if ((p = strchr(buf,'.')) != NULL) {
-        p = buf+len-1;
+    if (strchr(buf,'.') != NULL) {
+        char *p = buf+len-1;
         while(*p == '0') {
             p--;
             len--;