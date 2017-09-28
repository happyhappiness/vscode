     serverAssert(server.master != NULL && server.cached_master == NULL);
     serverLog(LL_NOTICE,"Caching the disconnected master state.");
 
     /* Unlink the client from the server structures. */
     unlinkClient(c);
 
+    /* Reset the master client so that's ready to accept new commands:
+     * we want to discard te non processed query buffers and non processed
+     * offsets, including pending transactions, already populated arguments,
+     * pending outputs to the master. */
+    sdsclear(server.master->querybuf);
+    sdsclear(server.master->pending_querybuf);
+    server.master->read_reploff = server.master->reploff;
+    if (c->flags & CLIENT_MULTI) discardTransaction(c);
+    listEmpty(c->reply);
+    c->bufpos = 0;
+    resetClient(c);
+
     /* Save the master. Server.master will be set to null later by
      * replicationHandleMasterDisconnection(). */
     server.cached_master = server.master;
 
     /* Invalidate the Peer ID cache. */
     if (c->peerid) {
