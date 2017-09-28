     }
     replicationDiscardCachedMaster();
     cancelReplicationHandshake();
     server.repl_state = REDIS_REPL_NONE;
 }
 
-/* This function is called when the slave lose the connection with the
- * master into an unexpected way. */
-void replicationHandleMasterDisconnection(void) {
-    server.master = NULL;
-    server.repl_state = REDIS_REPL_CONNECT;
-    server.repl_down_since = server.unixtime;
-    /* We lost connection with our master, don't disconnect slaves yet,
-     * maybe we'll be able to PSYNC with our master later. We'll disconnect
-     * the slaves only if we'll have to do a full resync with our master. */
-}
-
 void slaveofCommand(redisClient *c) {
+    /* SLAVEOF is not allowed in cluster mode as replication is automatically
+     * configured using the current address of the master node. */
+    if (server.cluster_enabled) {
+        addReplyError(c,"SLAVEOF not allowed in cluster mode.");
+        return;
+    }
+
+    /* The special host/port combination "NO" "ONE" turns the instance
+     * into a master. Otherwise the new master address is set. */
     if (!strcasecmp(c->argv[1]->ptr,"no") &&
         !strcasecmp(c->argv[2]->ptr,"one")) {
         if (server.masterhost) {
             replicationUnsetMaster();
-            sds client = catClientInfoString(sdsempty(),c);
-            redisLog(REDIS_NOTICE,
-                "MASTER MODE enabled (user request from '%s')",client);
-            sdsfree(client);
+            redisLog(REDIS_NOTICE,"MASTER MODE enabled (user request)");
         }
     } else {
         long port;
 
         if ((getLongFromObjectOrReply(c, c->argv[2], &port, NULL) != REDIS_OK))
             return;
