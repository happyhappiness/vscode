@@ -628,23 +628,28 @@ void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
     char buf[REDIS_IOBUF_LEN];
     ssize_t nwritten, buflen;
 
-    if (slave->repldboff == 0) {
-        /* Write the bulk write count before to transfer the DB. In theory here
-         * we don't know how much room there is in the output buffer of the
-         * socket, but in practice SO_SNDLOWAT (the minimum count for output
-         * operations) will never be smaller than the few bytes we need. */
-        sds bulkcount;
-
-        bulkcount = sdscatprintf(sdsempty(),"$%lld\r\n",(unsigned long long)
-            slave->repldbsize);
-        if (write(fd,bulkcount,sdslen(bulkcount)) != (signed)sdslen(bulkcount))
-        {
-            sdsfree(bulkcount);
+    /* Before sending the RDB file, we send the preamble as configured by the
+     * replication process. Currently the preamble is just the bulk count of
+     * the file in the form "$<length>\r\n". */
+    if (slave->replpreamble) {
+        nwritten = write(fd,slave->replpreamble,sdslen(slave->replpreamble));
+        if (nwritten == -1) {
+            redisLog(REDIS_VERBOSE,"Write error sending RDB preamble to slave: %s",
+                strerror(errno));
             freeClient(slave);
             return;
         }
-        sdsfree(bulkcount);
+        sdsrange(slave->replpreamble,nwritten,-1);
+        if (sdslen(slave->replpreamble) == 0) {
+            sdsfree(slave->replpreamble);
+            slave->replpreamble = NULL;
+            /* fall through sending data. */
+        } else {
+            return;
+        }
     }
+
+    /* If the preamble was already transfered, send the RDB bulk data. */
     lseek(slave->repldbfd,slave->repldboff,SEEK_SET);
     buflen = read(slave->repldbfd,buf,REDIS_IOBUF_LEN);
     if (buflen <= 0) {
@@ -711,6 +716,9 @@ void updateSlavesWaitingBgsave(int bgsaveerr) {
             slave->repldboff = 0;
             slave->repldbsize = buf.st_size;
             slave->replstate = REDIS_REPL_SEND_BULK;
+            slave->replpreamble = sdscatprintf(sdsempty(),"$%lld\r\n",
+                (unsigned long long) slave->repldbsize);
+
             aeDeleteFileEvent(server.el,slave->fd,AE_WRITABLE);
             if (aeCreateFileEvent(server.el, slave->fd, AE_WRITABLE, sendBulkToSlave, slave) == AE_ERR) {
                 freeClient(slave);