@@ -986,6 +986,8 @@ void createSharedObjects(void) {
         "-LOADING Redis is loading the dataset in memory\r\n"));
     shared.slowscripterr = createObject(REDIS_STRING,sdsnew(
         "-BUSY Redis is busy running a script. You can only call SCRIPT KILL or SHUTDOWN NOSAVE.\r\n"));
+    shared.masterdownerr = createObject(REDIS_STRING,sdsnew(
+        "-MASTERDOWN Link with MASTER is down and slave-serve-stale-data is set to 'no'.\r\n"));
     shared.bgsaveerr = createObject(REDIS_STRING,sdsnew(
         "-MISCONF Redis is configured to save RDB snapshots, but is currently not able to persist on disk. Commands that may modify the data set are disabled. Please check Redis logs for details about the error.\r\n"));
     shared.roslaveerr = createObject(REDIS_STRING,sdsnew(
@@ -1583,8 +1585,7 @@ int processCommand(redisClient *c) {
         server.repl_serve_stale_data == 0 &&
         c->cmd->proc != infoCommand && c->cmd->proc != slaveofCommand)
     {
-        addReplyError(c,
-            "link with MASTER is down and slave-serve-stale-data is set to no");
+        addReply(c, shared.masterdownerr);
         return REDIS_OK;
     }
 