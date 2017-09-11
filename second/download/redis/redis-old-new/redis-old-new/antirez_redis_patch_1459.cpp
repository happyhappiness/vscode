@@ -106,7 +106,7 @@ void syncCommand(redisClient *c) {
     redisLog(REDIS_NOTICE,"Slave ask for synchronization");
     /* Here we need to check if there is a background saving operation
      * in progress, or if it is required to start one */
-    if (server.bgsavechildpid != -1) {
+    if (server.rdb_child_pid != -1) {
         /* Ok a background save is in progress. Let's check if it is a good
          * one for replication, i.e. if there is another slave that is
          * registering differences since the server forked to save */
@@ -135,7 +135,7 @@ void syncCommand(redisClient *c) {
     } else {
         /* Ok we don't have a BGSAVE in progress, let's start one */
         redisLog(REDIS_NOTICE,"Starting BGSAVE for SYNC");
-        if (rdbSaveBackground(server.dbfilename) != REDIS_OK) {
+        if (rdbSaveBackground(server.rdb_filename) != REDIS_OK) {
             redisLog(REDIS_NOTICE,"Replication failed, can't BGSAVE");
             addReplyError(c,"Unable to perform background save");
             return;
@@ -229,7 +229,7 @@ void updateSlavesWaitingBgsave(int bgsaveerr) {
                 redisLog(REDIS_WARNING,"SYNC failed. BGSAVE child returned an error");
                 continue;
             }
-            if ((slave->repldbfd = open(server.dbfilename,O_RDONLY)) == -1 ||
+            if ((slave->repldbfd = open(server.rdb_filename,O_RDONLY)) == -1 ||
                 redis_fstat(slave->repldbfd,&buf) == -1) {
                 freeClient(slave);
                 redisLog(REDIS_WARNING,"SYNC failed. Can't open/stat DB after BGSAVE: %s", strerror(errno));
@@ -246,7 +246,7 @@ void updateSlavesWaitingBgsave(int bgsaveerr) {
         }
     }
     if (startbgsave) {
-        if (rdbSaveBackground(server.dbfilename) != REDIS_OK) {
+        if (rdbSaveBackground(server.rdb_filename) != REDIS_OK) {
             listIter li;
 
             listRewind(server.slaves,&li);
@@ -333,7 +333,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
     server.repl_transfer_left -= nread;
     /* Check if the transfer is now complete */
     if (server.repl_transfer_left == 0) {
-        if (rename(server.repl_transfer_tmpfile,server.dbfilename) == -1) {
+        if (rename(server.repl_transfer_tmpfile,server.rdb_filename) == -1) {
             redisLog(REDIS_WARNING,"Failed trying to rename the temp DB into dump.rdb in MASTER <-> SLAVE synchronization: %s", strerror(errno));
             replicationAbortSyncTransfer();
             return;
@@ -345,7 +345,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
          * rdbLoad() will call the event loop to process events from time to
          * time for non blocking loading. */
         aeDeleteFileEvent(server.el,server.repl_transfer_s,AE_READABLE);
-        if (rdbLoad(server.dbfilename) != REDIS_OK) {
+        if (rdbLoad(server.rdb_filename) != REDIS_OK) {
             redisLog(REDIS_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
             replicationAbortSyncTransfer();
             return;