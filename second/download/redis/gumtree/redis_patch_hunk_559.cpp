  * The goal of this function is to handle slaves waiting for a successful
  * background saving in order to perform non-blocking synchronization, and
  * to schedule a new BGSAVE if there are slaves that attached while a
  * BGSAVE was in progress, but it was not a good one for replication (no
  * other slave was accumulating differences).
  *
- * The argument bgsaveerr is REDIS_OK if the background saving succeeded
- * otherwise REDIS_ERR is passed to the function.
+ * The argument bgsaveerr is C_OK if the background saving succeeded
+ * otherwise C_ERR is passed to the function.
  * The 'type' argument is the type of the child that terminated
  * (if it had a disk or socket target). */
 void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
     listNode *ln;
     int startbgsave = 0;
     int mincapa = -1;
     listIter li;
 
     listRewind(server.slaves,&li);
     while((ln = listNext(&li))) {
-        redisClient *slave = ln->value;
+        client *slave = ln->value;
 
-        if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) {
+        if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START) {
             startbgsave = 1;
             mincapa = (mincapa == -1) ? slave->slave_capa :
                                         (mincapa & slave->slave_capa);
-        } else if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_END) {
+        } else if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_END) {
             struct redis_stat buf;
 
             /* If this was an RDB on disk save, we have to prepare to send
              * the RDB from disk to the slave socket. Otherwise if this was
              * already an RDB -> Slaves socket transfer, used in the case of
              * diskless replication, our work is trivial, we can just put
              * the slave online. */
-            if (type == REDIS_RDB_CHILD_TYPE_SOCKET) {
-                redisLog(REDIS_NOTICE,
+            if (type == RDB_CHILD_TYPE_SOCKET) {
+                serverLog(LL_NOTICE,
                     "Streamed RDB transfer with slave %s succeeded (socket). Waiting for REPLCONF ACK from slave to enable streaming",
                         replicationGetSlaveName(slave));
                 /* Note: we wait for a REPLCONF ACK message from slave in
                  * order to really put it online (install the write handler
                  * so that the accumulated data can be transfered). However
                  * we change the replication state ASAP, since our slave
                  * is technically online now. */
-                slave->replstate = REDIS_REPL_ONLINE;
+                slave->replstate = SLAVE_STATE_ONLINE;
                 slave->repl_put_online_on_ack = 1;
                 slave->repl_ack_time = server.unixtime; /* Timeout otherwise. */
             } else {
-                if (bgsaveerr != REDIS_OK) {
+                if (bgsaveerr != C_OK) {
                     freeClient(slave);
-                    redisLog(REDIS_WARNING,"SYNC failed. BGSAVE child returned an error");
+                    serverLog(LL_WARNING,"SYNC failed. BGSAVE child returned an error");
                     continue;
                 }
                 if ((slave->repldbfd = open(server.rdb_filename,O_RDONLY)) == -1 ||
                     redis_fstat(slave->repldbfd,&buf) == -1) {
                     freeClient(slave);
-                    redisLog(REDIS_WARNING,"SYNC failed. Can't open/stat DB after BGSAVE: %s", strerror(errno));
+                    serverLog(LL_WARNING,"SYNC failed. Can't open/stat DB after BGSAVE: %s", strerror(errno));
                     continue;
                 }
                 slave->repldboff = 0;
                 slave->repldbsize = buf.st_size;
-                slave->replstate = REDIS_REPL_SEND_BULK;
+                slave->replstate = SLAVE_STATE_SEND_BULK;
                 slave->replpreamble = sdscatprintf(sdsempty(),"$%lld\r\n",
                     (unsigned long long) slave->repldbsize);
 
                 aeDeleteFileEvent(server.el,slave->fd,AE_WRITABLE);
                 if (aeCreateFileEvent(server.el, slave->fd, AE_WRITABLE, sendBulkToSlave, slave) == AE_ERR) {
                     freeClient(slave);
