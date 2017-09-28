     }
     replicationDiscardCachedMaster();
     cancelReplicationHandshake();
     server.repl_state = REDIS_REPL_NONE;
 }
 
+/* This function is called when the slave lose the connection with the
+ * master into an unexpected way. */
+void replicationHandleMasterDisconnection(void) {
+    server.master = NULL;
+    server.repl_state = REDIS_REPL_CONNECT;
+    server.repl_down_since = server.unixtime;
+    /* We lost connection with our master, don't disconnect slaves yet,
+     * maybe we'll be able to PSYNC with our master later. We'll disconnect
+     * the slaves only if we'll have to do a full resync with our master. */
+}
+
 void slaveofCommand(redisClient *c) {
     /* SLAVEOF is not allowed in cluster mode as replication is automatically
      * configured using the current address of the master node. */
     if (server.cluster_enabled) {
         addReplyError(c,"SLAVEOF not allowed in cluster mode.");
         return;
