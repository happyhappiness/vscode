@@ -203,6 +203,7 @@ struct sentinelState {
     mstime_t tilt_start_time;   /* When TITL started. */
     mstime_t previous_time;     /* Last time we ran the time handler. */
     list *scripts_queue;    /* Queue of user scripts to execute. */
+    sentinelAddr *announce_addr; /* Address that is gossiped to other sentinels. */
 } sentinel;
 
 /* A script execution job. */
@@ -425,6 +426,7 @@ void initSentinel(void) {
     sentinel.previous_time = mstime();
     sentinel.running_scripts = 0;
     sentinel.scripts_queue = listCreate();
+    sentinel.announce_addr = NULL;
 }
 
 /* This function gets called when the server is in Sentinel mode, started,
@@ -1425,6 +1427,12 @@ char *sentinelHandleConfiguration(char **argv, int argc) {
             return "Wrong hostname or port for sentinel.";
         }
         if (argc == 5) si->runid = sdsnew(argv[4]);
+    } else if (!strcasecmp(argv[0],"announce") && argc == 2) {
+        /* announce <host> */
+        sentinel.announce_addr = createSentinelAddr(argv[1], server.port);
+        if (sentinel.announce_addr == NULL) {
+            return "Unable to resolve host.";
+        }
     } else {
         return "Unrecognized sentinel configuration statement.";
     }
@@ -2213,19 +2221,30 @@ int sentinelSendHello(sentinelRedisInstance *ri) {
     char ip[REDIS_IP_STR_LEN];
     char payload[REDIS_IP_STR_LEN+1024];
     int retval;
+    char *announceIP;
+    int port;
     sentinelRedisInstance *master = (ri->flags & SRI_MASTER) ? ri : ri->master;
     sentinelAddr *master_addr = sentinelGetCurrentMasterAddress(master);
 
     if (ri->flags & SRI_DISCONNECTED) return REDIS_ERR;
 
-    /* Try to obtain our own IP address. */
-    if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) == -1) return REDIS_ERR;
+    /* Use the specified announce address if specified, otherwise try to
+     * obtain our own IP address. */
+    if (sentinel.announce_addr) {
+        announceIP = sentinel.announce_addr->ip;
+        port = sentinel.announce_addr->port;
+    } else {
+        if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) == -1)
+            return REDIS_ERR;
+        announceIP = ip;
+        port = server.port;
+    }
 
     /* Format and send the Hello message. */
     snprintf(payload,sizeof(payload),
         "%s,%d,%s,%llu," /* Info about this sentinel. */
         "%s,%s,%d,%llu", /* Info about current master. */
-        ip, server.port, server.runid,
+        announceIP, port, server.runid,
         (unsigned long long) sentinel.current_epoch,
         /* --- */
         master->name,master_addr->ip,master_addr->port,
@@ -2234,6 +2253,8 @@ int sentinelSendHello(sentinelRedisInstance *ri) {
         sentinelPublishReplyCallback, NULL, "PUBLISH %s %s",
             SENTINEL_HELLO_CHANNEL,payload);
     if (retval != REDIS_OK) return REDIS_ERR;
+    redisLog(REDIS_DEBUG, "Sentinel Send Hello ip=%s, port=%d, id=%s, epoch=%llu",
+        announceIP, port, server.runid, (unsigned long long) sentinel.current_epoch);
     ri->pending_commands++;
     return REDIS_OK;
 }