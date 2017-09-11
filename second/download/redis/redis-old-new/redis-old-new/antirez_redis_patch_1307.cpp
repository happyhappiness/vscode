@@ -13,6 +13,115 @@
 void aofUpdateCurrentSize(void);
 
 /* ----------------------------------------------------------------------------
+ * AOF rewrite buffer implementation.
+ *
+ * The following code implement a simple buffer used in order to accumulate
+ * changes while the background process is rewriting the AOF file.
+ *
+ * We only need to append, but can't just use realloc with a large block
+ * because 'huge' reallocs are not always handled as one could expect
+ * (via remapping of pages at OS level) but may involve copying data.
+ *
+ * For this reason we use a list of blocks, every block is
+ * AOF_RW_BUF_BLOCK_SIZE bytes.
+ * ------------------------------------------------------------------------- */
+
+#define AOF_RW_BUF_BLOCK_SIZE (1024*1024*10)    /* 10 MB per block */
+
+typedef struct aofrwblock {
+    unsigned long used, free;
+    char buf[AOF_RW_BUF_BLOCK_SIZE];
+} aofrwblock;
+
+/* This function free the old AOF rewrite buffer if needed, and initialize
+ * a fresh new one. It tests for server.aof_rewrite_buf_blocks equal to NULL
+ * so can be used for the first initialization as well. */
+void aofRewriteBufferReset(void) {
+    if (server.aof_rewrite_buf_blocks)
+        listRelease(server.aof_rewrite_buf_blocks);
+
+    server.aof_rewrite_buf_blocks = listCreate();
+    listSetFreeMethod(server.aof_rewrite_buf_blocks,zfree);
+}
+
+/* Return the current size of the AOF rerwite buffer. */
+unsigned long aofRewriteBufferSize(void) {
+    listNode *ln = listLast(server.aof_rewrite_buf_blocks);
+    aofrwblock *block = ln ? ln->value : NULL;
+
+    if (block == NULL) return 0;
+    unsigned long size =
+        (listLength(server.aof_rewrite_buf_blocks)-1) * AOF_RW_BUF_BLOCK_SIZE;
+    size += block->used;
+    return size;
+}
+
+/* Append data to the AOF rewrite buffer, allocating new blocks if needed. */
+void aofRewriteBufferAppend(unsigned char *s, unsigned long len) {
+    listNode *ln = listLast(server.aof_rewrite_buf_blocks);
+    aofrwblock *block = ln ? ln->value : NULL;
+
+    while(len) {
+        /* If we already got at least an allocated block, try appending
+         * at least some piece into it. */
+        if (block) {
+            unsigned long thislen = (block->free < len) ? block->free : len;
+            if (thislen) {  /* The current block is not already full. */
+                memcpy(block->buf+block->used, s, thislen);
+                block->used += thislen;
+                block->free -= thislen;
+                s += thislen;
+                len -= thislen;
+            }
+        }
+
+        if (len) { /* First block to allocate, or need another block. */
+            int numblocks;
+
+            block = zmalloc(sizeof(*block));
+            block->free = AOF_RW_BUF_BLOCK_SIZE;
+            block->used = 0;
+            listAddNodeTail(server.aof_rewrite_buf_blocks,block);
+
+            /* Log every time we cross more 10 or 100 blocks, respectively
+             * as a notice or warning. */
+            numblocks = listLength(server.aof_rewrite_buf_blocks);
+            if (((numblocks+1) % 10) == 0) {
+                int level = ((numblocks+1) % 100) == 0 ? REDIS_WARNING :
+                                                         REDIS_NOTICE;
+                redisLog(level,"Background AOF buffer size: %lu MB",
+                    aofRewriteBufferSize()/(1024*1024));
+            }
+        }
+    }
+}
+
+/* Write the buffer (possibly composed of multiple blocks) into the specified
+ * fd. If no short write or any other error happens -1 is returned,
+ * otherwise the number of bytes written is returned. */
+ssize_t aofRewriteBufferWrite(int fd) {
+    listNode *ln;
+    listIter li;
+    ssize_t count = 0;
+
+    listRewind(server.aof_rewrite_buf_blocks,&li);
+    while((ln = listNext(&li))) {
+        aofrwblock *block = listNodeValue(ln);
+        ssize_t nwritten;
+
+        if (block->used) {
+            nwritten = write(fd,block->buf,block->used);
+            if (nwritten != block->used) {
+                if (nwritten == 0) errno = EIO;
+                return -1;
+            }
+            count += nwritten;
+        }
+    }
+    return count;
+}
+
+/* ----------------------------------------------------------------------------
  * AOF file implementation
  * ------------------------------------------------------------------------- */
 
@@ -42,8 +151,7 @@ void stopAppendOnly(void) {
         if (kill(server.aof_child_pid,SIGKILL) != -1)
             wait3(&statloc,0,NULL);
         /* reset the buffer accumulating changes while the child saves */
-        sdsfree(server.aof_rewrite_buf);
-        server.aof_rewrite_buf = sdsempty();
+        aofRewriteBufferReset();
         aofRemoveTempFile(server.aof_child_pid);
         server.aof_child_pid = -1;
     }
@@ -281,7 +389,7 @@ void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int a
      * in a buffer, so that when the child process will do its work we
      * can append the differences to the new append only file. */
     if (server.aof_child_pid != -1)
-        server.aof_rewrite_buf = sdscatlen(server.aof_rewrite_buf,buf,sdslen(buf));
+        aofRewriteBufferAppend((unsigned char*)buf,sdslen(buf));
 
     sdsfree(buf);
 }
@@ -885,7 +993,6 @@ void aofUpdateCurrentSize(void) {
 void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
     if (!bysignal && exitcode == 0) {
         int newfd, oldfd;
-        int nwritten;
         char tmpfile[256];
         long long now = ustime();
 
@@ -903,21 +1010,15 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
             goto cleanup;
         }
 
-        nwritten = write(newfd,server.aof_rewrite_buf,sdslen(server.aof_rewrite_buf));
-        if (nwritten != (signed)sdslen(server.aof_rewrite_buf)) {
-            if (nwritten == -1) {
-                redisLog(REDIS_WARNING,
-                    "Error trying to flush the parent diff to the rewritten AOF: %s", strerror(errno));
-            } else {
-                redisLog(REDIS_WARNING,
-                    "Short write trying to flush the parent diff to the rewritten AOF: %s", strerror(errno));
-            }
+        if (aofRewriteBufferWrite(newfd) == -1) {
+            redisLog(REDIS_WARNING,
+                "Error trying to flush the parent diff to the rewritten AOF: %s", strerror(errno));
             close(newfd);
             goto cleanup;
         }
 
         redisLog(REDIS_NOTICE,
-            "Parent diff successfully flushed to the rewritten AOF (%lu bytes)", nwritten);
+            "Parent diff successfully flushed to the rewritten AOF (%lu bytes)", aofRewriteBufferSize());
 
         /* The only remaining thing to do is to rename the temporary file to
          * the configured file and switch the file descriptor used to do AOF
@@ -1009,8 +1110,7 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
     }
 
 cleanup:
-    sdsfree(server.aof_rewrite_buf);
-    server.aof_rewrite_buf = sdsempty();
+    aofRewriteBufferReset();
     aofRemoveTempFile(server.aof_child_pid);
     server.aof_child_pid = -1;
     /* Schedule a new rewrite if we are waiting for it to switch the AOF ON. */