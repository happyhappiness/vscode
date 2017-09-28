 /* Close all the slaves connections. This is useful in chained replication
  * when we resync with our own master and want to force all our slaves to
  * resync with us as well. */
 void disconnectSlaves(void) {
     while (listLength(server.slaves)) {
         listNode *ln = listFirst(server.slaves);
-        freeClient((redisClient*)ln->value);
+        freeClient((client*)ln->value);
     }
 }
 
-void freeClient(redisClient *c) {
+/* Remove the specified client from global lists where the client could
+ * be referenced, not including the Pub/Sub channels.
+ * This is used by freeClient() and replicationCacheMaster(). */
+void unlinkClient(client *c) {
     listNode *ln;
 
-    /* If this is marked as current client unset it */
+    /* If this is marked as current client unset it. */
     if (server.current_client == c) server.current_client = NULL;
 
+    /* Certain operations must be done only if the client has an active socket.
+     * If the client was already unlinked or if it's a "fake client" the
+     * fd is already set to -1. */
+    if (c->fd != -1) {
+        /* Remove from the list of active clients. */
+        ln = listSearchKey(server.clients,c);
+        serverAssert(ln != NULL);
+        listDelNode(server.clients,ln);
+
+        /* Unregister async I/O handlers and close the socket. */
+        aeDeleteFileEvent(server.el,c->fd,AE_READABLE);
+        aeDeleteFileEvent(server.el,c->fd,AE_WRITABLE);
+        close(c->fd);
+        c->fd = -1;
+    }
+
+    /* Remove from the list of pending writes if needed. */
+    if (c->flags & CLIENT_PENDING_WRITE) {
+        ln = listSearchKey(server.clients_pending_write,c);
+        serverAssert(ln != NULL);
+        listDelNode(server.clients_pending_write,ln);
+        c->flags &= ~CLIENT_PENDING_WRITE;
+    }
+
+    /* When client was just unblocked because of a blocking operation,
+     * remove it from the list of unblocked clients. */
+    if (c->flags & CLIENT_UNBLOCKED) {
+        ln = listSearchKey(server.unblocked_clients,c);
+        serverAssert(ln != NULL);
+        listDelNode(server.unblocked_clients,ln);
+        c->flags &= ~CLIENT_UNBLOCKED;
+    }
+}
+
+void freeClient(client *c) {
+    listNode *ln;
+
     /* If it is our master that's beging disconnected we should make sure
      * to cache the state to try a partial resynchronization later.
      *
      * Note that before doing this we make sure that the client is not in
      * some unexpected state, by checking its flags. */
-    if (server.master && c->flags & REDIS_MASTER) {
-        redisLog(REDIS_WARNING,"Connection with master lost.");
-        if (!(c->flags & (REDIS_CLOSE_AFTER_REPLY|
-                          REDIS_CLOSE_ASAP|
-                          REDIS_BLOCKED|
-                          REDIS_UNBLOCKED)))
+    if (server.master && c->flags & CLIENT_MASTER) {
+        serverLog(LL_WARNING,"Connection with master lost.");
+        if (!(c->flags & (CLIENT_CLOSE_AFTER_REPLY|
+                          CLIENT_CLOSE_ASAP|
+                          CLIENT_BLOCKED|
+                          CLIENT_UNBLOCKED)))
         {
             replicationCacheMaster(c);
             return;
         }
     }
 
     /* Log link disconnection with slave */
-    if ((c->flags & REDIS_SLAVE) && !(c->flags & REDIS_MONITOR)) {
-        redisLog(REDIS_WARNING,"Connection with slave %s lost.",
+    if ((c->flags & CLIENT_SLAVE) && !(c->flags & CLIENT_MONITOR)) {
+        serverLog(LL_WARNING,"Connection with slave %s lost.",
             replicationGetSlaveName(c));
     }
 
     /* Free the query buffer */
     sdsfree(c->querybuf);
     c->querybuf = NULL;
 
     /* Deallocate structures used to block on blocking ops. */
-    if (c->flags & REDIS_BLOCKED) unblockClient(c);
+    if (c->flags & CLIENT_BLOCKED) unblockClient(c);
     dictRelease(c->bpop.keys);
 
     /* UNWATCH all the keys */
     unwatchAllKeys(c);
     listRelease(c->watched_keys);
 
     /* Unsubscribe from all the pubsub channels */
     pubsubUnsubscribeAllChannels(c,0);
     pubsubUnsubscribeAllPatterns(c,0);
     dictRelease(c->pubsub_channels);
     listRelease(c->pubsub_patterns);
 
-    /* Close socket, unregister events, and remove list of replies and
-     * accumulated arguments. */
-    if (c->fd != -1) {
-        aeDeleteFileEvent(server.el,c->fd,AE_READABLE);
-        aeDeleteFileEvent(server.el,c->fd,AE_WRITABLE);
-        close(c->fd);
-    }
+    /* Free data structures. */
     listRelease(c->reply);
     freeClientArgv(c);
 
-    /* Remove from the list of clients */
-    if (c->fd != -1) {
-        ln = listSearchKey(server.clients,c);
-        redisAssert(ln != NULL);
-        listDelNode(server.clients,ln);
-    }
-
-    /* When client was just unblocked because of a blocking operation,
-     * remove it from the list of unblocked clients. */
-    if (c->flags & REDIS_UNBLOCKED) {
-        ln = listSearchKey(server.unblocked_clients,c);
-        redisAssert(ln != NULL);
-        listDelNode(server.unblocked_clients,ln);
-    }
+    /* Unlink the client: this will close the socket, remove the I/O
+     * handlers, and remove references of the client from different
+     * places where active clients may be referenced. */
+    unlinkClient(c);
 
     /* Master/slave cleanup Case 1:
      * we lost the connection with a slave. */
-    if (c->flags & REDIS_SLAVE) {
-        if (c->replstate == REDIS_REPL_SEND_BULK) {
+    if (c->flags & CLIENT_SLAVE) {
+        if (c->replstate == SLAVE_STATE_SEND_BULK) {
             if (c->repldbfd != -1) close(c->repldbfd);
             if (c->replpreamble) sdsfree(c->replpreamble);
         }
-        list *l = (c->flags & REDIS_MONITOR) ? server.monitors : server.slaves;
+        list *l = (c->flags & CLIENT_MONITOR) ? server.monitors : server.slaves;
         ln = listSearchKey(l,c);
-        redisAssert(ln != NULL);
+        serverAssert(ln != NULL);
         listDelNode(l,ln);
         /* We need to remember the time when we started to have zero
          * attached slaves, as after some time we'll free the replication
          * backlog. */
-        if (c->flags & REDIS_SLAVE && listLength(server.slaves) == 0)
+        if (c->flags & CLIENT_SLAVE && listLength(server.slaves) == 0)
             server.repl_no_slaves_since = server.unixtime;
         refreshGoodSlavesCount();
     }
 
     /* Master/slave cleanup Case 2:
      * we lost the connection with the master. */
-    if (c->flags & REDIS_MASTER) replicationHandleMasterDisconnection();
+    if (c->flags & CLIENT_MASTER) replicationHandleMasterDisconnection();
 
     /* If this client was scheduled for async freeing we need to remove it
      * from the queue. */
-    if (c->flags & REDIS_CLOSE_ASAP) {
+    if (c->flags & CLIENT_CLOSE_ASAP) {
         ln = listSearchKey(server.clients_to_close,c);
-        redisAssert(ln != NULL);
+        serverAssert(ln != NULL);
         listDelNode(server.clients_to_close,ln);
     }
 
     /* Release other dynamically allocated client structure fields,
      * and finally release the client structure itself. */
     if (c->name) decrRefCount(c->name);
