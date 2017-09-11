@@ -1251,6 +1251,15 @@ void replicationUnsetMaster(void) {
 }
 
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