@@ -24,14 +24,14 @@ void freeClientMultiState(redisClient *c) {
 }
 
 /* Add a new command into the MULTI commands queue */
-void queueMultiCommand(redisClient *c, struct redisCommand *cmd) {
+void queueMultiCommand(redisClient *c) {
     multiCmd *mc;
     int j;
 
     c->mstate.commands = zrealloc(c->mstate.commands,
             sizeof(multiCmd)*(c->mstate.count+1));
     mc = c->mstate.commands+c->mstate.count;
-    mc->cmd = cmd;
+    mc->cmd = c->cmd;
     mc->argc = c->argc;
     mc->argv = zmalloc(sizeof(robj*)*c->argc);
     memcpy(mc->argv,c->argv,sizeof(robj*)*c->argc);
@@ -78,6 +78,7 @@ void execCommand(redisClient *c) {
     int j;
     robj **orig_argv;
     int orig_argc;
+    struct redisCommand *orig_cmd;
 
     if (!(c->flags & REDIS_MULTI)) {
         addReplyError(c,"EXEC without MULTI");
@@ -105,18 +106,22 @@ void execCommand(redisClient *c) {
     unwatchAllKeys(c); /* Unwatch ASAP otherwise we'll waste CPU cycles */
     orig_argv = c->argv;
     orig_argc = c->argc;
+    orig_cmd = c->cmd;
     addReplyMultiBulkLen(c,c->mstate.count);
     for (j = 0; j < c->mstate.count; j++) {
         c->argc = c->mstate.commands[j].argc;
         c->argv = c->mstate.commands[j].argv;
-        call(c,c->mstate.commands[j].cmd);
+        c->cmd = c->mstate.commands[j].cmd;
+        call(c);
 
         /* Commands may alter argc/argv, restore mstate. */
         c->mstate.commands[j].argc = c->argc;
         c->mstate.commands[j].argv = c->argv;
+        c->mstate.commands[j].cmd = c->cmd;
     }
     c->argv = orig_argv;
     c->argc = orig_argc;
+    c->cmd = orig_cmd;
     freeClientMultiState(c);
     initClientMultiState(c);
     c->flags &= ~(REDIS_MULTI|REDIS_DIRTY_CAS);