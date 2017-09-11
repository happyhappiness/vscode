@@ -570,7 +570,7 @@ void syncCommand(client *c) {
      * the client about already issued commands. We need a fresh reply
      * buffer registering the differences between the BGSAVE and the current
      * dataset, so that we can copy to other slaves if needed. */
-    if (listLength(c->reply) != 0 || c->bufpos != 0) {
+    if (clientHasPendingReplies(c)) {
         addReplyError(c,"SYNC and PSYNC are invalid with pending output");
         return;
     }
@@ -1924,7 +1924,7 @@ void replicationResurrectCachedMaster(int newfd) {
 
     /* We may also need to install the write handler as well if there is
      * pending data in the write buffers. */
-    if (server.master->bufpos || listLength(server.master->reply)) {
+    if (clientHasPendingReplies(server.master)) {
         if (aeCreateFileEvent(server.el, newfd, AE_WRITABLE,
                           sendReplyToClient, server.master)) {
             serverLog(LL_WARNING,"Error resurrecting the cached master, impossible to add the writable handler: %s", strerror(errno));