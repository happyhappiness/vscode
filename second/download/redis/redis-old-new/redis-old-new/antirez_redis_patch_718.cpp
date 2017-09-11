@@ -627,45 +627,37 @@ int rdbSaveKeyValuePair(rio *rdb, robj *key, robj *val,
     return 1;
 }
 
-/* Save the DB on disk. Return REDIS_ERR on error, REDIS_OK on success */
-int rdbSave(char *filename) {
+/* Produces a dump of the database in RDB format sending it to the specified
+ * Redis I/O channel. On success REDIS_OK is returned, otherwise REDIS_ERR
+ * is returned and part of the output, or all the output, can be
+ * missing because of I/O errors.
+ *
+ * When the function returns REDIS_ERR and if 'error' is not NULL, the
+ * integer pointed by 'error' is set to the value of errno just after the I/O
+ * error. */
+int rdbSaveRio(rio *rdb, int *error) {
     dictIterator *di = NULL;
     dictEntry *de;
-    char tmpfile[256];
     char magic[10];
     int j;
     long long now = mstime();
-    FILE *fp;
-    rio rdb;
     uint64_t cksum;
 
-    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
-    fp = fopen(tmpfile,"w");
-    if (!fp) {
-        redisLog(REDIS_WARNING, "Failed opening .rdb for saving: %s",
-            strerror(errno));
-        return REDIS_ERR;
-    }
-
-    rioInitWithFile(&rdb,fp);
     if (server.rdb_checksum)
-        rdb.update_cksum = rioGenericUpdateChecksum;
+        rdb->update_cksum = rioGenericUpdateChecksum;
     snprintf(magic,sizeof(magic),"REDIS%04d",REDIS_RDB_VERSION);
-    if (rdbWriteRaw(&rdb,magic,9) == -1) goto werr;
+    if (rdbWriteRaw(rdb,magic,9) == -1) goto werr;
 
     for (j = 0; j < server.dbnum; j++) {
         redisDb *db = server.db+j;
         dict *d = db->dict;
         if (dictSize(d) == 0) continue;
         di = dictGetSafeIterator(d);
-        if (!di) {
-            fclose(fp);
-            return REDIS_ERR;
-        }
+        if (!di) return REDIS_ERR;
 
         /* Write the SELECT DB opcode */
-        if (rdbSaveType(&rdb,REDIS_RDB_OPCODE_SELECTDB) == -1) goto werr;
-        if (rdbSaveLen(&rdb,j) == -1) goto werr;
+        if (rdbSaveType(rdb,REDIS_RDB_OPCODE_SELECTDB) == -1) goto werr;
+        if (rdbSaveLen(rdb,j) == -1) goto werr;
 
         /* Iterate this DB writing every entry */
         while((de = dictNext(di)) != NULL) {
@@ -675,20 +667,74 @@ int rdbSave(char *filename) {
 
             initStaticStringObject(key,keystr);
             expire = getExpire(db,&key);
-            if (rdbSaveKeyValuePair(&rdb,&key,o,expire,now) == -1) goto werr;
+            if (rdbSaveKeyValuePair(rdb,&key,o,expire,now) == -1) goto werr;
         }
         dictReleaseIterator(di);
     }
     di = NULL; /* So that we don't release it again on error. */
 
     /* EOF opcode */
-    if (rdbSaveType(&rdb,REDIS_RDB_OPCODE_EOF) == -1) goto werr;
+    if (rdbSaveType(rdb,REDIS_RDB_OPCODE_EOF) == -1) goto werr;
 
     /* CRC64 checksum. It will be zero if checksum computation is disabled, the
      * loading code skips the check in this case. */
-    cksum = rdb.cksum;
+    cksum = rdb->cksum;
     memrev64ifbe(&cksum);
-    if (rioWrite(&rdb,&cksum,8) == 0) goto werr;
+    if (rioWrite(rdb,&cksum,8) == 0) goto werr;
+    return REDIS_OK;
+
+werr:
+    if (error) *error = errno;
+    if (di) dictReleaseIterator(di);
+    return REDIS_ERR;
+}
+
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
+/* Save the DB on disk. Return REDIS_ERR on error, REDIS_OK on success. */
+int rdbSave(char *filename) {
+    char tmpfile[256];
+    FILE *fp;
+    rio rdb;
+    int error;
+
+    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
+    fp = fopen(tmpfile,"w");
+    if (!fp) {
+        redisLog(REDIS_WARNING, "Failed opening .rdb for saving: %s",
+            strerror(errno));
+        return REDIS_ERR;
+    }
+
+    rioInitWithFile(&rdb,fp);
+    if (rdbSaveRio(&rdb,&error) == REDIS_ERR) {
+        errno = error;
+        goto werr;
+    }
 
     /* Make sure data will not remain on the OS's output buffers */
     if (fflush(fp) == EOF) goto werr;
@@ -712,7 +758,6 @@ int rdbSave(char *filename) {
     fclose(fp);
     unlink(tmpfile);
     redisLog(REDIS_WARNING,"Write error saving DB on disk: %s", strerror(errno));
-    if (di) dictReleaseIterator(di);
     return REDIS_ERR;
 }
 
@@ -757,6 +802,7 @@ int rdbSaveBackground(char *filename) {
         redisLog(REDIS_NOTICE,"Background saving started by pid %d",childpid);
         server.rdb_save_time_start = time(NULL);
         server.rdb_child_pid = childpid;
+        server.rdb_child_type = REDIS_RDB_CHILD_TYPE_DISK;
         updateDictResizePolicy();
         return REDIS_OK;
     }
@@ -1191,8 +1237,9 @@ int rdbLoad(char *filename) {
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
@@ -1217,11 +1264,258 @@ void backgroundSaveDoneHandler(int exitcode, int bysignal) {
             server.lastbgsave_status = REDIS_ERR;
     }
     server.rdb_child_pid = -1;
+    server.rdb_child_type = REDIS_RDB_CHILD_TYPE_NONE;
     server.rdb_save_time_last = time(NULL)-server.rdb_save_time_start;
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
+    uint64_t *ok_slaves;
+
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
+
+    /* If the child returns an OK exit code, read the set of slave client
+     * IDs and the associated status code. We'll terminate all the slaves
+     * in error state.
+     *
+     * If the process returned an error, consider the list of slaves that
+     * can continue to be emtpy, so that it's just a special case of the
+     * normal code path. */
+    ok_slaves = zmalloc(sizeof(uint64_t)); /* Make space for the count. */
+    ok_slaves[0] = 0;
+    if (!bysignal && exitcode == 0) {
+        int readlen = sizeof(uint64_t);
+
+        if (read(server.rdb_pipe_read_result_from_child, ok_slaves, readlen) ==
+                 readlen)
+        {
+            readlen = ok_slaves[0]*sizeof(uint64_t)*2;
+
+            /* Make space for enough elements as specified by the first
+             * uint64_t element in the array. */
+            ok_slaves = zrealloc(ok_slaves,sizeof(uint64_t)+readlen);
+            if (readlen &&
+                read(server.rdb_pipe_read_result_from_child, ok_slaves+1,
+                     readlen) != readlen)
+            {
+                ok_slaves[0] = 0;
+            }
+        }
+    }
+
+    close(server.rdb_pipe_read_result_from_child);
+    close(server.rdb_pipe_write_result_to_parent);
+
+    /* We can continue the replication process with all the slaves that
+     * correctly received the full payload. Others are terminated. */
+    listNode *ln;
+    listIter li;
+
+    listRewind(server.slaves,&li);
+    while((ln = listNext(&li))) {
+        redisClient *slave = ln->value;
+
+        if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_END) {
+            uint64_t j;
+            int errorcode = 0;
+
+            /* Search for the slave ID in the reply. In order for a slave to
+             * continue the replication process, we need to find it in the list,
+             * and it must have an error code set to 0 (which means success). */
+            for (j = 0; j < ok_slaves[0]; j++) {
+                if (slave->id == ok_slaves[2*j+1]) {
+                    errorcode = ok_slaves[2*j+2];
+                    break; /* Found in slaves list. */
+                }
+            }
+            if (j == ok_slaves[0] || errorcode != 0) {
+                redisLog(REDIS_WARNING,
+                "Closing slave %s: child->slave RDB transfer failed: %s",
+                    replicationGetSlaveName(slave),
+                    (errorcode == 0) ? "RDB transfer child aborted"
+                                     : strerror(errorcode));
+                freeClient(slave);
+            } else {
+                redisLog(REDIS_WARNING,
+                "Slave %s correctly received the streamed RDB file.",
+                    replicationGetSlaveName(slave));
+                /* Restore the socket as non-blocking. */
+                anetNonBlock(NULL,slave->fd);
+                anetSendTimeout(NULL,slave->fd,0);
+            }
+        }
+    }
+    zfree(ok_slaves);
+
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
+    uint64_t *clientids;
+    int numfds;
+    listNode *ln;
+    listIter li;
+    pid_t childpid;
+    long long start;
+    int pipefds[2];
+
+    if (server.rdb_child_pid != -1) return REDIS_ERR;
+
+    /* Before to fork, create a pipe that will be used in order to
+     * send back to the parent the IDs of the slaves that successfully
+     * received all the writes. */
+    if (pipe(pipefds) == -1) return REDIS_ERR;
+    server.rdb_pipe_read_result_from_child = pipefds[0];
+    server.rdb_pipe_write_result_to_parent = pipefds[1];
+
+    /* Collect the file descriptors of the slaves we want to transfer
+     * the RDB to, which are i WAIT_BGSAVE_START state. */
+    fds = zmalloc(sizeof(int)*listLength(server.slaves));
+    /* We also allocate an array of corresponding client IDs. This will
+     * be useful for the child process in order to build the report
+     * (sent via unix pipe) that will be sent to the parent. */
+    clientids = zmalloc(sizeof(uint64_t)*listLength(server.slaves));
+    numfds = 0;
+
+    listRewind(server.slaves,&li);
+    while((ln = listNext(&li))) {
+        redisClient *slave = ln->value;
+
+        if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) {
+            clientids[numfds] = slave->id;
+            fds[numfds++] = slave->fd;
+            slave->replstate = REDIS_REPL_WAIT_BGSAVE_END;
+            /* Put the socket in non-blocking mode to simplify RDB transfer.
+             * We'll restore it when the children returns (since duped socket
+             * will share the O_NONBLOCK attribute with the parent). */
+            anetBlock(NULL,slave->fd);
+            anetSendTimeout(NULL,slave->fd,server.repl_timeout*1000);
+        }
+    }
+
+    /* Create the child process. */
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
+        if (retval == REDIS_OK && rioFlush(&slave_sockets) == 0)
+            retval = REDIS_ERR;
+
+        if (retval == REDIS_OK) {
+            size_t private_dirty = zmalloc_get_private_dirty();
+
+            if (private_dirty) {
+                redisLog(REDIS_NOTICE,
+                    "RDB: %zu MB of memory used by copy-on-write",
+                    private_dirty/(1024*1024));
+            }
+
+            /* If we are returning OK, at least one slave was served
+             * with the RDB file as expected, so we need to send a report
+             * to the parent via the pipe. The format of the message is:
+             *
+             * <len> <slave[0].id> <slave[0].error> ...
+             *
+             * len, slave IDs, and slave errors, are all uint64_t integers,
+             * so basically the reply is composed of 64 bits for the len field
+             * plus 2 additional 64 bit integers for each entry, for a total
+             * of 'len' entries.
+             *
+             * The 'id' represents the slave's client ID, so that the master
+             * can match the report with a specific slave, and 'error' is
+             * set to 0 if the replication process terminated with a success
+             * or the error code if an error occurred. */
+            void *msg = zmalloc(sizeof(uint64_t)*(1+2*numfds));
+            uint64_t *len = msg;
+            uint64_t *ids = len+1;
+            int j, msglen;
+
+            *len = numfds;
+            for (j = 0; j < numfds; j++) {
+                *ids++ = clientids[j];
+                *ids++ = slave_sockets.io.fdset.state[j];
+            }
+
+            /* Write the message to the parent. If we have no good slaves or
+             * we are unable to transfer the message to the parent, we exit
+             * with an error so that the parent will abort the replication
+             * process with all the childre that were waiting. */
+            msglen = sizeof(uint64_t)*(1+2*numfds);
+            if (*len == 0 ||
+                write(server.rdb_pipe_write_result_to_parent,msg,msglen)
+                != msglen)
+            {
+                retval = REDIS_ERR;
+            }
+        }
+        exitFromChild((retval == REDIS_OK) ? 0 : 1);
+    } else {
+        /* Parent */
+        zfree(clientids); /* Not used by parent. Free ASAP. */
+        server.stat_fork_time = ustime()-start;
+        server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
+        latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
+        if (childpid == -1) {
+            redisLog(REDIS_WARNING,"Can't save in background: fork: %s",
+                strerror(errno));
+            zfree(fds);
+            close(pipefds[0]);
+            close(pipefds[1]);
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