@@ -556,7 +556,12 @@ void redisLog(int level, const char *fmt, ...)
     va_start(ap, fmt);
     if (level >= server.verbosity) {
         char *c = ".-*";
-        fprintf(fp,"%c ",c[level]);
+        char buf[64];
+        time_t now;
+
+        now = time(NULL);
+        strftime(buf,64,"%d %b %H:%M:%S",gmtime(&now));
+        fprintf(fp,"%s %c ",buf,c[level]);
         vfprintf(fp, fmt, ap);
         fprintf(fp,"\n");
         fflush(fp);