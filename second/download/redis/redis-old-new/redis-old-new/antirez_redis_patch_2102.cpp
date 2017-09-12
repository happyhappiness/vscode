@@ -3513,7 +3513,10 @@ static int rdbSaveDoubleValue(FILE *fp, double val) {
         len = 1;
         buf[0] = (val < 0) ? 255 : 254;
     } else {
-        snprintf((char*)buf+1,sizeof(buf)-1,"%.17g",val);
+        if (val == ((long long)val))
+            ll2string((char*)buf+1,sizeof(buf),(long long)val);
+        else
+            snprintf((char*)buf+1,sizeof(buf)-1,"%.17g",val);
         buf[0] = strlen((char*)buf+1);
         len = buf[0]+1;
     }