@@ -689,6 +689,32 @@ int rdbSaveRio(rio *rdb, int *error) {
     return REDIS_ERR;
 }
 
+/* This is just a wrapper to rdbSaveRio() that additionally adds a prefix
+ * and a suffix to the generated RDB dump. The prefix is:
+ *
+ * $EOF:<40 bytes unguessable hex string>\r\n
+ *
+ * While the suffix is the 40 bytes hex string we announced in the prefix.
+ * This way processes receiving the payload can understand when it ends
+ * without doing any processing of the content. */
+int rdbSaveRioWithEOFMark(rio *rdb, int *error) {
+    char eofmark[REDIS_EOF_MARK_SIZE];
+
+    getRandomHexChars(eofmark,REDIS_EOF_MARK_SIZE);
+    if (error) *error = 0;
+    if (rioWrite(rdb,"$EOF:",5) == 0) goto werr;
+    if (rioWrite(rdb,eofmark,REDIS_EOF_MARK_SIZE) == 0) goto werr;
+    if (rioWrite(rdb,"\r\n",2) == 0) goto werr;
+    if (rdbSaveRio(rdb,error) == REDIS_ERR) goto werr;
+    if (rioWrite(rdb,eofmark,REDIS_EOF_MARK_SIZE) == 0) goto werr;
+    return REDIS_OK;
+
+werr: /* Write error. */
+    /* Set 'error' only if not already set by rdbSaveRio() call. */
+    if (error && *error == 0) *error = errno;
+    return REDIS_ERR;
+}
+
 /* Save the DB on disk. Return REDIS_ERR on error, REDIS_OK on success. */
 int rdbSave(char *filename) {
     char tmpfile[256];
@@ -1211,8 +1237,9 @@ int rdbLoad(char *filename) {
     return REDIS_ERR; /* Just to avoid warning */
 }
 
-/* A background saving child (BGSAVE) terminated its work. Handle this. */
-void backgroundSaveDoneHandler(int exitcode, int bysignal) {
+/* A background saving child (BGSAVE) terminated its work. Handle this.
+ * This function covers the case of actual BGSAVEs. */
+void backgroundSaveDoneHandlerDisk(int exitcode, int bysignal) {
     if (!bysignal && exitcode == 0) {
         redisLog(REDIS_NOTICE,
             "Background saving terminated with success");
@@ -1242,7 +1269,113 @@ void backgroundSaveDoneHandler(int exitcode, int bysignal) {
     server.rdb_save_time_start = -1;
     /* Possibly there are slaves waiting for a BGSAVE in order to be served
      * (the first stage of SYNC is a bulk transfer of dump.rdb) */
-    updateSlavesWaitingBgsave((!bysignal && exitcode == 0) ? REDIS_OK : REDIS_ERR);
+    updateSlavesWaitingBgsave((!bysignal && exitcode == 0) ? REDIS_OK : REDIS_ERR, REDIS_RDB_CHILD_TYPE_DISK);
+}
+
+/* A background saving child (BGSAVE) terminated its work. Handle this.
+ * This function covers the case of RDB -> Salves socket transfers for
+ * diskless replication. */
+void backgroundSaveDoneHandlerSocket(int exitcode, int bysignal) {
+    if (!bysignal && exitcode == 0) {
+        redisLog(REDIS_NOTICE,
+            "Background RDB transfer terminated with success");
+    } else if (!bysignal && exitcode != 0) {
+        redisLog(REDIS_WARNING, "Background transfer error");
+    } else {
+        redisLog(REDIS_WARNING,
+            "Background transfer terminated by signal %d", bysignal);
+    }
+    server.rdb_child_pid = -1;
+    server.rdb_child_type = REDIS_RDB_CHILD_TYPE_NONE;
+    server.rdb_save_time_start = -1;
+    /* Possibly there are slaves waiting for a BGSAVE in order to be served
+     * (the first stage of SYNC is a bulk transfer of dump.rdb) */
+    updateSlavesWaitingBgsave((!bysignal && exitcode == 0) ? REDIS_OK : REDIS_ERR, REDIS_RDB_CHILD_TYPE_SOCKET);
+}
+
+/* When a background RDB saving/transfer terminates, call the right handler. */
+void backgroundSaveDoneHandler(int exitcode, int bysignal) {
+    switch(server.rdb_child_type) {
+    case REDIS_RDB_CHILD_TYPE_DISK:
+        backgroundSaveDoneHandlerDisk(exitcode,bysignal);
+        break;
+    case REDIS_RDB_CHILD_TYPE_SOCKET:
+        backgroundSaveDoneHandlerSocket(exitcode,bysignal);
+        break;
+    default:
+        redisPanic("Unknown RDB child type.");
+        break;
+    }
+}
+
+/* Spawn an RDB child that writes the RDB to the sockets of the slaves
+ * that are currently in REDIS_REPL_WAIT_BGSAVE_START state. */
+int rdbSaveToSlavesSockets(void) {
+    int *fds;
+    int numfds;
+    listNode *ln;
+    listIter li;
+    pid_t childpid;
+    long long start;
+
+    if (server.rdb_child_pid != -1) return REDIS_ERR;
+
+    fds = zmalloc(sizeof(int)*listLength(server.slaves));
+    numfds = 0;
+
+    listRewind(server.slaves,&li);
+    while((ln = listNext(&li))) {
+        redisClient *slave = ln->value;
+
+        if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) {
+            fds[numfds++] = slave->fd;
+            slave->replstate = REDIS_REPL_WAIT_BGSAVE_END;
+        }
+    }
+
+    /* Fork ... */
+    start = ustime();
+    if ((childpid = fork()) == 0) {
+        /* Child */
+        int retval;
+        rio slave_sockets;
+
+        rioInitWithFdset(&slave_sockets,fds,numfds);
+        zfree(fds);
+
+        closeListeningSockets(0);
+        redisSetProcTitle("redis-rdb-to-slaves");
+
+        retval = rdbSaveRioWithEOFMark(&slave_sockets,NULL);
+        if (retval == REDIS_OK) {
+            size_t private_dirty = zmalloc_get_private_dirty();
+
+            if (private_dirty) {
+                redisLog(REDIS_NOTICE,
+                    "RDB: %zu MB of memory used by copy-on-write",
+                    private_dirty/(1024*1024));
+            }
+        }
+        exitFromChild((retval == REDIS_OK) ? 0 : 1);
+    } else {
+        /* Parent */
+        server.stat_fork_time = ustime()-start;
+        server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
+        latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
+        if (childpid == -1) {
+            redisLog(REDIS_WARNING,"Can't save in background: fork: %s",
+                strerror(errno));
+            return REDIS_ERR;
+        }
+        redisLog(REDIS_NOTICE,"Background RDB transfer started by pid %d",childpid);
+        server.rdb_save_time_start = time(NULL);
+        server.rdb_child_pid = childpid;
+        server.rdb_child_type = REDIS_RDB_CHILD_TYPE_SOCKET;
+        updateDictResizePolicy();
+        zfree(fds);
+        return REDIS_OK;
+    }
+    return REDIS_OK; /* unreached */
 }
 
 void saveCommand(redisClient *c) {