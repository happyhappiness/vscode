@@ -2414,7 +2414,7 @@ int processCommand(client *c) {
         c->cmd->proc != unsubscribeCommand &&
         c->cmd->proc != psubscribeCommand &&
         c->cmd->proc != punsubscribeCommand) {
-        addReplyError(c,"only (P)SUBSCRIBE / (P)UNSUBSCRIBE / QUIT allowed in this context");
+        addReplyError(c,"only (P)SUBSCRIBE / (P)UNSUBSCRIBE / PING / QUIT allowed in this context");
         return C_OK;
     }
 