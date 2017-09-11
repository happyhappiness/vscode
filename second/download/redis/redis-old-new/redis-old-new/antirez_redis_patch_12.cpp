@@ -117,6 +117,7 @@ void execCommand(client *c) {
     int orig_argc;
     struct redisCommand *orig_cmd;
     int must_propagate = 0; /* Need to propagate MULTI/EXEC to AOF / slaves? */
+    int was_master = server.masterhost == NULL;
 
     if (!(c->flags & CLIENT_MULTI)) {
         addReplyError(c,"EXEC without MULTI");
@@ -147,11 +148,12 @@ void execCommand(client *c) {
         c->argv = c->mstate.commands[j].argv;
         c->cmd = c->mstate.commands[j].cmd;
 
-        /* Propagate a MULTI request once we encounter the first write op.
+        /* Propagate a MULTI request once we encounter the first command which
+         * is not readonly nor an administrative one.
          * This way we'll deliver the MULTI/..../EXEC block as a whole and
          * both the AOF and the replication link will have the same consistency
          * and atomicity guarantees. */
-        if (!must_propagate && !(c->cmd->flags & CMD_READONLY)) {
+        if (!must_propagate && !(c->cmd->flags & (CMD_READONLY|CMD_ADMIN))) {
             execCommandPropagateMulti(c);
             must_propagate = 1;
         }
@@ -167,9 +169,22 @@ void execCommand(client *c) {
     c->argc = orig_argc;
     c->cmd = orig_cmd;
     discardTransaction(c);
+
     /* Make sure the EXEC command will be propagated as well if MULTI
      * was already propagated. */
-    if (must_propagate) server.dirty++;
+    if (must_propagate) {
+        int is_master = server.masterhost == NULL;
+        server.dirty++;
+        /* If inside the MULTI/EXEC block this instance was suddenly
+         * switched from master to slave (using the SLAVEOF command), the
+         * initial MULTI was propagated into the replication backlog, but the
+         * rest was not. We need to make sure to at least terminate the
+         * backlog with the final EXEC. */
+        if (server.repl_backlog && was_master && !is_master) {
+            char *execcmd = "*1\r\n$4\r\nEXEC\r\n";
+            feedReplicationBacklog(execcmd,strlen(execcmd));
+        }
+    }
 
 handle_monitor:
     /* Send EXEC to clients waiting data from MONITOR. We do it here