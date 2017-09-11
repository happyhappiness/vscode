@@ -1347,15 +1347,15 @@ void backgroundSaveDoneHandlerSocket(int exitcode, int bysignal) {
             }
             if (j == ok_slaves[0] || errorcode != 0) {
                 redisLog(REDIS_WARNING,
-                "Closing slave %llu: child->slave RDB transfer failed: %s",
-                    slave->id,
+                "Closing slave %s: child->slave RDB transfer failed: %s",
+                    replicationGetSlaveName(slave),
                     (errorcode == 0) ? "RDB transfer child aborted"
                                      : strerror(errorcode));
                 freeClient(slave);
             } else {
                 redisLog(REDIS_WARNING,
-                "Slave %llu correctly received the streamed RDB file.",
-                slave->id);
+                "Slave %s correctly received the streamed RDB file.",
+                    replicationGetSlaveName(slave));
                 /* Restore the socket as non-blocking. */
                 anetNonBlock(NULL,slave->fd);
                 anetSendTimeout(NULL,slave->fd,0);