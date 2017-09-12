@@ -914,10 +914,6 @@ int processCommand(redisClient *c) {
         return REDIS_OK;
     }
 
-    /* Let's try to encode the bulk object to save space. */
-    if (cmd->flags & REDIS_CMD_BULK)
-        c->argv[c->argc-1] = tryObjectEncoding(c->argv[c->argc-1]);
-
     /* Check if the user is authenticated */
     if (server.requirepass && !c->authenticated && cmd->proc != authCommand) {
         addReplyError(c,"operation not permitted");
@@ -1011,6 +1007,7 @@ void pingCommand(redisClient *c) {
 }
 
 void echoCommand(redisClient *c) {
+    c->argv[1] = tryObjectEncoding(c->argv[1]);
     addReplyBulk(c,c->argv[1]);
 }
 