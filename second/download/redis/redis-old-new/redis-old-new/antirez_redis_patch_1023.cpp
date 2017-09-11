@@ -39,6 +39,7 @@
 
 void replicationDiscardCachedMaster(void);
 void replicationResurrectCachedMaster(int newfd);
+void replicationSendAck(void);
 
 /* ---------------------------------- MASTER -------------------------------- */
 
@@ -560,6 +561,11 @@ void replconfCommand(redisClient *c) {
             c->repl_ack_time = server.unixtime;
             /* Note: this command does not reply anything! */
             return;
+        } else if (!strcasecmp(c->argv[j]->ptr,"getack")) {
+            /* REPLCONF GETACK is used in order to request an ACK ASAP
+             * to the slave. */
+            if (server.masterhost && server.master) replicationSendAck();
+            /* Note: this command does not reply anything! */
         } else {
             addReplyErrorFormat(c,"Unrecognized REPLCONF option: %s",
                 (char*)c->argv[j]->ptr);
@@ -1495,7 +1501,136 @@ int replicationScriptCacheExists(sds sha1) {
     return dictFind(server.repl_scriptcache_dict,sha1) != NULL;
 }
 
-/* --------------------------- REPLICATION CRON  ----------------------------- */
+/* ----------------------- SYNCHRONOUS REPLICATION --------------------------
+ * Redis synchronous replication design can be summarized in points:
+ *
+ * - Redis masters have a global replication offset, used by PSYNC.
+ * - Master increment the offset every time new commands are sent to slaves.
+ * - Slaves ping back masters with the offset processed so far.
+ *
+ * So synchronous replication adds a new WAIT command in the form:
+ *
+ *   WAIT <num_replicas> <milliseconds_timeout>
+ *
+ * That returns the number of replicas that processed the query when
+ * we finally have at least num_replicas, or when the timeout was
+ * reached.
+ *
+ * The command is implemented in this way:
+ *
+ * - Every time a client processes a command, we remember the replication
+ *   offset after sending that command to the slaves.
+ * - When WAIT is called, we ask slaves to send an acknowledgement ASAP.
+ *   The client is blocked at the same time (see blocked.c).
+ * - Once we receive enough ACKs for a given offset or when the timeout
+ *   is reached, the WAIT command is unblocked and the reply sent to the
+ *   client.
+ */
+
+/* This just set a flag so that we broadcast a REPLCONF GETACK command
+ * to all the slaves in the beforeSleep() function. Note that this way
+ * we "group" all the clients that want to wait for synchronouns replication
+ * in a given event loop iteration, and send a single GETACK for them all. */
+void replicationRequestAckFromSlaves(void) {
+    server.get_ack_from_slaves = 1;
+}
+
+/* Return the number of slaves that already acknowledged the specified
+ * replication offset. */
+int replicationCountAcksByOffset(long long offset) {
+    listIter li;
+    listNode *ln;
+    int count = 0;
+
+    listRewind(server.slaves,&li);
+    while((ln = listNext(&li))) {
+        redisClient *slave = ln->value;
+
+        if (slave->replstate != REDIS_REPL_ONLINE) continue;
+        if (slave->repl_ack_off >= offset) count++;
+    }
+    return count;
+}
+
+/* WAIT for N replicas to acknowledge the processing of our latest
+ * write command (and all the previous commands). */
+void waitCommand(redisClient *c) {
+    mstime_t timeout;
+    long numreplicas, ackreplicas;
+    long long offset = c->woff;
+
+    /* Argument parsing. */
+    if (getLongFromObjectOrReply(c,c->argv[1],&numreplicas,NULL) != REDIS_OK)
+        return;
+    if (getTimeoutFromObjectOrReply(c,c->argv[2],&timeout,UNIT_MILLISECONDS)
+        != REDIS_OK) return;
+
+    /* First try without blocking at all. */
+    ackreplicas = replicationCountAcksByOffset(c->woff);
+    if (ackreplicas >= numreplicas || c->flags & REDIS_MULTI) {
+        addReplyLongLong(c,ackreplicas);
+        return;
+    }
+
+    /* Otherwise block the client and put it into our list of clients
+     * waiting for ack from slaves. */
+    c->bpop.timeout = timeout;
+    c->bpop.reploffset = offset;
+    c->bpop.numreplicas = numreplicas;
+    listAddNodeTail(server.clients_waiting_acks,c);
+    blockClient(c,REDIS_BLOCKED_WAIT);
+
+    /* Make sure that the server will send an ACK request to all the slaves
+     * before returning to the event loop. */
+    replicationRequestAckFromSlaves();
+}
+
+/* This is called by unblockClient() to perform the blocking op type
+ * specific cleanup. We just remove the client from the list of clients
+ * waiting for replica acks. Never call it directly, call unblockClient()
+ * instead. */
+void unblockClientWaitingReplicas(redisClient *c) {
+    listNode *ln = listSearchKey(server.clients_waiting_acks,c);
+    redisAssert(ln != NULL);
+    listDelNode(server.clients_waiting_acks,ln);
+}
+
+/* Check if there are clients blocked in WAIT that can be unblocked since
+ * we received enough ACKs from slaves. */
+void processClientsWaitingReplicas(void) {
+    long long last_offset = 0;
+    int last_numreplicas = 0;
+
+    listIter li;
+    listNode *ln;
+
+    listRewind(server.clients_waiting_acks,&li);
+    while((ln = listNext(&li))) {
+        redisClient *c = ln->value;
+
+        /* Every time we find a client that is satisfied for a given
+         * offset and number of replicas, we remember it so the next client
+         * may be unblocked without calling replicationCountAcksByOffset()
+         * if the requested offset / replicas were equal or less. */
+        if (last_offset && last_offset > c->bpop.reploffset &&
+                           last_numreplicas > c->bpop.numreplicas)
+        {
+            unblockClient(c);
+            addReplyLongLong(c,last_numreplicas);
+        } else {
+            int numreplicas = replicationCountAcksByOffset(c->bpop.reploffset);
+
+            if (numreplicas >= c->bpop.numreplicas) {
+                last_offset = c->bpop.reploffset;
+                last_numreplicas = numreplicas;
+                unblockClient(c);
+                addReplyLongLong(c,numreplicas);
+            }
+        }
+    }
+}
+
+/* --------------------------- REPLICATION CRON  ---------------------------- */
 
 /* Replication cron funciton, called 1 time per second. */
 void replicationCron(void) {