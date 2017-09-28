 /* Replication cron function, called 1 time per second. */
 void replicationCron(void) {
     static long long replication_cron_loops = 0;
 
     /* Non blocking connection timeout? */
     if (server.masterhost &&
-        (server.repl_state == REDIS_REPL_CONNECTING ||
+        (server.repl_state == REPL_STATE_CONNECTING ||
          slaveIsInHandshakeState()) &&
          (time(NULL)-server.repl_transfer_lastio) > server.repl_timeout)
     {
-        redisLog(REDIS_WARNING,"Timeout connecting to the MASTER...");
-        undoConnectWithMaster();
+        serverLog(LL_WARNING,"Timeout connecting to the MASTER...");
+        cancelReplicationHandshake();
     }
 
     /* Bulk transfer I/O timeout? */
-    if (server.masterhost && server.repl_state == REDIS_REPL_TRANSFER &&
+    if (server.masterhost && server.repl_state == REPL_STATE_TRANSFER &&
         (time(NULL)-server.repl_transfer_lastio) > server.repl_timeout)
     {
-        redisLog(REDIS_WARNING,"Timeout receiving bulk data from MASTER... If the problem persists try to set the 'repl-timeout' parameter in redis.conf to a larger value.");
-        replicationAbortSyncTransfer();
+        serverLog(LL_WARNING,"Timeout receiving bulk data from MASTER... If the problem persists try to set the 'repl-timeout' parameter in redis.conf to a larger value.");
+        cancelReplicationHandshake();
     }
 
     /* Timed out master when we are an already connected slave? */
-    if (server.masterhost && server.repl_state == REDIS_REPL_CONNECTED &&
+    if (server.masterhost && server.repl_state == REPL_STATE_CONNECTED &&
         (time(NULL)-server.master->lastinteraction) > server.repl_timeout)
     {
-        redisLog(REDIS_WARNING,"MASTER timeout: no data nor PING received...");
+        serverLog(LL_WARNING,"MASTER timeout: no data nor PING received...");
         freeClient(server.master);
     }
 
     /* Check if we should connect to a MASTER */
-    if (server.repl_state == REDIS_REPL_CONNECT) {
-        redisLog(REDIS_NOTICE,"Connecting to MASTER %s:%d",
+    if (server.repl_state == REPL_STATE_CONNECT) {
+        serverLog(LL_NOTICE,"Connecting to MASTER %s:%d",
             server.masterhost, server.masterport);
-        if (connectWithMaster() == REDIS_OK) {
-            redisLog(REDIS_NOTICE,"MASTER <-> SLAVE sync started");
+        if (connectWithMaster() == C_OK) {
+            serverLog(LL_NOTICE,"MASTER <-> SLAVE sync started");
         }
     }
 
     /* Send ACK to master from time to time.
      * Note that we do not send periodic acks to masters that don't
      * support PSYNC and replication offsets. */
     if (server.masterhost && server.master &&
-        !(server.master->flags & REDIS_PRE_PSYNC))
+        !(server.master->flags & CLIENT_PRE_PSYNC))
         replicationSendAck();
 
     /* If we have attached slaves, PING them from time to time.
      * So slaves can implement an explicit timeout to masters, and will
      * be able to detect a link disconnection even if the TCP connection
      * will not actually go down. */
