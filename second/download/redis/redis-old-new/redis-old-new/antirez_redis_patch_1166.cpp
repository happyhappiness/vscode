@@ -116,6 +116,7 @@ void execCommand(redisClient *c) {
     robj **orig_argv;
     int orig_argc;
     struct redisCommand *orig_cmd;
+    int must_propagate = 0; /* Need to propagate MULTI/EXEC to AOF / slaves? */
 
     if (!(c->flags & REDIS_MULTI)) {
         addReplyError(c,"EXEC without MULTI");
@@ -135,12 +136,6 @@ void execCommand(redisClient *c) {
         goto handle_monitor;
     }
 
-    /* Propagate a MULTI request now that we are sure the block is executed.
-     * This way we'll deliver the MULTI/..../EXEC block as a whole and
-     * both the AOF and the replication link will have the same consistency
-     * and atomicity guarantees. */
-    execCommandPropagateMulti(c);
-
     /* Exec all the queued commands */
     unwatchAllKeys(c); /* Unwatch ASAP otherwise we'll waste CPU cycles */
     orig_argv = c->argv;
@@ -151,6 +146,16 @@ void execCommand(redisClient *c) {
         c->argc = c->mstate.commands[j].argc;
         c->argv = c->mstate.commands[j].argv;
         c->cmd = c->mstate.commands[j].cmd;
+
+        /* Propagate a MULTI request once we encounter the first write op.
+         * This way we'll deliver the MULTI/..../EXEC block as a whole and
+         * both the AOF and the replication link will have the same consistency
+         * and atomicity guarantees. */
+        if (!must_propagate && !(c->cmd->flags & REDIS_CMD_READONLY)) {
+            execCommandPropagateMulti(c);
+            must_propagate = 1;
+        }
+
         call(c,REDIS_CALL_FULL);
 
         /* Commands may alter argc/argv, restore mstate. */
@@ -162,10 +167,9 @@ void execCommand(redisClient *c) {
     c->argc = orig_argc;
     c->cmd = orig_cmd;
     discardTransaction(c);
-    /* Make sure the EXEC command is always replicated / AOF, since we
-     * always send the MULTI command (we can't know beforehand if the
-     * next operations will contain at least a modification to the DB). */
-    server.dirty++;
+    /* Make sure the EXEC command will be propagated as well if MULTI
+     * was already propagated. */
+    if (must_propagate) server.dirty++;
 
 handle_monitor:
     /* Send EXEC to clients waiting data from MONITOR. We do it here