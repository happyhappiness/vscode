@@ -521,12 +521,12 @@ int ld2string(char *buf, size_t len, long double value, int humanfriendly) {
         if (l+1 > len) return 0; /* No room. */
         /* Now remove trailing zeroes after the '.' */
         if (strchr(buf,'.') != NULL) {
-            char *p = buf+len-1;
+            char *p = buf+l-1;
             while(*p == '0') {
                 p--;
-                len--;
+                l--;
             }
-            if (*p == '.') len--;
+            if (*p == '.') l--;
         }
     } else {
         l = snprintf(buf,len,"%.17Lg", value);