@@ -457,8 +457,8 @@ void syncCommand(redisClient *c) {
      * the client about already issued commands. We need a fresh reply
      * buffer registering the differences between the BGSAVE and the current
      * dataset, so that we can copy to other slaves if needed. */
-    if (listLength(c->reply) != 0) {
-        addReplyError(c,"SYNC and PSYNC are invalid with pending input");
+    if (listLength(c->reply) != 0 || c->bufpos != 0) {
+        addReplyError(c,"SYNC and PSYNC are invalid with pending output");
         return;
     }
 