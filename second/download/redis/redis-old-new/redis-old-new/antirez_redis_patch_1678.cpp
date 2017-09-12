@@ -205,14 +205,20 @@ void redisLogRaw(int level, const char *msg) {
     time_t now = time(NULL);
     FILE *fp;
     char buf[64];
+    int rawmode = (level & REDIS_LOG_RAW);
 
+    level &= 0xff; /* clear flags */
     if (level < server.verbosity) return;
 
     fp = (server.logfile == NULL) ? stdout : fopen(server.logfile,"a");
     if (!fp) return;
 
-    strftime(buf,sizeof(buf),"%d %b %H:%M:%S",localtime(&now));
-    fprintf(fp,"[%d] %s %c %s\n",(int)getpid(),buf,c[level],msg);
+    if (rawmode) {
+        fprintf(fp,"%s",msg);
+    } else {
+        strftime(buf,sizeof(buf),"%d %b %H:%M:%S",localtime(&now));
+        fprintf(fp,"[%d] %s %c %s\n",(int)getpid(),buf,c[level],msg);
+    }
     fflush(fp);
 
     if (server.logfile) fclose(fp);
@@ -227,7 +233,7 @@ void redisLog(int level, const char *fmt, ...) {
     va_list ap;
     char msg[REDIS_MAX_LOGMSG_LEN];
 
-    if (level < server.verbosity) return;
+    if ((level&0xff) < server.verbosity) return;
 
     va_start(ap, fmt);
     vsnprintf(msg, sizeof(msg), fmt, ap);
@@ -1715,6 +1721,23 @@ void usage() {
     exit(1);
 }
 
+void redisAsciiArt(void) {
+#include "asciilogo.h"
+    char *buf = zmalloc(1024*16);
+
+    snprintf(buf,1024*16,ascii_logo,
+        REDIS_VERSION,
+        redisGitSHA1(),
+        strtol(redisGitDirty(),NULL,10) > 0,
+        (sizeof(long) == 8) ? "64" : "32",
+        server.cluster_enabled ? "cluster" : "stand alone",
+        server.port,
+        (long) getpid()
+    );
+    redisLogRaw(REDIS_NOTICE|REDIS_LOG_RAW,buf);
+    zfree(buf);
+}
+
 int main(int argc, char **argv) {
     long long start;
 
@@ -1733,6 +1756,7 @@ int main(int argc, char **argv) {
     if (server.daemonize) daemonize();
     initServer();
     if (server.daemonize) createPidFile();
+    redisAsciiArt();
     redisLog(REDIS_NOTICE,"Server started, Redis version " REDIS_VERSION);
 #ifdef __linux__
     linuxOvercommitMemoryWarning();