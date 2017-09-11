@@ -2049,6 +2049,46 @@ void sentinelReceiveHelloMessages(redisAsyncContext *c, void *reply, void *privd
     }
 }
 
+/* Send an "Hello" message via Pub/Sub to the specified 'ri' Redis
+ * instance in order to broadcast the current configuraiton for this
+ * master, and to advertise the existence of this Sentinel at the same time.
+ *
+ * The message has the following format:
+ *
+ * sentinel_ip,sentinel_port,sentinel_runid,current_epoch,
+ * master_name,master_ip,master_port,master_config_epoch.
+ *
+ * Returns REDIS_OK if the PUBLISH was queued correctly, otherwise
+ * REDIS_ERR is returned. */
+int sentinelSendHello(sentinelRedisInstance *ri) {
+    char ip[REDIS_IP_STR_LEN];
+    char payload[REDIS_IP_STR_LEN+1024];
+    int retval;
+    sentinelRedisInstance *master = (ri->flags & SRI_MASTER) ? ri : ri->master;
+    sentinelAddr *master_addr = sentinelGetCurrentMasterAddress(master);
+
+    /* Try to obtain our own IP address. */
+    if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) == -1) return REDIS_ERR;
+
+    /* Format and send the Hello message. */
+    snprintf(payload,sizeof(payload),
+        "%s,%d,%s,%llu," /* Info about this sentinel. */
+        "%s,%s,%d,%lld", /* Info about current master. */
+        ip, server.port, server.runid,
+        (unsigned long long) sentinel.current_epoch,
+        /* --- */
+        master->name,master_addr->ip,master_addr->port,
+        master->config_epoch);
+    retval = redisAsyncCommand(ri->cc,
+        sentinelPublishReplyCallback, NULL, "PUBLISH %s %s",
+            SENTINEL_HELLO_CHANNEL,payload);
+    if (retval != REDIS_OK) return REDIS_ERR;
+    ri->pending_commands++;
+    return REDIS_OK;
+}
+
+/* Send periodic PING, INFO, and PUBLISH to the Hello channel to
+ * the specified master or slave instance. */
 void sentinelPingInstance(sentinelRedisInstance *ri) {
     mstime_t now = mstime();
     mstime_t info_period;
@@ -2096,27 +2136,7 @@ void sentinelPingInstance(sentinelRedisInstance *ri) {
                (now - ri->last_pub_time) > SENTINEL_PUBLISH_PERIOD)
     {
         /* PUBLISH hello messages to masters and slaves. */
-        char ip[REDIS_IP_STR_LEN];
-        if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) != -1) {
-            char payload[REDIS_IP_STR_LEN+1024];
-            sentinelRedisInstance *master = (ri->flags & SRI_MASTER) ?
-                                             ri : ri->master;
-            sentinelAddr *master_addr = sentinelGetCurrentMasterAddress(master);
-
-            snprintf(payload,sizeof(payload),
-                "%s,%d,%s,%llu," /* Info about this sentinel. */
-                "%s,%s,%d,%lld",    /* Info about current master. */
-                ip, server.port, server.runid,
-                (unsigned long long) sentinel.current_epoch,
-                /* --- */
-                master->name,master_addr->ip,master_addr->port,
-                master->config_epoch);
-            retval = redisAsyncCommand(ri->cc,
-                sentinelPublishReplyCallback, NULL, "PUBLISH %s %s",
-                    SENTINEL_HELLO_CHANNEL,payload);
-            if (retval != REDIS_OK) return;
-            ri->pending_commands++;
-        }
+        sentinelSendHello(ri);
     }
 }
 