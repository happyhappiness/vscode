     }
     return soft || hard;
 }
 
 /* Asynchronously close a client if soft or hard limit is reached on the
  * output buffer size. The caller can check if the client will be closed
- * checking if the client REDIS_CLOSE_ASAP flag is set.
+ * checking if the client CLIENT_CLOSE_ASAP flag is set.
  *
  * Note: we need to close the client asynchronously because this function is
  * called from contexts where the client can't be freed safely, i.e. from the
  * lower level functions pushing data inside the client output buffers. */
-void asyncCloseClientOnOutputBufferLimitReached(redisClient *c) {
-    redisAssert(c->reply_bytes < ULONG_MAX-(1024*64));
-    if (c->reply_bytes == 0 || c->flags & REDIS_CLOSE_ASAP) return;
+void asyncCloseClientOnOutputBufferLimitReached(client *c) {
+    serverAssert(c->reply_bytes < SIZE_MAX-(1024*64));
+    if (c->reply_bytes == 0 || c->flags & CLIENT_CLOSE_ASAP) return;
     if (checkClientOutputBufferLimits(c)) {
         sds client = catClientInfoString(sdsempty(),c);
 
         freeClientAsync(c);
-        redisLog(REDIS_WARNING,"Client %s scheduled to be closed ASAP for overcoming of output buffer limits.", client);
+        serverLog(LL_WARNING,"Client %s scheduled to be closed ASAP for overcoming of output buffer limits.", client);
         sdsfree(client);
     }
 }
 
 /* Helper function used by freeMemoryIfNeeded() in order to flush slaves
- * output buffers without returning control to the event loop. */
+ * output buffers without returning control to the event loop.
+ * This is also called by SHUTDOWN for a best-effort attempt to send
+ * slaves the latest writes. */
 void flushSlavesOutputBuffers(void) {
     listIter li;
     listNode *ln;
 
     listRewind(server.slaves,&li);
     while((ln = listNext(&li))) {
-        redisClient *slave = listNodeValue(ln);
+        client *slave = listNodeValue(ln);
         int events;
 
         /* Note that the following will not flush output buffers of slaves
          * in STATE_ONLINE but having put_online_on_ack set to true: in this
          * case the writable event is never installed, since the purpose
          * of put_online_on_ack is to postpone the moment it is installed.
          * This is what we want since slaves in this state should not receive
          * writes before the first ACK. */
         events = aeGetFileEvents(server.el,slave->fd);
         if (events & AE_WRITABLE &&
-            slave->replstate == REDIS_REPL_ONLINE &&
-            listLength(slave->reply))
+            slave->replstate == SLAVE_STATE_ONLINE &&
+            clientHasPendingReplies(slave))
         {
-            sendReplyToClient(server.el,slave->fd,slave,0);
+            writeToClient(slave->fd,slave,0);
         }
     }
 }
 
 /* Pause clients up to the specified unixtime (in ms). While clients
  * are paused no command is processed from clients, so the data set can't
