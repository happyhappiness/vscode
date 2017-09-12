@@ -671,7 +671,7 @@ static void redisLog(int level, const char *fmt, ...) {
         time_t now;
 
         now = time(NULL);
-        strftime(buf,64,"%d %b %H:%M:%S",gmtime(&now));
+        strftime(buf,64,"%d %b %H:%M:%S",localtime(&now));
         fprintf(fp,"%s %c ",buf,c[level]);
         vfprintf(fp, fmt, ap);
         fprintf(fp,"\n");