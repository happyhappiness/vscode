@@ -909,7 +909,7 @@ int processCommand(redisClient *c) {
     } else if (c->multibulk) {
         if (c->bulklen == -1) {
             if (((char*)c->argv[0]->ptr)[0] != '$') {
-                addReplySds(c,sdsnew("-ERR multi bulk protocol error\r\n"));
+                addReplyError(c,"multi bulk protocol error");
                 resetClient(c);
                 return 1;
             } else {
@@ -922,7 +922,7 @@ int processCommand(redisClient *c) {
                     bulklen < 0 || bulklen > 1024*1024*1024)
                 {
                     c->argc--;
-                    addReplySds(c,sdsnew("-ERR invalid bulk write count\r\n"));
+                    addReplyError(c,"invalid bulk write count");
                     resetClient(c);
                     return 1;
                 }
@@ -975,17 +975,14 @@ int processCommand(redisClient *c) {
      * such wrong arity, bad command name and so forth. */
     cmd = lookupCommand(c->argv[0]->ptr);
     if (!cmd) {
-        addReplySds(c,
-            sdscatprintf(sdsempty(), "-ERR unknown command '%s'\r\n",
-                (char*)c->argv[0]->ptr));
+        addReplyErrorFormat(c,"unknown command '%s'",
+            (char*)c->argv[0]->ptr);
         resetClient(c);
         return 1;
     } else if ((cmd->arity > 0 && cmd->arity != c->argc) ||
                (c->argc < -cmd->arity)) {
-        addReplySds(c,
-            sdscatprintf(sdsempty(),
-                "-ERR wrong number of arguments for '%s' command\r\n",
-                cmd->name));
+        addReplyErrorFormat(c,"wrong number of arguments for '%s' command",
+            cmd->name);
         resetClient(c);
         return 1;
     } else if (cmd->flags & REDIS_CMD_BULK && c->bulklen == -1) {
@@ -999,7 +996,7 @@ int processCommand(redisClient *c) {
             bulklen < 0 || bulklen > 1024*1024*1024)
         {
             c->argc--;
-            addReplySds(c,sdsnew("-ERR invalid bulk write count\r\n"));
+            addReplyError(c,"invalid bulk write count");
             resetClient(c);
             return 1;
         }
@@ -1026,7 +1023,7 @@ int processCommand(redisClient *c) {
 
     /* Check if the user is authenticated */
     if (server.requirepass && !c->authenticated && cmd->proc != authCommand) {
-        addReplySds(c,sdsnew("-ERR operation not permitted\r\n"));
+        addReplyError(c,"operation not permitted");
         resetClient(c);
         return 1;
     }
@@ -1035,7 +1032,7 @@ int processCommand(redisClient *c) {
     if (server.maxmemory && (cmd->flags & REDIS_CMD_DENYOOM) &&
         zmalloc_used_memory() > server.maxmemory)
     {
-        addReplySds(c,sdsnew("-ERR command not allowed when used memory > 'maxmemory'\r\n"));
+        addReplyError(c,"command not allowed when used memory > 'maxmemory'");
         resetClient(c);
         return 1;
     }
@@ -1045,7 +1042,7 @@ int processCommand(redisClient *c) {
         &&
         cmd->proc != subscribeCommand && cmd->proc != unsubscribeCommand &&
         cmd->proc != psubscribeCommand && cmd->proc != punsubscribeCommand) {
-        addReplySds(c,sdsnew("-ERR only (P)SUBSCRIBE / (P)UNSUBSCRIBE / QUIT allowed in this context\r\n"));
+        addReplyError(c,"only (P)SUBSCRIBE / (P)UNSUBSCRIBE / QUIT allowed in this context");
         resetClient(c);
         return 1;
     }
@@ -1109,7 +1106,7 @@ void authCommand(redisClient *c) {
       addReply(c,shared.ok);
     } else {
       c->authenticated = 0;
-      addReplySds(c,sdscatprintf(sdsempty(),"-ERR invalid password\r\n"));
+      addReplyError(c,"invalid password");
     }
 }
 