@@ -7213,6 +7213,20 @@ static void discardCommand(redisClient *c) {
     addReply(c,shared.ok);
 }
 
+/* Send a MULTI command to all the slaves and AOF file. Check the execCommand
+ * implememntation for more information. */
+static void execCommandReplicateMulti(redisClient *c) {
+    struct redisCommand *cmd;
+    robj *multistring = createStringObject("MULTI",5);
+
+    cmd = lookupCommand("multi");
+    if (server.appendonly)
+        feedAppendOnlyFile(cmd,c->db->id,&multistring,1);
+    if (listLength(server.slaves))
+        replicationFeedSlaves(server.slaves,c->db->id,&multistring,1);
+    decrRefCount(multistring);
+}
+
 static void execCommand(redisClient *c) {
     int j;
     robj **orig_argv;
@@ -7223,6 +7237,13 @@ static void execCommand(redisClient *c) {
         return;
     }
 
+    /* Replicate a MULTI request now that we are sure the block is executed.
+     * This way we'll deliver the MULTI/..../EXEC block as a whole and
+     * both the AOF and the replication link will have the same consistency
+     * and atomicity guarantees. */
+    execCommandReplicateMulti(c);
+
+    /* Exec all the queued commands */
     orig_argv = c->argv;
     orig_argc = c->argc;
     addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->mstate.count));
@@ -7236,6 +7257,10 @@ static void execCommand(redisClient *c) {
     freeClientMultiState(c);
     initClientMultiState(c);
     c->flags &= (~REDIS_MULTI);
+    /* Make sure the EXEC command is always replicated / AOF, since we
+     * always send the MULTI command (we can't know beforehand if the
+     * next operations will contain at least a modification to the DB). */
+    server.dirty++;
 }
 
 /* =========================== Blocking Operations  ========================= */