@@ -413,6 +413,17 @@ void initSentinel(void) {
     sentinel.scripts_queue = listCreate();
 }
 
+/* This function gets called when the server is in Sentinel mode, started,
+ * loaded the configuration, and is ready for normal operations. */
+void sentinelIsRunning(void) {
+    redisLog(REDIS_WARNING,"Sentinel runid is %s", server.runid);
+
+    if (server.configfile == NULL || access(server.configfile,W_OK) == -1) {
+        redisLog(REDIS_WARNING,"Sentinel started without a config file, or config file not writable. Exiting...");
+        exit(1);
+    }
+}
+
 /* ============================== sentinelAddr ============================== */
 
 /* Create a sentinelAddr object and return it on success.
@@ -2069,7 +2080,7 @@ int sentinelSendHello(sentinelRedisInstance *ri) {
 
     /* Try to obtain our own IP address. */
     if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) == -1) return REDIS_ERR;
-    if (ri->flags & SRI_DISCONNECTED) return;
+    if (ri->flags & SRI_DISCONNECTED) return REDIS_ERR;
 
     /* Format and send the Hello message. */
     snprintf(payload,sizeof(payload),