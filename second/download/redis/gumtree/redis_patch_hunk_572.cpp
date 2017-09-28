 
 /* Free a cached master, called when there are no longer the conditions for
  * a partial resync on reconnection. */
 void replicationDiscardCachedMaster(void) {
     if (server.cached_master == NULL) return;
 
-    redisLog(REDIS_NOTICE,"Discarding previously cached master state.");
-    server.cached_master->flags &= ~REDIS_MASTER;
+    serverLog(LL_NOTICE,"Discarding previously cached master state.");
+    server.cached_master->flags &= ~CLIENT_MASTER;
     freeClient(server.cached_master);
     server.cached_master = NULL;
 }
 
 /* Turn the cached master into the current master, using the file descriptor
  * passed as argument as the socket for the new master.
