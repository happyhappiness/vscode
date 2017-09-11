@@ -40,6 +40,7 @@
 #include <sys/wait.h>
 
 void aofUpdateCurrentSize(void);
+void aofClosePipes(void);
 
 /* ----------------------------------------------------------------------------
  * AOF rewrite buffer implementation.
@@ -75,16 +76,38 @@ void aofRewriteBufferReset(void) {
 
 /* Return the current size of the AOF rerwite buffer. */
 unsigned long aofRewriteBufferSize(void) {
-    listNode *ln = listLast(server.aof_rewrite_buf_blocks);
-    aofrwblock *block = ln ? ln->value : NULL;
+    listNode *ln;
+    listIter li;
+    unsigned long size = 0;
 
-    if (block == NULL) return 0;
-    unsigned long size =
-        (listLength(server.aof_rewrite_buf_blocks)-1) * AOF_RW_BUF_BLOCK_SIZE;
-    size += block->used;
+    listRewind(server.aof_rewrite_buf_blocks,&li);
+    while((ln = listNext(&li))) {
+        aofrwblock *block = listNodeValue(ln);
+        size += block->used;
+    }
     return size;
 }
 
+/* Event handler used to send data to the child process doing the AOF
+ * rewrite. We send pieces of our AOF differences buffer so that the final
+ * write when the child finishes the rewrite will be small. */
+void aofChildWriteDiffData(aeEventLoop *el, int fd, void *privdata, int mask) {
+    listNode *ln = listFirst(server.aof_rewrite_buf_blocks);
+    aofrwblock *block = ln ? ln->value : NULL;
+    ssize_t nwritten;
+
+    if (server.aof_stop_sending_diff || !block) {
+        aeDeleteFileEvent(server.el,server.aof_pipe_write_data_to_child,
+                          AE_WRITABLE);
+        return;
+    }
+    nwritten = write(server.aof_pipe_write_data_to_child,block->buf,block->used);
+    if (nwritten <= 0) return;
+    memmove(block->buf,block->buf+nwritten,block->used-nwritten);
+    block->used -= nwritten;
+    if (block->used == 0) listDelNode(server.aof_rewrite_buf_blocks,ln);
+}
+
 /* Append data to the AOF rewrite buffer, allocating new blocks if needed. */
 void aofRewriteBufferAppend(unsigned char *s, unsigned long len) {
     listNode *ln = listLast(server.aof_rewrite_buf_blocks);
@@ -123,6 +146,13 @@ void aofRewriteBufferAppend(unsigned char *s, unsigned long len) {
             }
         }
     }
+
+    /* Install a file event to send data to the rewrite child if there is
+     * not one already. */
+    if (aeGetFileEvents(server.el,server.aof_pipe_write_data_to_child) == 0) {
+        aeCreateFileEvent(server.el, server.aof_pipe_write_data_to_child,
+            AE_WRITABLE, aofChildWriteDiffData, NULL);
+    }
 }
 
 /* Write the buffer (possibly composed of multiple blocks) into the specified
@@ -184,6 +214,8 @@ void stopAppendOnly(void) {
         aofRemoveTempFile(server.aof_child_pid);
         server.aof_child_pid = -1;
         server.aof_rewrite_time_start = -1;
+        /* close pipes used for IPC between the two processes. */
+        aofClosePipes();
     }
 }
 
@@ -901,6 +933,19 @@ int rewriteHashObject(rio *r, robj *key, robj *o) {
     return 1;
 }
 
+/* This function is called by the child rewriting the AOF file to read
+ * the difference accumulated from the parent into a buffer, that is
+ * concatenated at the end of the rewrite. */
+void aofReadDiffFromParent(void) {
+    char buf[1024*16];
+    ssize_t nread;
+
+    while ((nread =
+            read(server.aof_pipe_read_data_from_parent,buf,sizeof(buf))) > 0) {
+        server.aof_child_diff = sdscatlen(server.aof_child_diff,buf,nread);
+    }
+}
+
 /* Write a sequence of commands able to fully rebuild the dataset into
  * "filename". Used both by REWRITEAOF and BGREWRITEAOF.
  *
@@ -916,6 +961,8 @@ int rewriteAppendOnlyFile(char *filename) {
     char tmpfile[256];
     int j;
     long long now = mstime();
+    unsigned long ops = 0;
+    char byte;
 
     /* Note that we have to use a different temp name here compared to the
      * one used by rewriteAppendOnlyFileBackground() function. */
@@ -926,6 +973,7 @@ int rewriteAppendOnlyFile(char *filename) {
         return REDIS_ERR;
     }
 
+    server.aof_child_diff = sdsempty();
     rioInitWithFile(&aof,fp);
     if (server.aof_rewrite_incremental_fsync)
         rioSetAutoSync(&aof,REDIS_AOF_AUTOSYNC_BYTES);
@@ -985,10 +1033,27 @@ int rewriteAppendOnlyFile(char *filename) {
                 if (rioWriteBulkObject(&aof,&key) == 0) goto werr;
                 if (rioWriteBulkLongLong(&aof,expiretime) == 0) goto werr;
             }
+            /* Read some diff from the parent process from time to time. */
+            if (ops++ % 1000) aofReadDiffFromParent();
         }
         dictReleaseIterator(di);
     }
 
+    /* Ask the master to stop sending diffs. */
+    write(server.aof_pipe_write_ack_to_parent,"!",1);
+    if (read(server.aof_pipe_read_ack_from_parent,&byte,1) != 1 ||
+        byte != '!') goto werr;
+
+    /* Read the final diff if any. */
+    aofReadDiffFromParent();
+
+    /* Write the received diff to the file. */
+    redisLog(REDIS_NOTICE,
+        "Concatenating %llu bytes of AOF diff received from parent.",
+        (unsigned long long) sdslen(server.aof_child_diff));
+    if (rioWrite(&aof,server.aof_child_diff,sdslen(server.aof_child_diff)) == 0)
+        goto werr;
+
     /* Make sure data will not remain on the OS's output buffers */
     if (fflush(fp) == EOF) goto werr;
     if (fsync(fileno(fp)) == -1) goto werr;
@@ -1012,6 +1077,74 @@ int rewriteAppendOnlyFile(char *filename) {
     return REDIS_ERR;
 }
 
+/* ----------------------------------------------------------------------------
+ * AOF rewrite pipes for IPC
+ * -------------------------------------------------------------------------- */
+
+/* This event handler is called when the AOF rewriting child sends us a
+ * single '!' char to signal we should stop sending buffer diffs. The
+ * parent sends a '!' as well to acknowledge. */
+void aofChildPipeReadable(aeEventLoop *el, int fd, void *privdata, int mask) {
+    char byte;
+
+    if (read(fd,&byte,1) == 1 && byte == '!') {
+        redisLog(REDIS_NOTICE,"AOF rewrite child asks to stop sending diffs.");
+        server.aof_stop_sending_diff = 1;
+        write(server.aof_pipe_write_ack_to_child,"!",1);
+    }
+    /* Remove the handler since this can be called only one time during a
+     * rewrite. */
+    aeDeleteFileEvent(server.el,server.aof_pipe_read_ack_from_child,AE_READABLE);
+}
+
+/* Create the pipes used for parent - child process IPC during rewrite.
+ * We have a data pipe used to send AOF incremental diffs to the child,
+ * and two other pipes used by the children to signal it finished with
+ * the rewrite so no more data should be written, and another for the
+ * parent to acknowledge it understood this new condition. */
+int aofCreatePipes(void) {
+    int fds[6] = {-1, -1, -1, -1, -1, -1};
+    int j;
+
+    if (pipe(fds) == -1) goto error; /* parent -> children data. */
+    if (pipe(fds+2) == -1) goto error; /* children -> parent ack. */
+    if (pipe(fds+4) == -1) goto error; /* children -> parent ack. */
+    /* Parent -> children data is non blocking. */
+    if (anetNonBlock(NULL,fds[0]) != ANET_OK) goto error;
+    if (anetNonBlock(NULL,fds[1]) != ANET_OK) goto error;
+    if (aeCreateFileEvent(server.el, fds[2], AE_READABLE, aofChildPipeReadable, NULL) == AE_ERR) goto error;
+
+    server.aof_pipe_write_data_to_child = fds[1];
+    server.aof_pipe_read_data_from_parent = fds[0];
+    server.aof_pipe_write_ack_to_parent = fds[3];
+    server.aof_pipe_read_ack_from_child = fds[2];
+    server.aof_pipe_write_ack_to_child = fds[5];
+    server.aof_pipe_read_ack_from_parent = fds[4];
+    server.aof_stop_sending_diff = 0;
+    return REDIS_OK;
+
+error:
+    redisLog(REDIS_WARNING,"Error opening /setting AOF rewrite IPC pipes: %s",
+        strerror(errno));
+    for (j = 0; j < 6; j++) if(fds[j] != -1) close(fds[j]);
+    return REDIS_ERR;
+}
+
+void aofClosePipes(void) {
+    aeDeleteFileEvent(server.el,server.aof_pipe_read_ack_from_child,AE_READABLE);
+    aeDeleteFileEvent(server.el,server.aof_pipe_write_data_to_child,AE_WRITABLE);
+    close(server.aof_pipe_write_data_to_child);
+    close(server.aof_pipe_read_data_from_parent);
+    close(server.aof_pipe_write_ack_to_parent);
+    close(server.aof_pipe_read_ack_from_child);
+    close(server.aof_pipe_write_ack_to_child);
+    close(server.aof_pipe_read_ack_from_parent);
+}
+
+/* ----------------------------------------------------------------------------
+ * AOF backgorund rewrite
+ * ------------------------------------------------------------------------- */
+
 /* This is how rewriting of the append only file in background works:
  *
  * 1) The user calls BGREWRITEAOF
@@ -1029,6 +1162,7 @@ int rewriteAppendOnlyFileBackground(void) {
     long long start;
 
     if (server.aof_child_pid != -1) return REDIS_ERR;
+    if (aofCreatePipes() != REDIS_OK) return REDIS_ERR;
     start = ustime();
     if ((childpid = fork()) == 0) {
         char tmpfile[256];
@@ -1250,6 +1384,7 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
     }
 
 cleanup:
+    aofClosePipes();
     aofRewriteBufferReset();
     aofRemoveTempFile(server.aof_child_pid);
     server.aof_child_pid = -1;