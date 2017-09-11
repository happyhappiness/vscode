@@ -3274,6 +3274,10 @@ void migrateCommand(redisClient *c) {
     return;
 }
 
+/* -----------------------------------------------------------------------------
+ * Cluster functions related to serving / redirecting clients
+ * -------------------------------------------------------------------------- */
+
 /* The ASKING command is required after a -ASK redirection.
  * The client should issue ASKING before to actually send the command to
  * the target instance. See the Redis Cluster specification for more
@@ -3287,9 +3291,23 @@ void askingCommand(redisClient *c) {
     addReply(c,shared.ok);
 }
 
-/* -----------------------------------------------------------------------------
- * Cluster functions related to serving / redirecting clients
- * -------------------------------------------------------------------------- */
+/* The READONLY command is uesd by clients to enter the read-only mode.
+ * In this mode slaves will not redirect clients as long as clients access
+ * with read-only commands to keys that are served by the slave's master. */
+void readonlyCommand(redisClient *c) {
+    if (server.cluster_enabled == 0) {
+        addReplyError(c,"This instance has cluster support disabled");
+        return;
+    }
+    c->flags |= REDIS_READONLY;
+    addReply(c,shared.ok);
+}
+
+/* The READWRITE command just clears the READONLY command state. */
+void readwriteCommand(redisClient *c) {
+    c->flags &= ~REDIS_READONLY;
+    addReply(c,shared.ok);
+}
 
 /* Return the pointer to the cluster node that is able to serve the command.
  * For the function to succeed the command should only target a single
@@ -3385,6 +3403,16 @@ clusterNode *getNodeByQuery(redisClient *c, struct redisCommand *cmd, robj **arg
         (c->flags & REDIS_ASKING || cmd->flags & REDIS_CMD_ASKING)) {
         return server.cluster->myself;
     }
+    /* Handle the read-only client case reading from a slave: if this
+     * node is a slave and the request is about an hash slot our master
+     * is serving, we can reply without redirection. */
+    if (c->flags & REDIS_READONLY &&
+        cmd->flags & REDIS_CMD_READONLY &&
+        server.cluster->myself->flags & REDIS_NODE_SLAVE &&
+        server.cluster->myself->slaveof == n)
+    {
+        return server.cluster->myself;
+    }
     /* It's not a -ASK case. Base case: just return the right node. */
     return n;
 }