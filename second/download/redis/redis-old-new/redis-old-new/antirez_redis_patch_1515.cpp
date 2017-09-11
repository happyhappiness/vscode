@@ -1657,6 +1657,19 @@ void dumpCommand(redisClient *c) {
     return;
 }
 
+/* The ASKING command is required after a -ASK redirection.
+ * The client should issue ASKING before to actualy send the command to
+ * the target instance. See the Redis Cluster specification for more
+ * information. */
+void askingCommand(redisClient *c) {
+    if (server.cluster_enabled == 0) {
+        addReplyError(c,"This instance has cluster support disabled");
+        return;
+    }
+    c->flags |= REDIS_ASKING;
+    addReply(c,shared.ok);
+}
+
 /* -----------------------------------------------------------------------------
  * Cluster functions related to serving / redirecting clients
  * -------------------------------------------------------------------------- */
@@ -1750,9 +1763,12 @@ clusterNode *getNodeByQuery(redisClient *c, struct redisCommand *cmd, robj **arg
     }
     /* Handle the case in which we are receiving this hash slot from
      * another instance, so we'll accept the query even if in the table
-     * it is assigned to a different node. */
-    if (server.cluster.importing_slots_from[slot] != NULL)
+     * it is assigned to a different node, but only if the client
+     * issued an ASKING command before. */
+    if (server.cluster.importing_slots_from[slot] != NULL &&
+        c->flags & REDIS_ASKING) {
         return server.cluster.myself;
+    }
     /* It's not a -ASK case. Base case: just return the right node. */
     return n;
 }