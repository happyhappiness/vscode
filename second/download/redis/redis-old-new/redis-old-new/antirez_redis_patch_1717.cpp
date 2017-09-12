@@ -192,24 +192,20 @@ struct redisCommand redisCommandTable[] = {
 
 /*============================ Utility functions ============================ */
 
-void redisLog(int level, const char *fmt, ...) {
+/* Low level logging. To use only for very big messages, otherwise
+ * redisLog() is to prefer. */
+void redisLogRaw(int level, const char *msg) {
     const int syslogLevelMap[] = { LOG_DEBUG, LOG_INFO, LOG_NOTICE, LOG_WARNING };
     const char *c = ".-*#";
     time_t now = time(NULL);
-    va_list ap;
     FILE *fp;
     char buf[64];
-    char msg[REDIS_MAX_LOGMSG_LEN];
 
     if (level < server.verbosity) return;
 
     fp = (server.logfile == NULL) ? stdout : fopen(server.logfile,"a");
     if (!fp) return;
 
-    va_start(ap, fmt);
-    vsnprintf(msg, sizeof(msg), fmt, ap);
-    va_end(ap);
-
     strftime(buf,sizeof(buf),"%d %b %H:%M:%S",localtime(&now));
     fprintf(fp,"[%d] %s %c %s\n",(int)getpid(),buf,c[level],msg);
     fflush(fp);
@@ -219,6 +215,22 @@ void redisLog(int level, const char *fmt, ...) {
     if (server.syslog_enabled) syslog(syslogLevelMap[level], "%s", msg);
 }
 
+/* Like redisLogRaw() but with printf-alike support. This is the funciton that
+ * is used across the code. The raw version is only used in order to dump
+ * the INFO output on crash. */
+void redisLog(int level, const char *fmt, ...) {
+    va_list ap;
+    char msg[REDIS_MAX_LOGMSG_LEN];
+
+    if (level < server.verbosity) return;
+
+    va_start(ap, fmt);
+    vsnprintf(msg, sizeof(msg), fmt, ap);
+    va_end(ap);
+
+    redisLogRaw(level,msg);
+}
+
 /* Redis generally does not try to recover from out of memory conditions
  * when allocating objects or strings, it is not clear if it will be possible
  * to report this condition to the client since the networking layer itself
@@ -1725,7 +1737,7 @@ void segvHandler(int sig, siginfo_t *info, void *secret) {
     redisLog(REDIS_WARNING,
         "======= Ooops! Redis %s got signal: -%d- =======", REDIS_VERSION, sig);
     infostring = genRedisInfoString("all");
-    redisLog(REDIS_WARNING, "%s",infostring);
+    redisLogRaw(REDIS_WARNING, infostring);
     /* It's not safe to sdsfree() the returned string under memory
      * corruption conditions. Let it leak as we are going to abort */
 