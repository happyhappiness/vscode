@@ -193,27 +193,30 @@ struct redisCommand readonlyCommandTable[] = {
 /*============================ Utility functions ============================ */
 
 void redisLog(int level, const char *fmt, ...) {
+    const int syslogLevelMap[] = { LOG_DEBUG, LOG_INFO, LOG_NOTICE, LOG_WARNING };
+    const char *c = ".-*#";
+    time_t now = time(NULL);
     va_list ap;
     FILE *fp;
-    char *c = ".-*#";
     char buf[64];
-    time_t now;
+    char msg[REDIS_MAX_LOGMSG_LEN];
 
     if (level < server.verbosity) return;
 
     fp = (server.logfile == NULL) ? stdout : fopen(server.logfile,"a");
     if (!fp) return;
 
     va_start(ap, fmt);
-    now = time(NULL);
-    strftime(buf,64,"%d %b %H:%M:%S",localtime(&now));
-    fprintf(fp,"[%d] %s %c ",(int)getpid(),buf,c[level]);
-    vfprintf(fp, fmt, ap);
-    fprintf(fp,"\n");
-    fflush(fp);
+    vsnprintf(msg, sizeof(msg), fmt, ap);
     va_end(ap);
 
+    strftime(buf,sizeof(buf),"%d %b %H:%M:%S",localtime(&now));
+    fprintf(fp,"[%d] %s %c %s\n",(int)getpid(),buf,c[level],msg);
+    fflush(fp);
+
     if (server.logfile) fclose(fp);
+
+    if (server.syslog_enabled) syslog(syslogLevelMap[level], "%s", msg);
 }
 
 /* Redis generally does not try to recover from out of memory conditions
@@ -762,6 +765,9 @@ void initServerConfig() {
     server.saveparams = NULL;
     server.loading = 0;
     server.logfile = NULL; /* NULL = log on standard output */
+    server.syslog_enabled = 0;
+    server.syslog_ident = zstrdup("redis");
+    server.syslog_facility = LOG_LOCAL0;
     server.glueoutputbuf = 1;
     server.daemonize = 0;
     server.appendonly = 0;
@@ -832,6 +838,11 @@ void initServer() {
     signal(SIGPIPE, SIG_IGN);
     setupSigSegvAction();
 
+    if (server.syslog_enabled) {
+        openlog(server.syslog_ident, LOG_PID | LOG_NDELAY | LOG_NOWAIT,
+            server.syslog_facility);
+    }
+
     server.mainthread = pthread_self();
     server.clients = listCreate();
     server.slaves = listCreate();