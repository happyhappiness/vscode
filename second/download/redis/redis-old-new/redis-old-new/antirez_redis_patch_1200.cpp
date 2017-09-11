@@ -1083,6 +1083,8 @@ void createSharedObjects(void) {
         "-MISCONF Redis is configured to save RDB snapshots, but is currently not able to persist on disk. Commands that may modify the data set are disabled. Please check Redis logs for details about the error.\r\n"));
     shared.roslaveerr = createObject(REDIS_STRING,sdsnew(
         "-READONLY You can't write against a read only slave.\r\n"));
+    shared.noautherr = createObject(REDIS_STRING,sdsnew(
+        "-NOAUTH Authentication required.\r\n"));
     shared.oomerr = createObject(REDIS_STRING,sdsnew(
         "-OOM command not allowed when used memory > 'maxmemory'.\r\n"));
     shared.execaborterr = createObject(REDIS_STRING,sdsnew(
@@ -1650,7 +1652,7 @@ int processCommand(redisClient *c) {
     if (server.requirepass && !c->authenticated && c->cmd->proc != authCommand)
     {
         flagTransaction(c);
-        addReplyError(c,"operation not permitted");
+        addReply(c,shared.noautherr);
         return REDIS_OK;
     }
 