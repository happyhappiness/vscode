@@ -1070,6 +1070,8 @@ void createSharedObjects(void) {
         "-READONLY You can't write against a read only slave.\r\n"));
     shared.oomerr = createObject(REDIS_STRING,sdsnew(
         "-OOM command not allowed when used memory > 'maxmemory'.\r\n"));
+    shared.execaborterr = createObject(REDIS_STRING,sdsnew(
+        "-EXECABORT Transaction discarded because of previous errors.\r\n"));
     shared.space = createObject(REDIS_STRING,sdsnew(" "));
     shared.colon = createObject(REDIS_STRING,sdsnew(":"));
     shared.plus = createObject(REDIS_STRING,sdsnew("+"));
@@ -1590,11 +1592,13 @@ int processCommand(redisClient *c) {
      * such as wrong arity, bad command name and so forth. */
     c->cmd = c->lastcmd = lookupCommand(c->argv[0]->ptr);
     if (!c->cmd) {
+        flagTransaction(c);
         addReplyErrorFormat(c,"unknown command '%s'",
             (char*)c->argv[0]->ptr);
         return REDIS_OK;
     } else if ((c->cmd->arity > 0 && c->cmd->arity != c->argc) ||
                (c->argc < -c->cmd->arity)) {
+        flagTransaction(c);
         addReplyErrorFormat(c,"wrong number of arguments for '%s' command",
             c->cmd->name);
         return REDIS_OK;
@@ -1603,6 +1607,7 @@ int processCommand(redisClient *c) {
     /* Check if the user is authenticated */
     if (server.requirepass && !c->authenticated && c->cmd->proc != authCommand)
     {
+        flagTransaction(c);
         addReplyError(c,"operation not permitted");
         return REDIS_OK;
     }
@@ -1638,6 +1643,7 @@ int processCommand(redisClient *c) {
     if (server.maxmemory) {
         int retval = freeMemoryIfNeeded();
         if ((c->cmd->flags & REDIS_CMD_DENYOOM) && retval == REDIS_ERR) {
+            flagTransaction(c);
             addReply(c, shared.oomerr);
             return REDIS_OK;
         }
@@ -1649,6 +1655,7 @@ int processCommand(redisClient *c) {
         && server.lastbgsave_status == REDIS_ERR &&
         c->cmd->flags & REDIS_CMD_WRITE)
     {
+        flagTransaction(c);
         addReply(c, shared.bgsaveerr);
         return REDIS_OK;
     }
@@ -1680,6 +1687,7 @@ int processCommand(redisClient *c) {
         server.repl_serve_stale_data == 0 &&
         !(c->cmd->flags & REDIS_CMD_STALE))
     {
+        flagTransaction(c);
         addReply(c, shared.masterdownerr);
         return REDIS_OK;
     }
@@ -1701,6 +1709,7 @@ int processCommand(redisClient *c) {
           c->argc == 2 &&
           tolower(((char*)c->argv[1]->ptr)[0]) == 'k'))
     {
+        flagTransaction(c);
         addReply(c, shared.slowscripterr);
         return REDIS_OK;
     }