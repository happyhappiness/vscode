@@ -611,6 +611,29 @@ void replconfCommand(redisClient *c) {
     addReply(c,shared.ok);
 }
 
+/* This function puts a slave in the online state, and should be called just
+ * after a slave received the RDB file for the initial synchronization, and
+ * we are finally ready to send the incremental stream of commands.
+ *
+ * It does a few things:
+ *
+ * 1) Put the slave in ONLINE state.
+ * 2) Make sure the writable event is re-installed, since calling the SYNC
+ *    command disables it, so that we can accumulate output buffer without
+ *    sending it to the slave.
+ * 3) Update the count of good slaves. */
+void putSlaveOnline(redisClient *slave) {
+    slave->replstate = REDIS_REPL_ONLINE;
+    slave->repl_ack_time = server.unixtime;
+    if (aeCreateFileEvent(server.el, slave->fd, AE_WRITABLE,
+        sendReplyToClient, slave) == AE_ERR) {
+        redisLog(REDIS_WARNING,"Unable to register writable event for slave bulk transfer: %s", strerror(errno));
+        freeClient(slave);
+        return;
+    }
+    refreshGoodSlavesCount();
+}
+
 void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
     redisClient *slave = privdata;
     REDIS_NOTUSED(el);
@@ -661,16 +684,8 @@ void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
         close(slave->repldbfd);
         slave->repldbfd = -1;
         aeDeleteFileEvent(server.el,slave->fd,AE_WRITABLE);
-        slave->replstate = REDIS_REPL_ONLINE;
-        slave->repl_ack_time = server.unixtime;
-        if (aeCreateFileEvent(server.el, slave->fd, AE_WRITABLE,
-            sendReplyToClient, slave) == AE_ERR) {
-            redisLog(REDIS_WARNING,"Unable to register writable event for slave bulk transfer: %s", strerror(errno));
-            freeClient(slave);
-            return;
-        }
-        refreshGoodSlavesCount();
-        redisLog(REDIS_NOTICE,"Synchronization with slave succeeded");
+        putSlaveOnline(slave);
+        redisLog(REDIS_NOTICE,"Synchronization with slave succeeded (disk)");
     }
 }
 
@@ -700,27 +715,38 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
         } else if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_END) {
             struct redis_stat buf;
 
-            if (bgsaveerr != REDIS_OK) {
-                freeClient(slave);
-                redisLog(REDIS_WARNING,"SYNC failed. BGSAVE child returned an error");
-                continue;
-            }
-            if ((slave->repldbfd = open(server.rdb_filename,O_RDONLY)) == -1 ||
-                redis_fstat(slave->repldbfd,&buf) == -1) {
-                freeClient(slave);
-                redisLog(REDIS_WARNING,"SYNC failed. Can't open/stat DB after BGSAVE: %s", strerror(errno));
-                continue;
-            }
-            slave->repldboff = 0;
-            slave->repldbsize = buf.st_size;
-            slave->replstate = REDIS_REPL_SEND_BULK;
-            slave->replpreamble = sdscatprintf(sdsempty(),"$%lld\r\n",
-                (unsigned long long) slave->repldbsize);
-
-            aeDeleteFileEvent(server.el,slave->fd,AE_WRITABLE);
-            if (aeCreateFileEvent(server.el, slave->fd, AE_WRITABLE, sendBulkToSlave, slave) == AE_ERR) {
-                freeClient(slave);
-                continue;
+            /* If this was an RDB on disk save, we have to prepare to send
+             * the RDB from disk to the slave socket. Otherwise if this was
+             * already an RDB -> Slaves socket transfer, used in the case of
+             * diskless replication, our work is trivial, we can just put
+             * the slave online. */
+            if (type == REDIS_RDB_CHILD_TYPE_SOCKET) {
+                putSlaveOnline(slave);
+            redisLog(REDIS_NOTICE,
+                "Synchronization with slave succeeded (socket)");
+            } else {
+                if (bgsaveerr != REDIS_OK) {
+                    freeClient(slave);
+                    redisLog(REDIS_WARNING,"SYNC failed. BGSAVE child returned an error");
+                    continue;
+                }
+                if ((slave->repldbfd = open(server.rdb_filename,O_RDONLY)) == -1 ||
+                    redis_fstat(slave->repldbfd,&buf) == -1) {
+                    freeClient(slave);
+                    redisLog(REDIS_WARNING,"SYNC failed. Can't open/stat DB after BGSAVE: %s", strerror(errno));
+                    continue;
+                }
+                slave->repldboff = 0;
+                slave->repldbsize = buf.st_size;
+                slave->replstate = REDIS_REPL_SEND_BULK;
+                slave->replpreamble = sdscatprintf(sdsempty(),"$%lld\r\n",
+                    (unsigned long long) slave->repldbsize);
+
+                aeDeleteFileEvent(server.el,slave->fd,AE_WRITABLE);
+                if (aeCreateFileEvent(server.el, slave->fd, AE_WRITABLE, sendBulkToSlave, slave) == AE_ERR) {
+                    freeClient(slave);
+                    continue;
+                }
             }
         }
     }