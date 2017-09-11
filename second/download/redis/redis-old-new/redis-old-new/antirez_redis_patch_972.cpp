@@ -417,8 +417,13 @@ void initSentinel(void) {
 void sentinelIsRunning(void) {
     redisLog(REDIS_WARNING,"Sentinel runid is %s", server.runid);
 
-    if (server.configfile == NULL || access(server.configfile,W_OK) == -1) {
-        redisLog(REDIS_WARNING,"Sentinel started without a config file, or config file not writable. Exiting...");
+    if (server.configfile == NULL) {
+        redisLog(REDIS_WARNING,
+            "Sentinel started without a config file. Exiting...");
+    } else if (access(server.configfile,W_OK) == -1) {
+        redisLog(REDIS_WARNING,
+            "Sentinel config file %s is not writable: %s. Exiting...",
+            server.configfile,strerror(errno));
         exit(1);
     }
 }