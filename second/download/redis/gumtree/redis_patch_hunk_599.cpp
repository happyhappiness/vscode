  * On failure the function logs a warning on the Redis log. */
 void sentinelFlushConfig(void) {
     int fd = -1;
     int saved_hz = server.hz;
     int rewrite_status;
 
-    server.hz = REDIS_DEFAULT_HZ;
+    server.hz = CONFIG_DEFAULT_HZ;
     rewrite_status = rewriteConfig(server.configfile);
     server.hz = saved_hz;
 
     if (rewrite_status == -1) goto werr;
     if ((fd = open(server.configfile,O_RDONLY)) == -1) goto werr;
     if (fsync(fd) == -1) goto werr;
     if (close(fd) == EOF) goto werr;
     return;
 
 werr:
     if (fd != -1) close(fd);
-    redisLog(REDIS_WARNING,"WARNING: Sentinel was not able to save the new configuration on disk!!!: %s", strerror(errno));
+    serverLog(LL_WARNING,"WARNING: Sentinel was not able to save the new configuration on disk!!!: %s", strerror(errno));
 }
 
 /* ====================== hiredis connection handling ======================= */
 
-/* Completely disconnect a hiredis link from an instance. */
-void sentinelKillLink(sentinelRedisInstance *ri, redisAsyncContext *c) {
-    if (ri->cc == c) {
-        ri->cc = NULL;
-        ri->pending_commands = 0;
-    }
-    if (ri->pc == c) ri->pc = NULL;
-    c->data = NULL;
-    ri->flags |= SRI_DISCONNECTED;
-    redisAsyncFree(c);
-}
-
-/* This function takes a hiredis context that is in an error condition
- * and make sure to mark the instance as disconnected performing the
- * cleanup needed.
- *
- * Note: we don't free the hiredis context as hiredis will do it for us
- * for async connections. */
-void sentinelDisconnectInstanceFromContext(const redisAsyncContext *c) {
-    sentinelRedisInstance *ri = c->data;
-    int pubsub;
-
-    if (ri == NULL) return; /* The instance no longer exists. */
-
-    pubsub = (ri->pc == c);
-    sentinelEvent(REDIS_DEBUG, pubsub ? "-pubsub-link" : "-cmd-link", ri,
-        "%@ #%s", c->errstr);
-    if (pubsub)
-        ri->pc = NULL;
-    else
-        ri->cc = NULL;
-    ri->flags |= SRI_DISCONNECTED;
-}
-
-void sentinelLinkEstablishedCallback(const redisAsyncContext *c, int status) {
-    if (status != REDIS_OK) {
-        sentinelDisconnectInstanceFromContext(c);
-    } else {
-        sentinelRedisInstance *ri = c->data;
-        int pubsub = (ri->pc == c);
-
-        sentinelEvent(REDIS_DEBUG, pubsub ? "+pubsub-link" : "+cmd-link", ri,
-            "%@");
-    }
-}
-
-void sentinelDisconnectCallback(const redisAsyncContext *c, int status) {
-    REDIS_NOTUSED(status);
-    sentinelDisconnectInstanceFromContext(c);
-}
-
 /* Send the AUTH command with the specified master password if needed.
  * Note that for slaves the password set for the master is used.
  *
  * We don't check at all if the command was successfully transmitted
  * to the instance as if it fails Sentinel will detect the instance down,
  * will disconnect and reconnect the link and so forth. */
 void sentinelSendAuthIfNeeded(sentinelRedisInstance *ri, redisAsyncContext *c) {
     char *auth_pass = (ri->flags & SRI_MASTER) ? ri->auth_pass :
                                                  ri->master->auth_pass;
 
     if (auth_pass) {
-        if (redisAsyncCommand(c, sentinelDiscardReplyCallback, NULL, "AUTH %s",
-            auth_pass) == REDIS_OK) ri->pending_commands++;
+        if (redisAsyncCommand(c, sentinelDiscardReplyCallback, ri, "AUTH %s",
+            auth_pass) == C_OK) ri->link->pending_commands++;
     }
 }
 
 /* Use CLIENT SETNAME to name the connection in the Redis instance as
  * sentinel-<first_8_chars_of_runid>-<connection_type>
  * The connection type is "cmd" or "pubsub" as specified by 'type'.
  *
  * This makes it possible to list all the sentinel instances connected
  * to a Redis servewr with CLIENT LIST, grepping for a specific name format. */
 void sentinelSetClientName(sentinelRedisInstance *ri, redisAsyncContext *c, char *type) {
     char name[64];
 
-    snprintf(name,sizeof(name),"sentinel-%.8s-%s",server.runid,type);
-    if (redisAsyncCommand(c, sentinelDiscardReplyCallback, NULL,
-        "CLIENT SETNAME %s", name) == REDIS_OK)
+    snprintf(name,sizeof(name),"sentinel-%.8s-%s",sentinel.myid,type);
+    if (redisAsyncCommand(c, sentinelDiscardReplyCallback, ri,
+        "CLIENT SETNAME %s", name) == C_OK)
     {
-        ri->pending_commands++;
+        ri->link->pending_commands++;
     }
 }
 
-/* Create the async connections for the specified instance if the instance
- * is disconnected. Note that the SRI_DISCONNECTED flag is set even if just
+/* Create the async connections for the instance link if the link
+ * is disconnected. Note that link->disconnected is true even if just
  * one of the two links (commands and pub/sub) is missing. */
 void sentinelReconnectInstance(sentinelRedisInstance *ri) {
-    if (!(ri->flags & SRI_DISCONNECTED)) return;
+    if (ri->link->disconnected == 0) return;
+    if (ri->addr->port == 0) return; /* port == 0 means invalid address. */
+    instanceLink *link = ri->link;
+    mstime_t now = mstime();
+
+    if (now - ri->link->last_reconn_time < SENTINEL_PING_PERIOD) return;
+    ri->link->last_reconn_time = now;
 
     /* Commands connection. */
-    if (ri->cc == NULL) {
-        ri->cc = redisAsyncConnectBind(ri->addr->ip,ri->addr->port,REDIS_BIND_ADDR);
-        if (ri->cc->err) {
-            sentinelEvent(REDIS_DEBUG,"-cmd-link-reconnection",ri,"%@ #%s",
-                ri->cc->errstr);
-            sentinelKillLink(ri,ri->cc);
+    if (link->cc == NULL) {
+        link->cc = redisAsyncConnectBind(ri->addr->ip,ri->addr->port,NET_FIRST_BIND_ADDR);
+        if (link->cc->err) {
+            sentinelEvent(LL_DEBUG,"-cmd-link-reconnection",ri,"%@ #%s",
+                link->cc->errstr);
+            instanceLinkCloseConnection(link,link->cc);
         } else {
-            ri->cc_conn_time = mstime();
-            ri->cc->data = ri;
-            redisAeAttach(server.el,ri->cc);
-            redisAsyncSetConnectCallback(ri->cc,
-                                            sentinelLinkEstablishedCallback);
-            redisAsyncSetDisconnectCallback(ri->cc,
-                                            sentinelDisconnectCallback);
-            sentinelSendAuthIfNeeded(ri,ri->cc);
-            sentinelSetClientName(ri,ri->cc,"cmd");
+            link->cc_conn_time = mstime();
+            link->cc->data = link;
+            redisAeAttach(server.el,link->cc);
+            redisAsyncSetConnectCallback(link->cc,
+                    sentinelLinkEstablishedCallback);
+            redisAsyncSetDisconnectCallback(link->cc,
+                    sentinelDisconnectCallback);
+            sentinelSendAuthIfNeeded(ri,link->cc);
+            sentinelSetClientName(ri,link->cc,"cmd");
 
             /* Send a PING ASAP when reconnecting. */
             sentinelSendPing(ri);
         }
     }
     /* Pub / Sub */
-    if ((ri->flags & (SRI_MASTER|SRI_SLAVE)) && ri->pc == NULL) {
-        ri->pc = redisAsyncConnectBind(ri->addr->ip,ri->addr->port,REDIS_BIND_ADDR);
-        if (ri->pc->err) {
-            sentinelEvent(REDIS_DEBUG,"-pubsub-link-reconnection",ri,"%@ #%s",
-                ri->pc->errstr);
-            sentinelKillLink(ri,ri->pc);
+    if ((ri->flags & (SRI_MASTER|SRI_SLAVE)) && link->pc == NULL) {
+        link->pc = redisAsyncConnectBind(ri->addr->ip,ri->addr->port,NET_FIRST_BIND_ADDR);
+        if (link->pc->err) {
+            sentinelEvent(LL_DEBUG,"-pubsub-link-reconnection",ri,"%@ #%s",
+                link->pc->errstr);
+            instanceLinkCloseConnection(link,link->pc);
         } else {
             int retval;
 
-            ri->pc_conn_time = mstime();
-            ri->pc->data = ri;
-            redisAeAttach(server.el,ri->pc);
-            redisAsyncSetConnectCallback(ri->pc,
-                                            sentinelLinkEstablishedCallback);
-            redisAsyncSetDisconnectCallback(ri->pc,
-                                            sentinelDisconnectCallback);
-            sentinelSendAuthIfNeeded(ri,ri->pc);
-            sentinelSetClientName(ri,ri->pc,"pubsub");
+            link->pc_conn_time = mstime();
+            link->pc->data = link;
+            redisAeAttach(server.el,link->pc);
+            redisAsyncSetConnectCallback(link->pc,
+                    sentinelLinkEstablishedCallback);
+            redisAsyncSetDisconnectCallback(link->pc,
+                    sentinelDisconnectCallback);
+            sentinelSendAuthIfNeeded(ri,link->pc);
+            sentinelSetClientName(ri,link->pc,"pubsub");
             /* Now we subscribe to the Sentinels "Hello" channel. */
-            retval = redisAsyncCommand(ri->pc,
-                sentinelReceiveHelloMessages, NULL, "SUBSCRIBE %s",
+            retval = redisAsyncCommand(link->pc,
+                sentinelReceiveHelloMessages, ri, "SUBSCRIBE %s",
                     SENTINEL_HELLO_CHANNEL);
-            if (retval != REDIS_OK) {
+            if (retval != C_OK) {
                 /* If we can't subscribe, the Pub/Sub connection is useless
                  * and we can simply disconnect it and try again. */
-                sentinelKillLink(ri,ri->pc);
+                instanceLinkCloseConnection(link,link->pc);
                 return;
             }
         }
     }
-    /* Clear the DISCONNECTED flags only if we have both the connections
+    /* Clear the disconnected status only if we have both the connections
      * (or just the commands connection if this is a sentinel instance). */
-    if (ri->cc && (ri->flags & SRI_SENTINEL || ri->pc))
-        ri->flags &= ~SRI_DISCONNECTED;
+    if (link->cc && (ri->flags & SRI_SENTINEL || link->pc))
+        link->disconnected = 0;
 }
 
 /* ======================== Redis instances pinging  ======================== */
 
 /* Return true if master looks "sane", that is:
  * 1) It is actually a master in the current configuration.
