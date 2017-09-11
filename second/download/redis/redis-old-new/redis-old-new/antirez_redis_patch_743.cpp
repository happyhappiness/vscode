@@ -82,7 +82,7 @@ void resizeReplicationBacklog(long long newsize) {
         server.repl_backlog = zmalloc(server.repl_backlog_size);
         server.repl_backlog_histlen = 0;
         server.repl_backlog_idx = 0;
-        /* Next byte we have is... the next since the buffer is emtpy. */
+        /* Next byte we have is... the next since the buffer is empty. */
         server.repl_backlog_off = server.master_repl_offset+1;
     }
 }
@@ -200,7 +200,7 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
 
             /* We need to feed the buffer with the object as a bulk reply
              * not just as a plain string, so create the $..CRLF payload len
-             * ad add the final CRLF */
+             * and add the final CRLF */
             aux[0] = '$';
             len = ll2string(aux+1,sizeof(aux)-1,objlen);
             aux[len+1] = '\r';
@@ -376,7 +376,7 @@ int masterTryPartialResynchronization(redisClient *c) {
     listAddNodeTail(server.slaves,c);
     /* We can't use the connection buffers since they are used to accumulate
      * new commands at this stage. But we are sure the socket send buffer is
-     * emtpy so this write will never fail actually. */
+     * empty so this write will never fail actually. */
     buflen = snprintf(buf,sizeof(buf),"+CONTINUE\r\n");
     if (write(c->fd,buf,buflen) != buflen) {
         freeClientAsync(c);
@@ -408,7 +408,7 @@ int masterTryPartialResynchronization(redisClient *c) {
     return REDIS_ERR;
 }
 
-/* SYNC ad PSYNC command implemenation. */
+/* SYNC and PSYNC command implemenation. */
 void syncCommand(redisClient *c) {
     /* ignore SYNC if already slave or in monitor mode */
     if (c->flags & REDIS_SLAVE) return;
@@ -1460,7 +1460,7 @@ void replicationDiscardCachedMaster(void) {
 /* Turn the cached master into the current master, using the file descriptor
  * passed as argument as the socket for the new master.
  *
- * This funciton is called when successfully setup a partial resynchronization
+ * This function is called when successfully setup a partial resynchronization
  * so the stream of data that we'll receive will start from were this
  * master left. */
 void replicationResurrectCachedMaster(int newfd) {
@@ -1750,7 +1750,7 @@ long long replicationGetSlaveOffset(void) {
 
 /* --------------------------- REPLICATION CRON  ---------------------------- */
 
-/* Replication cron funciton, called 1 time per second. */
+/* Replication cron function, called 1 time per second. */
 void replicationCron(void) {
     /* Non blocking connection timeout? */
     if (server.masterhost &&