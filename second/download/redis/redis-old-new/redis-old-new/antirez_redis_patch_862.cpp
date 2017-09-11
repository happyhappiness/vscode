@@ -398,7 +398,7 @@ int rdbSaveDoubleValue(rio *rdb, double val) {
         double min = -4503599627370495; /* (2^52)-1 */
         double max = 4503599627370496; /* -(2^52) */
         if (val > min && val < max && val == ((double)((long long)val)))
-            ll2string((char*)buf+1,sizeof(buf),(long long)val);
+            ll2string((char*)buf+1,sizeof(buf)-1,(long long)val);
         else
 #endif
             snprintf((char*)buf+1,sizeof(buf)-1,"%.17g",val);