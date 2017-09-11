@@ -203,7 +203,10 @@ struct sentinelState {
     mstime_t tilt_start_time;   /* When TITL started. */
     mstime_t previous_time;     /* Last time we ran the time handler. */
     list *scripts_queue;    /* Queue of user scripts to execute. */
-    sentinelAddr *announce_addr; /* Address that is gossiped to other sentinels. */
+    char *announce_ip;      /* IP addr that is gossiped to other sentinels if
+                               not NULL. */
+    int announce_port;      /* Port that is gossiped to other sentinels if
+                               non zero. */
 } sentinel;
 
 /* A script execution job. */
@@ -426,7 +429,8 @@ void initSentinel(void) {
     sentinel.previous_time = mstime();
     sentinel.running_scripts = 0;
     sentinel.scripts_queue = listCreate();
-    sentinel.announce_addr = NULL;
+    sentinel.announce_ip = NULL;
+    sentinel.announce_port = 0;
 }
 
 /* This function gets called when the server is in Sentinel mode, started,
@@ -1427,12 +1431,12 @@ char *sentinelHandleConfiguration(char **argv, int argc) {
             return "Wrong hostname or port for sentinel.";
         }
         if (argc == 5) si->runid = sdsnew(argv[4]);
-    } else if (!strcasecmp(argv[0],"announce") && argc == 2) {
-        /* announce <host> */
-        sentinel.announce_addr = createSentinelAddr(argv[1], server.port);
-        if (sentinel.announce_addr == NULL) {
-            return "Unable to resolve host.";
-        }
+    } else if (!strcasecmp(argv[0],"announce-ip") && argc == 2) {
+        /* announce-ip <ip-address> */
+        sentinel.announce_ip = sdsnew(argv[1]);
+    } else if (!strcasecmp(argv[0],"announce-port") && argc == 2) {
+        /* announce-port <port> */
+        sentinel.announce_port = atoi(argv[1]);
     } else {
         return "Unrecognized sentinel configuration statement.";
     }
@@ -1564,6 +1568,20 @@ void rewriteConfigSentinelOption(struct rewriteConfigState *state) {
         "sentinel current-epoch %llu", (unsigned long long) sentinel.current_epoch);
     rewriteConfigRewriteLine(state,"sentinel",line,1);
 
+    /* sentinel announce-ip. */
+    if (sentinel.announce_ip) {
+        line = sdsnew("sentinel announce-ip ");
+        line = sdscatrepr(line, sentinel.announce_ip, sdslen(sentinel.announce_ip));
+        rewriteConfigRewriteLine(state,"sentinel",line,1);
+    }
+
+    /* sentinel announce-port. */
+    if (sentinel.announce_port) {
+        line = sdscatprintf(sdsempty(),"sentinel announce-port %d",
+                            sentinel.announce_port);
+        rewriteConfigRewriteLine(state,"sentinel",line,1);
+    }
+
     dictReleaseIterator(di);
 }
 
@@ -2221,30 +2239,30 @@ int sentinelSendHello(sentinelRedisInstance *ri) {
     char ip[REDIS_IP_STR_LEN];
     char payload[REDIS_IP_STR_LEN+1024];
     int retval;
-    char *announceIP;
-    int port;
+    char *announce_ip;
+    int announce_port;
     sentinelRedisInstance *master = (ri->flags & SRI_MASTER) ? ri : ri->master;
     sentinelAddr *master_addr = sentinelGetCurrentMasterAddress(master);
 
     if (ri->flags & SRI_DISCONNECTED) return REDIS_ERR;
 
     /* Use the specified announce address if specified, otherwise try to
      * obtain our own IP address. */
-    if (sentinel.announce_addr) {
-        announceIP = sentinel.announce_addr->ip;
-        port = sentinel.announce_addr->port;
+    if (sentinel.announce_ip) {
+        announce_ip = sentinel.announce_ip;
     } else {
         if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) == -1)
             return REDIS_ERR;
-        announceIP = ip;
-        port = server.port;
+        announce_ip = ip;
     }
+    announce_port = sentinel.announce_port ?
+                    sentinel.announce_port : server.port;
 
     /* Format and send the Hello message. */
     snprintf(payload,sizeof(payload),
         "%s,%d,%s,%llu," /* Info about this sentinel. */
         "%s,%s,%d,%llu", /* Info about current master. */
-        announceIP, port, server.runid,
+        announce_ip, announce_port, server.runid,
         (unsigned long long) sentinel.current_epoch,
         /* --- */
         master->name,master_addr->ip,master_addr->port,
@@ -2253,8 +2271,6 @@ int sentinelSendHello(sentinelRedisInstance *ri) {
         sentinelPublishReplyCallback, NULL, "PUBLISH %s %s",
             SENTINEL_HELLO_CHANNEL,payload);
     if (retval != REDIS_OK) return REDIS_ERR;
-    redisLog(REDIS_DEBUG, "Sentinel Send Hello ip=%s, port=%d, id=%s, epoch=%llu",
-        announceIP, port, server.runid, (unsigned long long) sentinel.current_epoch);
     ri->pending_commands++;
     return REDIS_OK;
 }