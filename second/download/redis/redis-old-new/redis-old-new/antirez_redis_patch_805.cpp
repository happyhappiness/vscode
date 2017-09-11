@@ -2403,7 +2403,8 @@ void authCommand(redisClient *c) {
 void pingCommand(redisClient *c) {
     /* The command takes zero or one arguments. */
     if (c->argc > 2) {
-        addReply(c,shared.syntaxerr);
+        addReplyErrorFormat(c,"wrong number of arguments for '%s' command",
+            c->cmd->name);
         return;
     }
 