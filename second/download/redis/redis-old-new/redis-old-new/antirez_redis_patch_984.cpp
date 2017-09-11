@@ -1086,6 +1086,9 @@ int processMultibulkBuffer(redisClient *c) {
 void processInputBuffer(redisClient *c) {
     /* Keep processing while there is something in the input buffer */
     while(sdslen(c->querybuf)) {
+        /* Return if clients are paused. */
+        if (!(c->flags & REDIS_SLAVE) && clientsArePaused()) return;
+
         /* Immediately abort if the client is in the middle of something. */
         if (c->flags & REDIS_BLOCKED) return;
 
@@ -1373,6 +1376,13 @@ void clientCommand(redisClient *c) {
             addReplyBulk(c,c->name);
         else
             addReply(c,shared.nullbulk);
+    } else if (!strcasecmp(c->argv[1]->ptr,"pause") && c->argc == 3) {
+        long long duration;
+
+        if (getTimeoutFromObjectOrReply(c,c->argv[2],&duration,UNIT_MILLISECONDS)
+                                        != REDIS_OK) return;
+        pauseClients(duration);
+        addReply(c,shared.ok);
     } else {
         addReplyError(c, "Syntax error, try CLIENT (LIST | KILL ip:port | GETNAME | SETNAME connection-name)");
     }
@@ -1555,3 +1565,49 @@ void flushSlavesOutputBuffers(void) {
         }
     }
 }
+
+/* Pause clients up to the specified unixtime (in ms). While clients
+ * are paused no command is processed from clients, so the data set can't
+ * change during that time.
+ *
+ * However while this function pauses normal and Pub/Sub clients, slaves are
+ * still served, so this function can be used on server upgrades where it is
+ * required that slaves process the latest bytes from the replication stream
+ * before being turned to masters.
+ *
+ * This function is also internally used by Redis Cluster for the manual
+ * failover procedure implemented by CLUSTER FAILOVER.
+ *
+ * The function always succeed, even if there is already a pause in progress.
+ * In such a case, the pause is extended if the duration is more than the
+ * time left for the previous duration. However if the duration is smaller
+ * than the time left for the previous pause, no change is made to the
+ * left duration. */
+void pauseClients(mstime_t end) {
+    if (!server.clients_paused || end > server.clients_pause_end_time)
+        server.clients_pause_end_time = end;
+    server.clients_paused = 1;
+}
+
+/* Return non-zero if clients are currently paused. As a side effect the
+ * function checks if the pause time was reached and clear it. */
+int clientsArePaused(void) {
+    if (server.clients_paused && server.clients_pause_end_time < server.mstime) {
+        listNode *ln;
+        listIter li;
+        redisClient *c;
+
+        server.clients_paused = 0;
+
+        /* Put all the clients in the unblocked clients queue in order to
+         * force the re-processing of the input buffer if any. */
+        listRewind(server.clients,&li);
+        while ((ln = listNext(&li)) != NULL) {
+            c = listNodeValue(ln);
+
+            if (c->flags & REDIS_SLAVE) continue;
+            listAddNodeTail(server.unblocked_clients,c);
+        }
+    }
+    return server.clients_paused;
+}