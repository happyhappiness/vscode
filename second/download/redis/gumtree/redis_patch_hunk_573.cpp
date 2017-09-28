  * so the stream of data that we'll receive will start from were this
  * master left. */
 void replicationResurrectCachedMaster(int newfd) {
     server.master = server.cached_master;
     server.cached_master = NULL;
     server.master->fd = newfd;
-    server.master->flags &= ~(REDIS_CLOSE_AFTER_REPLY|REDIS_CLOSE_ASAP);
+    server.master->flags &= ~(CLIENT_CLOSE_AFTER_REPLY|CLIENT_CLOSE_ASAP);
     server.master->authenticated = 1;
     server.master->lastinteraction = server.unixtime;
-    server.repl_state = REDIS_REPL_CONNECTED;
+    server.repl_state = REPL_STATE_CONNECTED;
 
     /* Re-add to the list of clients. */
     listAddNodeTail(server.clients,server.master);
     if (aeCreateFileEvent(server.el, newfd, AE_READABLE,
                           readQueryFromClient, server.master)) {
-        redisLog(REDIS_WARNING,"Error resurrecting the cached master, impossible to add the readable handler: %s", strerror(errno));
+        serverLog(LL_WARNING,"Error resurrecting the cached master, impossible to add the readable handler: %s", strerror(errno));
         freeClientAsync(server.master); /* Close ASAP. */
     }
 
     /* We may also need to install the write handler as well if there is
      * pending data in the write buffers. */
-    if (server.master->bufpos || listLength(server.master->reply)) {
+    if (clientHasPendingReplies(server.master)) {
         if (aeCreateFileEvent(server.el, newfd, AE_WRITABLE,
                           sendReplyToClient, server.master)) {
-            redisLog(REDIS_WARNING,"Error resurrecting the cached master, impossible to add the writable handler: %s", strerror(errno));
+            serverLog(LL_WARNING,"Error resurrecting the cached master, impossible to add the writable handler: %s", strerror(errno));
             freeClientAsync(server.master); /* Close ASAP. */
         }
     }
 }
 
 /* ------------------------- MIN-SLAVES-TO-WRITE  --------------------------- */
