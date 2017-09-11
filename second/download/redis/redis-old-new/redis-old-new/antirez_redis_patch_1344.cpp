@@ -253,7 +253,6 @@ struct redisCommand redisCommandTable[] = {
 void redisLogRaw(int level, const char *msg) {
     const int syslogLevelMap[] = { LOG_DEBUG, LOG_INFO, LOG_NOTICE, LOG_WARNING };
     const char *c = ".-*#";
-    time_t now = time(NULL);
     FILE *fp;
     char buf[64];
     int rawmode = (level & REDIS_LOG_RAW);
@@ -267,7 +266,12 @@ void redisLogRaw(int level, const char *msg) {
     if (rawmode) {
         fprintf(fp,"%s",msg);
     } else {
-        strftime(buf,sizeof(buf),"%d %b %H:%M:%S",localtime(&now));
+        int off;
+        struct timeval tv;
+
+        gettimeofday(&tv,NULL);
+        off = strftime(buf,sizeof(buf),"%d %b %H:%M:%S.",localtime(&tv.tv_sec));
+        snprintf(buf+off,sizeof(buf)-off,"%03d",(int)tv.tv_usec/1000);
         fprintf(fp,"[%d] %s %c %s\n",(int)getpid(),buf,c[level],msg);
     }
     fflush(fp);