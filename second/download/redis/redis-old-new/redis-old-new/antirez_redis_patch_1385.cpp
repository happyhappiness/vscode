@@ -211,7 +211,7 @@ struct redisCommand redisCommandTable[] = {
     {"lastsave",lastsaveCommand,1,"r",0,NULL,0,0,0,0,0},
     {"type",typeCommand,2,"r",0,NULL,1,1,1,0,0},
     {"multi",multiCommand,1,"rs",0,NULL,0,0,0,0,0},
-    {"exec",execCommand,1,"wms",0,NULL,0,0,0,0,0},
+    {"exec",execCommand,1,"s",0,NULL,0,0,0,0,0},
     {"discard",discardCommand,1,"rs",0,NULL,0,0,0,0,0},
     {"sync",syncCommand,1,"ars",0,NULL,0,0,0,0,0},
     {"flushdb",flushdbCommand,1,"w",0,NULL,0,0,0,0,0},
@@ -239,8 +239,8 @@ struct redisCommand redisCommandTable[] = {
     {"dump",dumpCommand,2,"ar",0,NULL,1,1,1,0,0},
     {"object",objectCommand,-2,"r",0,NULL,2,2,2,0,0},
     {"client",clientCommand,-2,"ar",0,NULL,0,0,0,0,0},
-    {"eval",evalCommand,-3,"wms",0,zunionInterGetKeys,0,0,0,0,0},
-    {"evalsha",evalShaCommand,-3,"wms",0,zunionInterGetKeys,0,0,0,0,0},
+    {"eval",evalCommand,-3,"s",0,zunionInterGetKeys,0,0,0,0,0},
+    {"evalsha",evalShaCommand,-3,"s",0,zunionInterGetKeys,0,0,0,0,0},
     {"slowlog",slowlogCommand,-2,"r",0,NULL,0,0,0,0,0},
     {"script",scriptCommand,-2,"ras",0,NULL,0,0,0,0,0},
     {"time",timeCommand,1,"rR",0,NULL,0,0,0,0,0}
@@ -939,7 +939,11 @@ void createSharedObjects(void) {
     shared.slowscripterr = createObject(REDIS_STRING,sdsnew(
         "-BUSY Redis is busy running a script. You can only call SCRIPT KILL or SHUTDOWN NOSAVE.\r\n"));
     shared.bgsaveerr = createObject(REDIS_STRING,sdsnew(
-        "-MISCONF Redis is configured to save RDB snapshots, but is currently not able to persist on disk. Write commands are disabled. Please check Redis logs for details about the error.\r\n"));
+        "-MISCONF Redis is configured to save RDB snapshots, but is currently not able to persist on disk. Commands that may modify the data set are disabled. Please check Redis logs for details about the error.\r\n"));
+    shared.roslaveerr = createObject(REDIS_STRING,sdsnew(
+        "-READONLY You can't write against a read only slave.\r\n"));
+    shared.oomerr = createObject(REDIS_STRING,
+        "-OOM command not allowed when used memory > 'maxmemory'.\r\n");
     shared.space = createObject(REDIS_STRING,sdsnew(" "));
     shared.colon = createObject(REDIS_STRING,sdsnew(":"));
     shared.plus = createObject(REDIS_STRING,sdsnew("+"));
@@ -1048,6 +1052,7 @@ void initServerConfig() {
     server.repl_state = REDIS_REPL_NONE;
     server.repl_syncio_timeout = REDIS_REPL_SYNCIO_TIMEOUT;
     server.repl_serve_stale_data = 1;
+    server.repl_slave_ro = 1;
     server.repl_down_since = -1;
 
     /* Client output buffer limits */
@@ -1483,8 +1488,7 @@ int processCommand(redisClient *c) {
     if (server.maxmemory) {
         int retval = freeMemoryIfNeeded();
         if ((c->cmd->flags & REDIS_CMD_DENYOOM) && retval == REDIS_ERR) {
-            addReplyError(c,
-                "command not allowed when used memory > 'maxmemory'");
+            addReply(c, shared.oomerr);
             return REDIS_OK;
         }
     }
@@ -1499,6 +1503,16 @@ int processCommand(redisClient *c) {
         return REDIS_OK;
     }
 
+    /* Don't accept wirte commands if this is a read only slave. But
+     * accept write commands if this is our master. */
+    if (server.masterhost && server.repl_slave_ro &&
+        !(c->flags & REDIS_MASTER) &&
+        c->cmd->flags & REDIS_CMD_WRITE)
+    {
+        addReply(c, shared.roslaveerr);
+        return REDIS_OK;
+    }
+
     /* Only allow SUBSCRIBE and UNSUBSCRIBE in the context of Pub/Sub */
     if ((dictSize(c->pubsub_channels) > 0 || listLength(c->pubsub_patterns) > 0)
         &&