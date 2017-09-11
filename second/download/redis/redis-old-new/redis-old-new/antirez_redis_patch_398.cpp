@@ -1846,36 +1846,16 @@ void replicationSendAck(void) {
  * handshake in order to reactivate the cached master.
  */
 void replicationCacheMaster(client *c) {
-    listNode *ln;
-
     serverAssert(server.master != NULL && server.cached_master == NULL);
     serverLog(LL_NOTICE,"Caching the disconnected master state.");
 
-    /* Remove from the list of clients, we don't want this client to be
-     * listed by CLIENT LIST or processed in any way by batch operations. */
-    ln = listSearchKey(server.clients,c);
-    serverAssert(ln != NULL);
-    listDelNode(server.clients,ln);
-
-    /* Remove from the list of clients with pending writes as well. */
-    if (c->flags & CLIENT_PENDING_WRITE) {
-        ln = listSearchKey(server.clients_pending_write,c);
-        if (ln) listDelNode(server.clients_pending_write,ln);
-    }
+    /* Unlink the client from the server structures. */
+    unlinkClient(c);
 
     /* Save the master. Server.master will be set to null later by
      * replicationHandleMasterDisconnection(). */
     server.cached_master = server.master;
 
-    /* Remove the event handlers and close the socket. We'll later reuse
-     * the socket of the new connection with the master during PSYNC. */
-    aeDeleteFileEvent(server.el,c->fd,AE_READABLE);
-    aeDeleteFileEvent(server.el,c->fd,AE_WRITABLE);
-    close(c->fd);
-
-    /* Set fd to -1 so that we can safely call freeClient(c) later. */
-    c->fd = -1;
-
     /* Invalidate the Peer ID cache. */
     if (c->peerid) {
         sdsfree(c->peerid);