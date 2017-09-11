@@ -2403,15 +2403,15 @@ void timeCommand(redisClient *c) {
 }
 
 
-static int replyCmdFlag(redisClient *c,
-                        struct redisCommand *cmd, int f, char *reply) {
+int addReplyCommandFlag(redisClient *c, struct redisCommand *cmd, int f, char *reply) {
     if (cmd->flags & f) {
         addReplyStatus(c, reply);
         return 1;
     }
     return 0;
 }
-static void replyCmd(redisClient *c, struct redisCommand *cmd) {
+
+void addReplyCommand(redisClient *c, struct redisCommand *cmd) {
     if (!cmd) {
         addReply(c, shared.nullbulk);
     } else {
@@ -2422,18 +2422,18 @@ static void replyCmd(redisClient *c, struct redisCommand *cmd) {
 
         int flagcount = 0;
         void *flaglen = addDeferredMultiBulkLength(c);
-        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_WRITE, "write");
-        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_READONLY, "readonly");
-        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_DENYOOM, "denyoom");
-        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_ADMIN, "admin");
-        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_PUBSUB, "pubsub");
-        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_NOSCRIPT, "noscript");
-        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_RANDOM, "random");
-        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_SORT_FOR_SCRIPT,"scriptsort");
-        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_LOADING, "loading");
-        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_STALE, "stale");
-        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_SKIP_MONITOR, "skipmonitor");
-        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_ASKING, "asking");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_WRITE, "write");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_READONLY, "readonly");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_DENYOOM, "denyoom");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_ADMIN, "admin");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_PUBSUB, "pubsub");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_NOSCRIPT, "noscript");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_RANDOM, "random");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_SORT_FOR_SCRIPT,"sort_for_script");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_LOADING, "loading");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_STALE, "stale");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_SKIP_MONITOR, "skip_monitor");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_ASKING, "asking");
         if (cmd->getkeys_proc) {
             addReplyStatus(c, "movablekeys");
             flagcount += 1;
@@ -2445,6 +2445,7 @@ static void replyCmd(redisClient *c, struct redisCommand *cmd) {
         addReplyLongLong(c, cmd->keystep);
     }
 }
+
 void commandsCommand(redisClient *c) {
     dictIterator *di;
     dictEntry *de;
@@ -2453,7 +2454,7 @@ void commandsCommand(redisClient *c) {
         int i;
         addReplyMultiBulkLen(c, c->argc-2);
         for (i = 2; i < c->argc; i++) {
-            replyCmd(c, dictFetchValue(server.commands, c->argv[i]->ptr));
+            addReplyCommand(c, dictFetchValue(server.commands, c->argv[i]->ptr));
         }
     } else if (c->argc > 2) {
         addReplyError(c, "Unknown subcommand.");
@@ -2462,13 +2463,12 @@ void commandsCommand(redisClient *c) {
         addReplyMultiBulkLen(c, dictSize(server.commands));
         di = dictGetIterator(server.commands);
         while ((de = dictNext(di)) != NULL) {
-            replyCmd(c, dictGetVal(de));
+            addReplyCommand(c, dictGetVal(de));
         }
         dictReleaseIterator(di);
     }
 }
 
-
 /* Convert an amount of bytes into a human readable string in the form
  * of 100B, 2G, 100M, 4K, and so forth. */
 void bytesToHuman(char *s, unsigned long long n) {