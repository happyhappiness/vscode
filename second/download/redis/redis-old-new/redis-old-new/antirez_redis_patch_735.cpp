@@ -1274,7 +1274,13 @@ void backgroundSaveDoneHandlerDisk(int exitcode, int bysignal) {
 
 /* A background saving child (BGSAVE) terminated its work. Handle this.
  * This function covers the case of RDB -> Salves socket transfers for
- * diskless replication. */
+ * diskless replication.
+ *
+ * TODO:
+ * 1) Read from the pipe the set of IDs which are fine. This should be
+ *    just an uint32_t with the len, and N pid_t elements.
+ * 2) Close all the slaves in state REDIS_REPL_WAIT_BGSAVE_END but are
+ *    not reported as "transfer ok" by the child. */
 void backgroundSaveDoneHandlerSocket(int exitcode, int bysignal) {
     if (!bysignal && exitcode == 0) {
         redisLog(REDIS_NOTICE,
@@ -1288,8 +1294,18 @@ void backgroundSaveDoneHandlerSocket(int exitcode, int bysignal) {
     server.rdb_child_pid = -1;
     server.rdb_child_type = REDIS_RDB_CHILD_TYPE_NONE;
     server.rdb_save_time_start = -1;
-    /* Possibly there are slaves waiting for a BGSAVE in order to be served
-     * (the first stage of SYNC is a bulk transfer of dump.rdb) */
+    /* Read the set of slave client IDs that currently received the full
+     * RDB payload, closing all the slaves which are not among the ones
+     * listed. */
+
+    /* TODO ... */
+
+    /* Close the pipe FDs. */
+
+    /* TODO ... */
+
+    /* We can continue the replication process with all the slaves that
+     * correctly received the full payload. */
     updateSlavesWaitingBgsave((!bysignal && exitcode == 0) ? REDIS_OK : REDIS_ERR, REDIS_RDB_CHILD_TYPE_SOCKET);
 }
 
@@ -1317,9 +1333,19 @@ int rdbSaveToSlavesSockets(void) {
     listIter li;
     pid_t childpid;
     long long start;
+    int pipefds[2];
 
     if (server.rdb_child_pid != -1) return REDIS_ERR;
 
+    /* Before to fork, create a pipe that will be used in order to
+     * send back to the parent the IDs of the slaves that successfully
+     * received all the writes. */
+    if (pipe(pipefds) == -1) return REDIS_ERR;
+    server.rdb_pipe_read_result_from_child = pipefds[0];
+    server.rdb_pipe_write_result_to_parent = pipefds[1];
+
+    /* Collect the file descriptors of the slaves we want to transfer
+     * the RDB to, which are i WAIT_BGSAVE_START state. */
     fds = zmalloc(sizeof(int)*listLength(server.slaves));
     numfds = 0;
 
@@ -1333,7 +1359,7 @@ int rdbSaveToSlavesSockets(void) {
         }
     }
 
-    /* Fork ... */
+    /* Create the child process. */
     start = ustime();
     if ((childpid = fork()) == 0) {
         /* Child */
@@ -1365,6 +1391,9 @@ int rdbSaveToSlavesSockets(void) {
         if (childpid == -1) {
             redisLog(REDIS_WARNING,"Can't save in background: fork: %s",
                 strerror(errno));
+            zfree(fds);
+            close(pipefds[0]);
+            close(pipefds[1]);
             return REDIS_ERR;
         }
         redisLog(REDIS_NOTICE,"Background RDB transfer started by pid %d",childpid);