@@ -38,6 +38,7 @@
 #include <sys/time.h>
 #include <sys/resource.h>
 #include <sys/wait.h>
+#include <sys/param.h>
 
 void aofUpdateCurrentSize(void);
 void aofClosePipes(void);
@@ -234,11 +235,20 @@ void stopAppendOnly(void) {
 /* Called when the user switches from "appendonly no" to "appendonly yes"
  * at runtime using the CONFIG command. */
 int startAppendOnly(void) {
+    char cwd[MAXPATHLEN]; /* Current working dir path for error messages. */
+
     server.aof_last_fsync = server.unixtime;
     server.aof_fd = open(server.aof_filename,O_WRONLY|O_APPEND|O_CREAT,0644);
     serverAssert(server.aof_state == AOF_OFF);
     if (server.aof_fd == -1) {
-        serverLog(LL_WARNING,"Redis needs to enable the AOF but can't open the append only file: %s",strerror(errno));
+        char *cwdp = getcwd(cwd,MAXPATHLEN);
+
+        serverLog(LL_WARNING,
+            "Redis needs to enable the AOF but can't open the "
+            "append only file %s (in server root dir %s): %s",
+            server.aof_filename,
+            cwdp ? cwdp : "unknown",
+            strerror(errno));
         return C_ERR;
     }
     if (rewriteAppendOnlyFileBackground() == C_ERR) {
@@ -1413,7 +1423,10 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
         latencyStartMonitor(latency);
         if (rename(tmpfile,server.aof_filename) == -1) {
             serverLog(LL_WARNING,
-                "Error trying to rename the temporary AOF file: %s", strerror(errno));
+                "Error trying to rename the temporary AOF file %s into %s: %s",
+                tmpfile,
+                server.aof_filename,
+                strerror(errno));
             close(newfd);
             if (oldfd != -1) close(oldfd);
             goto cleanup;