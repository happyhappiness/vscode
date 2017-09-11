@@ -816,14 +816,13 @@ void freeClientsInAsyncFreeQueue(void) {
     }
 }
 
-void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
-    client *c = privdata;
+/* Write data in output buffers to client. Return C_OK if the client
+ * is still valid after the call, C_ERR if it was freed. */
+int writeToClient(int fd, client *c) {
     ssize_t nwritten = 0, totwritten = 0;
     size_t objlen;
     size_t objmem;
     robj *o;
-    UNUSED(el);
-    UNUSED(mask);
 
     while(c->bufpos > 0 || listLength(c->reply)) {
         if (c->bufpos > 0) {
@@ -881,7 +880,7 @@ void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
             serverLog(LL_VERBOSE,
                 "Error writing to client: %s", strerror(errno));
             freeClient(c);
-            return;
+            return C_ERR;
         }
     }
     if (totwritten > 0) {
@@ -896,8 +895,19 @@ void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
         aeDeleteFileEvent(server.el,c->fd,AE_WRITABLE);
 
         /* Close connection after entire reply has been sent. */
-        if (c->flags & CLIENT_CLOSE_AFTER_REPLY) freeClient(c);
+        if (c->flags & CLIENT_CLOSE_AFTER_REPLY) {
+            freeClient(c);
+            return C_ERR;
+        }
     }
+    return C_OK;
+}
+
+/* Write event handler. Just send data to the client. */
+void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
+    UNUSED(el);
+    UNUSED(mask);
+    writeToClient(fd,privdata);
 }
 
 /* This function is called just before entering the event loop, in the hope
@@ -915,7 +925,7 @@ void handleClientsWithPendingWrites(void) {
         listDelNode(server.clients_pending_write,ln);
 
         /* Try to write buffers to the client socket. */
-        sendReplyToClient(server.el,c->fd,c,0);
+        if (writeToClient(c->fd,c) == C_ERR) continue;
 
         /* If there is nothing left, do nothing. Otherwise install
          * the write handler. */