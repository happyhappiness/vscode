@@ -1005,20 +1005,20 @@ struct redisCommand *lookupCommandByCString(char *s) {
 }
 
 /* Call() is the core of Redis execution of a command */
-void call(redisClient *c, struct redisCommand *cmd) {
+void call(redisClient *c) {
     long long dirty, start = ustime(), duration;
 
     dirty = server.dirty;
-    cmd->proc(c);
+    c->cmd->proc(c);
     dirty = server.dirty-dirty;
     duration = ustime()-start;
-    cmd->microseconds += duration;
+    c->cmd->microseconds += duration;
     slowlogPushEntryIfNeeded(c->argv,c->argc,duration);
-    cmd->calls++;
+    c->cmd->calls++;
 
     if (server.appendonly && dirty)
-        feedAppendOnlyFile(cmd,c->db->id,c->argv,c->argc);
-    if ((dirty || cmd->flags & REDIS_CMD_FORCE_REPLICATION) &&
+        feedAppendOnlyFile(c->cmd,c->db->id,c->argv,c->argc);
+    if ((dirty || c->cmd->flags & REDIS_CMD_FORCE_REPLICATION) &&
         listLength(server.slaves))
         replicationFeedSlaves(server.slaves,c->db->id,c->argv,c->argc);
     if (listLength(server.monitors))
@@ -1035,8 +1035,6 @@ void call(redisClient *c, struct redisCommand *cmd) {
  * and other operations can be performed by the caller. Otherwise
  * if 0 is returned the client was destroied (i.e. after QUIT). */
 int processCommand(redisClient *c) {
-    struct redisCommand *cmd;
-
     /* The QUIT command is handled separately. Normal command procs will
      * go through checking for replication and QUIT will cause trouble
      * when FORCE_REPLICATION is enabled and would be implemented in
@@ -1048,36 +1046,37 @@ int processCommand(redisClient *c) {
     }
 
     /* Now lookup the command and check ASAP about trivial error conditions
-     * such wrong arity, bad command name and so forth. */
-    cmd = lookupCommand(c->argv[0]->ptr);
-    if (!cmd) {
+     * such as wrong arity, bad command name and so forth. */
+    c->cmd = lookupCommand(c->argv[0]->ptr);
+    if (!c->cmd) {
         addReplyErrorFormat(c,"unknown command '%s'",
             (char*)c->argv[0]->ptr);
         return REDIS_OK;
-    } else if ((cmd->arity > 0 && cmd->arity != c->argc) ||
-               (c->argc < -cmd->arity)) {
+    } else if ((c->cmd->arity > 0 && c->cmd->arity != c->argc) ||
+               (c->argc < -c->cmd->arity)) {
         addReplyErrorFormat(c,"wrong number of arguments for '%s' command",
-            cmd->name);
+            c->cmd->name);
         return REDIS_OK;
     }
 
     /* Check if the user is authenticated */
-    if (server.requirepass && !c->authenticated && cmd->proc != authCommand) {
+    if (server.requirepass && !c->authenticated && c->cmd->proc != authCommand)
+    {
         addReplyError(c,"operation not permitted");
         return REDIS_OK;
     }
 
     /* If cluster is enabled, redirect here */
     if (server.cluster_enabled &&
-                !(cmd->getkeys_proc == NULL && cmd->firstkey == 0)) {
+                !(c->cmd->getkeys_proc == NULL && c->cmd->firstkey == 0)) {
         int hashslot;
 
         if (server.cluster.state != REDIS_CLUSTER_OK) {
             addReplyError(c,"The cluster is down. Check with CLUSTER INFO for more information");
             return REDIS_OK;
         } else {
             int ask;
-            clusterNode *n = getNodeByQuery(c,cmd,c->argv,c->argc,&hashslot,&ask);
+            clusterNode *n = getNodeByQuery(c,c->cmd,c->argv,c->argc,&hashslot,&ask);
             if (n == NULL) {
                 addReplyError(c,"Multi keys request invalid in cluster");
                 return REDIS_OK;
@@ -1096,7 +1095,7 @@ int processCommand(redisClient *c) {
      * keys in the dataset). If there are not the only thing we can do
      * is returning an error. */
     if (server.maxmemory) freeMemoryIfNeeded();
-    if (server.maxmemory && (cmd->flags & REDIS_CMD_DENYOOM) &&
+    if (server.maxmemory && (c->cmd->flags & REDIS_CMD_DENYOOM) &&
         zmalloc_used_memory() > server.maxmemory)
     {
         addReplyError(c,"command not allowed when used memory > 'maxmemory'");
@@ -1106,8 +1105,10 @@ int processCommand(redisClient *c) {
     /* Only allow SUBSCRIBE and UNSUBSCRIBE in the context of Pub/Sub */
     if ((dictSize(c->pubsub_channels) > 0 || listLength(c->pubsub_patterns) > 0)
         &&
-        cmd->proc != subscribeCommand && cmd->proc != unsubscribeCommand &&
-        cmd->proc != psubscribeCommand && cmd->proc != punsubscribeCommand) {
+        c->cmd->proc != subscribeCommand &&
+        c->cmd->proc != unsubscribeCommand &&
+        c->cmd->proc != psubscribeCommand &&
+        c->cmd->proc != punsubscribeCommand) {
         addReplyError(c,"only (P)SUBSCRIBE / (P)UNSUBSCRIBE / QUIT allowed in this context");
         return REDIS_OK;
     }
@@ -1116,28 +1117,28 @@ int processCommand(redisClient *c) {
      * we are a slave with a broken link with master. */
     if (server.masterhost && server.replstate != REDIS_REPL_CONNECTED &&
         server.repl_serve_stale_data == 0 &&
-        cmd->proc != infoCommand && cmd->proc != slaveofCommand)
+        c->cmd->proc != infoCommand && c->cmd->proc != slaveofCommand)
     {
         addReplyError(c,
             "link with MASTER is down and slave-serve-stale-data is set to no");
         return REDIS_OK;
     }
 
     /* Loading DB? Return an error if the command is not INFO */
-    if (server.loading && cmd->proc != infoCommand) {
+    if (server.loading && c->cmd->proc != infoCommand) {
         addReply(c, shared.loadingerr);
         return REDIS_OK;
     }
 
     /* Exec the command */
     if (c->flags & REDIS_MULTI &&
-        cmd->proc != execCommand && cmd->proc != discardCommand &&
-        cmd->proc != multiCommand && cmd->proc != watchCommand)
+        c->cmd->proc != execCommand && c->cmd->proc != discardCommand &&
+        c->cmd->proc != multiCommand && c->cmd->proc != watchCommand)
     {
-        queueMultiCommand(c,cmd);
+        queueMultiCommand(c);
         addReply(c,shared.queued);
     } else {
-        call(c,cmd);
+        call(c);
     }
     return REDIS_OK;
 }