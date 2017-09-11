@@ -940,14 +940,16 @@ int rewriteHashObject(rio *r, robj *key, robj *o) {
 /* This function is called by the child rewriting the AOF file to read
  * the difference accumulated from the parent into a buffer, that is
  * concatenated at the end of the rewrite. */
-void aofReadDiffFromParent(void) {
-    char buf[1024*16];
-    ssize_t nread;
+ssize_t aofReadDiffFromParent(void) {
+    char buf[65536]; /* Default pipe buffer size on most Linux sytems. */
+    ssize_t nread, total = 0;
 
     while ((nread =
             read(server.aof_pipe_read_data_from_parent,buf,sizeof(buf))) > 0) {
         server.aof_child_diff = sdscatlen(server.aof_child_diff,buf,nread);
+        total += nread;
     }
+    return total;
 }
 
 /* Write a sequence of commands able to fully rebuild the dataset into
@@ -1038,14 +1040,35 @@ int rewriteAppendOnlyFile(char *filename) {
                 if (rioWriteBulkLongLong(&aof,expiretime) == 0) goto werr;
             }
             /* Read some diff from the parent process from time to time. */
-            if (aof.processed_bytes > processed+REDIS_AOF_AUTOSYNC_BYTES) {
+            if (aof.processed_bytes > processed+1024*10) {
                 processed = aof.processed_bytes;
                 aofReadDiffFromParent();
             }
         }
         dictReleaseIterator(di);
     }
 
+    /* Do an initial slow fsync here while the parent is still sending
+     * data, in order to make the next final fsync faster. */
+    if (fflush(fp) == EOF) goto werr;
+    if (fsync(fileno(fp)) == -1) goto werr;
+
+    /* Read again a few times to get more data from the parent.
+     * We can't read forever (the server may receive data from clients
+     * fater than it is able to send data to the child), so we try to read
+     * some more data in a loop and wait a bit if data is not available, but
+     * don't wait more than 100 ms total. */
+    int nodata = 0;
+    for (j = 0; j < 100; j++) {
+        ssize_t nread_from_parent = aofReadDiffFromParent();
+        printf("%lld\n", (long long) nread_from_parent);
+        if (nread_from_parent == 0) {
+            nodata++;
+            if (nodata == 10) break;
+            usleep(10000);
+        }
+    }
+
     /* Ask the master to stop sending diffs. */
     if (write(server.aof_pipe_write_ack_to_parent,"!",1) != 1) goto werr;
     if (anetNonBlock(NULL,server.aof_pipe_read_ack_from_parent) != ANET_OK)