 void redisLogRaw(int level, const char *msg) {
     const int syslogLevelMap[] = { LOG_DEBUG, LOG_INFO, LOG_NOTICE, LOG_WARNING };
     const char *c = ".-*#";
     FILE *fp;
     char buf[64];
     int rawmode = (level & REDIS_LOG_RAW);
+    int log_to_stdout = server.logfile[0] == '\0';
 
     level &= 0xff; /* clear flags */
     if (level < server.verbosity) return;
 
-    fp = (server.logfile == NULL) ? stdout : fopen(server.logfile,"a");
+    fp = log_to_stdout ? stdout : fopen(server.logfile,"a");
     if (!fp) return;
 
     if (rawmode) {
         fprintf(fp,"%s",msg);
     } else {
         int off;
