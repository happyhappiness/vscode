@@ -186,23 +186,22 @@ struct redisCommand readonlyCommandTable[] = {
 void redisLog(int level, const char *fmt, ...) {
     va_list ap;
     FILE *fp;
+    char *c = ".-*#";
+    char buf[64];
+    time_t now;
+
+    if (level < server.verbosity) return;
 
     fp = (server.logfile == NULL) ? stdout : fopen(server.logfile,"a");
     if (!fp) return;
 
     va_start(ap, fmt);
-    if (level >= server.verbosity) {
-        char *c = ".-*#";
-        char buf[64];
-        time_t now;
-
-        now = time(NULL);
-        strftime(buf,64,"%d %b %H:%M:%S",localtime(&now));
-        fprintf(fp,"[%d] %s %c ",(int)getpid(),buf,c[level]);
-        vfprintf(fp, fmt, ap);
-        fprintf(fp,"\n");
-        fflush(fp);
-    }
+    now = time(NULL);
+    strftime(buf,64,"%d %b %H:%M:%S",localtime(&now));
+    fprintf(fp,"[%d] %s %c ",(int)getpid(),buf,c[level]);
+    vfprintf(fp, fmt, ap);
+    fprintf(fp,"\n");
+    fflush(fp);
     va_end(ap);
 
     if (server.logfile) fclose(fp);