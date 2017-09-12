@@ -786,6 +786,7 @@ void initServerConfig() {
     server.masterport = 6379;
     server.master = NULL;
     server.replstate = REDIS_REPL_NONE;
+    server.repl_serve_stale_data = 1;
 
     /* Double constants initialization */
     R_Zero = 0.0;
@@ -994,6 +995,17 @@ int processCommand(redisClient *c) {
         return REDIS_OK;
     }
 
+    /* Only allow INFO and SLAVEOF when slave-serve-stale-data is no and
+     * we are a slave with a broken link with master. */
+    if (server.masterhost && server.replstate != REDIS_REPL_CONNECTED &&
+        server.repl_serve_stale_data == 0 &&
+        cmd->proc != infoCommand && cmd->proc != slaveofCommand)
+    {
+        addReplyError(c,
+            "link with MASTER is down and slave-serve-stale-data is set to no");
+        return REDIS_OK;
+    }
+
     /* Exec the command */
     if (c->flags & REDIS_MULTI &&
         cmd->proc != execCommand && cmd->proc != discardCommand &&