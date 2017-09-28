                 if (slave->id == ok_slaves[2*j+1]) {
                     errorcode = ok_slaves[2*j+2];
                     break; /* Found in slaves list. */
                 }
             }
             if (j == ok_slaves[0] || errorcode != 0) {
-                redisLog(REDIS_WARNING,
+                serverLog(LL_WARNING,
                 "Closing slave %s: child->slave RDB transfer failed: %s",
                     replicationGetSlaveName(slave),
                     (errorcode == 0) ? "RDB transfer child aborted"
                                      : strerror(errorcode));
                 freeClient(slave);
             } else {
-                redisLog(REDIS_WARNING,
+                serverLog(LL_WARNING,
                 "Slave %s correctly received the streamed RDB file.",
                     replicationGetSlaveName(slave));
                 /* Restore the socket as non-blocking. */
                 anetNonBlock(NULL,slave->fd);
                 anetSendTimeout(NULL,slave->fd,0);
             }
         }
     }
     zfree(ok_slaves);
 
-    updateSlavesWaitingBgsave((!bysignal && exitcode == 0) ? REDIS_OK : REDIS_ERR, REDIS_RDB_CHILD_TYPE_SOCKET);
+    updateSlavesWaitingBgsave((!bysignal && exitcode == 0) ? C_OK : C_ERR, RDB_CHILD_TYPE_SOCKET);
 }
 
 /* When a background RDB saving/transfer terminates, call the right handler. */
 void backgroundSaveDoneHandler(int exitcode, int bysignal) {
     switch(server.rdb_child_type) {
-    case REDIS_RDB_CHILD_TYPE_DISK:
+    case RDB_CHILD_TYPE_DISK:
         backgroundSaveDoneHandlerDisk(exitcode,bysignal);
         break;
-    case REDIS_RDB_CHILD_TYPE_SOCKET:
+    case RDB_CHILD_TYPE_SOCKET:
         backgroundSaveDoneHandlerSocket(exitcode,bysignal);
         break;
     default:
-        redisPanic("Unknown RDB child type.");
+        serverPanic("Unknown RDB child type.");
         break;
     }
 }
 
 /* Spawn an RDB child that writes the RDB to the sockets of the slaves
- * that are currently in REDIS_REPL_WAIT_BGSAVE_START state. */
+ * that are currently in SLAVE_STATE_WAIT_BGSAVE_START state. */
 int rdbSaveToSlavesSockets(void) {
     int *fds;
     uint64_t *clientids;
     int numfds;
     listNode *ln;
     listIter li;
     pid_t childpid;
     long long start;
     int pipefds[2];
 
-    if (server.rdb_child_pid != -1) return REDIS_ERR;
+    if (server.rdb_child_pid != -1) return C_ERR;
 
     /* Before to fork, create a pipe that will be used in order to
      * send back to the parent the IDs of the slaves that successfully
      * received all the writes. */
-    if (pipe(pipefds) == -1) return REDIS_ERR;
+    if (pipe(pipefds) == -1) return C_ERR;
     server.rdb_pipe_read_result_from_child = pipefds[0];
     server.rdb_pipe_write_result_to_parent = pipefds[1];
 
     /* Collect the file descriptors of the slaves we want to transfer
      * the RDB to, which are i WAIT_BGSAVE_START state. */
     fds = zmalloc(sizeof(int)*listLength(server.slaves));
