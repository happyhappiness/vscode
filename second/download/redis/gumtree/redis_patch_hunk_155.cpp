     {
         addReply(c, shared.roslaveerr);
         return REDIS_OK;
     }
 
     /* Only allow SUBSCRIBE and UNSUBSCRIBE in the context of Pub/Sub */
-    if ((dictSize(c->pubsub_channels) > 0 || listLength(c->pubsub_patterns) > 0)
-        &&
+    if (c->flags & REDIS_PUBSUB &&
+        c->cmd->proc != pingCommand &&
         c->cmd->proc != subscribeCommand &&
         c->cmd->proc != unsubscribeCommand &&
         c->cmd->proc != psubscribeCommand &&
         c->cmd->proc != punsubscribeCommand) {
         addReplyError(c,"only (P)SUBSCRIBE / (P)UNSUBSCRIBE / QUIT allowed in this context");
         return REDIS_OK;
