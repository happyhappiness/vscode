@@ -652,15 +652,16 @@ void replconfCommand(redisClient *c) {
  *
  * It does a few things:
  *
- * 1) Put the slave in ONLINE state.
+ * 1) Put the slave in ONLINE state (useless when the function is called
+ *    because state is already ONLINE but repl_put_online_on_ack is true).
  * 2) Make sure the writable event is re-installed, since calling the SYNC
  *    command disables it, so that we can accumulate output buffer without
  *    sending it to the slave.
  * 3) Update the count of good slaves. */
 void putSlaveOnline(redisClient *slave) {
     slave->replstate = REDIS_REPL_ONLINE;
     slave->repl_put_online_on_ack = 0;
-    slave->repl_ack_time = server.unixtime;
+    slave->repl_ack_time = server.unixtime; /* Prevent false timeout. */
     if (aeCreateFileEvent(server.el, slave->fd, AE_WRITABLE,
         sendReplyToClient, slave) == AE_ERR) {
         redisLog(REDIS_WARNING,"Unable to register writable event for slave bulk transfer: %s", strerror(errno));
@@ -773,7 +774,7 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
                  * is technically online now. */
                 slave->replstate = REDIS_REPL_ONLINE;
                 slave->repl_put_online_on_ack = 1;
-                slave->repl_ack_time = server.unixtime;
+                slave->repl_ack_time = server.unixtime; /* Timeout otherwise. */
             } else {
                 if (bgsaveerr != REDIS_OK) {
                     freeClient(slave);