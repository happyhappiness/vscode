@@ -93,6 +93,7 @@ client *createClient(int fd) {
     c->name = NULL;
     c->bufpos = 0;
     c->querybuf = sdsempty();
+    c->pending_querybuf = sdsempty();
     c->querybuf_peak = 0;
     c->reqtype = 0;
     c->argc = 0;
@@ -107,6 +108,7 @@ client *createClient(int fd) {
     c->replstate = REPL_STATE_NONE;
     c->repl_put_online_on_ack = 0;
     c->reploff = 0;
+    c->read_reploff = 0;
     c->repl_ack_off = 0;
     c->repl_ack_time = 0;
     c->slave_listening_port = 0;
@@ -796,6 +798,7 @@ void freeClient(client *c) {
 
     /* Free the query buffer */
     sdsfree(c->querybuf);
+    sdsfree(c->pending_querybuf);
     c->querybuf = NULL;
 
     /* Deallocate structures used to block on blocking ops. */
@@ -1318,8 +1321,13 @@ void processInputBuffer(client *c) {
             resetClient(c);
         } else {
             /* Only reset the client when the command was executed. */
-            if (processCommand(c) == C_OK)
+            if (processCommand(c) == C_OK) {
+                if (c->flags & CLIENT_MASTER && !(c->flags & CLIENT_MULTI)) {
+                    /* Update the applied replication offset of our master. */
+                    c->reploff = c->read_reploff - sdslen(c->querybuf);
+                }
                 resetClient(c);
+            }
             /* freeMemoryIfNeeded may flush slave output buffers. This may result
              * into a slave, that may be the active client, to be freed. */
             if (server.current_client == NULL) break;
@@ -1366,15 +1374,17 @@ void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
         serverLog(LL_VERBOSE, "Client closed connection");
         freeClient(c);
         return;
+    } else if (c->flags & CLIENT_MASTER) {
+        /* Append the query buffer to the pending (not applied) buffer
+         * of the master. We'll use this buffer later in order to have a
+         * copy of the string applied by the last command executed. */
+        c->pending_querybuf = sdscatlen(c->pending_querybuf,
+                                        c->querybuf+qblen,nread);
     }
 
     sdsIncrLen(c->querybuf,nread);
     c->lastinteraction = server.unixtime;
-    if (c->flags & CLIENT_MASTER) {
-        c->reploff += nread;
-        replicationFeedSlavesFromMasterStream(server.slaves,
-                c->querybuf+qblen,nread);
-    }
+    if (c->flags & CLIENT_MASTER) c->read_reploff += nread;
     server.stat_net_input_bytes += nread;
     if (sdslen(c->querybuf) > server.client_max_querybuf_len) {
         sds ci = catClientInfoString(sdsempty(),c), bytes = sdsempty();
@@ -1386,7 +1396,25 @@ void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
         freeClient(c);
         return;
     }
-    processInputBuffer(c);
+
+    /* Time to process the buffer. If the client is a master we need to
+     * compute the difference between the applied offset before and after
+     * processing the buffer, to understand how much of the replication stream
+     * was actually applied to the master state: this quantity, and its
+     * corresponding part of the replication stream, will be propagated to
+     * the sub-slaves and to the replication backlog. */
+    if (!(c->flags & CLIENT_MASTER)) {
+        processInputBuffer(c);
+    } else {
+        size_t prev_offset = c->reploff;
+        processInputBuffer(c);
+        size_t applied = c->reploff - prev_offset;
+        if (applied) {
+            replicationFeedSlavesFromMasterStream(server.slaves,
+                    c->pending_querybuf, applied);
+            sdsrange(c->pending_querybuf,applied,-1);
+        }
+    }
 }
 
 void getClientsMaxBuffers(unsigned long *longest_output_list,