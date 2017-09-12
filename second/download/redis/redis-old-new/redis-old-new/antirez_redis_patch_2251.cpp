@@ -1713,7 +1713,10 @@ static int processCommand(redisClient *c) {
         return 1;
     } else if ((cmd->arity > 0 && cmd->arity != c->argc) ||
                (c->argc < -cmd->arity)) {
-        addReplySds(c,sdsnew("-ERR wrong number of arguments\r\n"));
+        addReplySds(c,
+            sdscatprintf(sdsempty(),
+                "-ERR wrong number of arguments for '%s' command\r\n",
+                cmd->name));
         resetClient(c);
         return 1;
     } else if (server.maxmemory && cmd->flags & REDIS_CMD_DENYOOM && zmalloc_used_memory() > server.maxmemory) {
@@ -3058,7 +3061,7 @@ static void msetGenericCommand(redisClient *c, int nx) {
     int j, busykeys = 0;
 
     if ((c->argc % 2) == 0) {
-        addReplySds(c,sdsnew("-ERR wrong number of arguments\r\n"));
+        addReplySds(c,sdsnew("-ERR wrong number of arguments for MSET\r\n"));
         return;
     }
     /* Handle the NX flag. The MSETNX semantic is to return zero and don't
@@ -4581,7 +4584,8 @@ static void zrangebyscoreCommand(redisClient *c) {
     int offset = 0, limit = -1;
 
     if (c->argc != 4 && c->argc != 7) {
-        addReplySds(c,sdsnew("-ERR wrong number of arguments\r\n"));
+        addReplySds(c,
+            sdsnew("-ERR wrong number of arguments for ZRANGEBYSCORE\r\n"));
         return;
     } else if (c->argc == 7 && strcasecmp(c->argv[4]->ptr,"limit")) {
         addReply(c,shared.syntaxerr);