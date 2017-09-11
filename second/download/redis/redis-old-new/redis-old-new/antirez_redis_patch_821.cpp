@@ -2403,6 +2403,7 @@ void timeCommand(redisClient *c) {
 }
 
 
+/* Helper function for addReplyCommand() to output flags. */
 int addReplyCommandFlag(redisClient *c, struct redisCommand *cmd, int f, char *reply) {
     if (cmd->flags & f) {
         addReplyStatus(c, reply);
@@ -2411,6 +2412,7 @@ int addReplyCommandFlag(redisClient *c, struct redisCommand *cmd, int f, char *r
     return 0;
 }
 
+/* Output the representation of a Redis command. Used by the COMMAND command. */
 void addReplyCommand(redisClient *c, struct redisCommand *cmd) {
     if (!cmd) {
         addReply(c, shared.nullbulk);
@@ -2446,26 +2448,27 @@ void addReplyCommand(redisClient *c, struct redisCommand *cmd) {
     }
 }
 
+/* COMMAND <subcommand> <args> */
 void commandCommand(redisClient *c) {
     dictIterator *di;
     dictEntry *de;
 
-    if (c->argc > 2 && !strcasecmp(c->argv[1]->ptr, "info")) {
+    if (c->argc == 1) {
+        addReplyMultiBulkLen(c, dictSize(server.commands));
+        di = dictGetIterator(server.commands);
+        while ((de = dictNext(di)) != NULL) {
+            addReplyCommand(c, dictGetVal(de));
+        }
+        dictReleaseIterator(di);
+    } else if (!strcasecmp(c->argv[1]->ptr, "info")) {
         int i;
         addReplyMultiBulkLen(c, c->argc-2);
         for (i = 2; i < c->argc; i++) {
             addReplyCommand(c, dictFetchValue(server.commands, c->argv[i]->ptr));
         }
-    } else if (c->argc > 2) {
+    } else {
         addReplyError(c, "Unknown subcommand.");
         return;
-    } else {
-        addReplyMultiBulkLen(c, dictSize(server.commands));
-        di = dictGetIterator(server.commands);
-        while ((de = dictNext(di)) != NULL) {
-            addReplyCommand(c, dictGetVal(de));
-        }
-        dictReleaseIterator(di);
     }
 }
 