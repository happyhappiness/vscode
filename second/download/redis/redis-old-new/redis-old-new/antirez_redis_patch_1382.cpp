@@ -48,15 +48,24 @@ robj *createStringObjectFromLongLong(long long value) {
 /* Note: this function is defined into object.c since here it is where it
  * belongs but it is actually designed to be used just for INCRBYFLOAT */
 robj *createStringObjectFromLongDouble(long double value) {
-    char buf[256];
+    char buf[256], *p;
     int len;
 
     /* We use 17 digits precision since with 128 bit floats that precision
      * after rouding is able to represent most small decimal numbers in a way
      * that is "non surprising" for the user (that is, most small decimal
      * numbers will be represented in a way that when converted back into
      * a string are exactly the same as what the user typed.) */
-    len = snprintf(buf,sizeof(buf),"%.17Lg", value);
+    len = snprintf(buf,sizeof(buf),"%.17Lf", value);
+    /* Now remove trailing zeroes after the '.' */
+    if ((p = strchr(buf,'.')) != NULL) {
+        p = buf+len-1;
+        while(*p == '0') {
+            p--;
+            len--;
+        }
+        if (*p == '.') len--;
+    }
     return createStringObject(buf,len);
 }
 