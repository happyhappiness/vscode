@@ -315,7 +315,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
     /* If repl_transfer_left == -1 we still have to read the bulk length
      * from the master reply. */
     if (server.repl_transfer_left == -1) {
-        if (syncReadLine(fd,buf,1024,3600) == -1) {
+        if (syncReadLine(fd,buf,1024,server.repl_syncio_timeout) == -1) {
             redisLog(REDIS_WARNING,
                 "I/O error reading bulk count from MASTER: %s",
                 strerror(errno));
@@ -414,13 +414,13 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
         size_t authlen;
 
         authlen = snprintf(authcmd,sizeof(authcmd),"AUTH %s\r\n",server.masterauth);
-        if (syncWrite(fd,authcmd,authlen,5) == -1) {
+        if (syncWrite(fd,authcmd,authlen,server.repl_syncio_timeout) == -1) {
             redisLog(REDIS_WARNING,"Unable to AUTH to MASTER: %s",
                 strerror(errno));
             goto error;
         }
         /* Read the AUTH result.  */
-        if (syncReadLine(fd,buf,1024,3600) == -1) {
+        if (syncReadLine(fd,buf,1024,server.repl_syncio_timeout) == -1) {
             redisLog(REDIS_WARNING,"I/O error reading auth result from MASTER: %s",
                 strerror(errno));
             goto error;
@@ -432,7 +432,7 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
 
     /* Issue the SYNC command */
-    if (syncWrite(fd,"SYNC \r\n",7,5) == -1) {
+    if (syncWrite(fd,"SYNC \r\n",7,server.repl_syncio_timeout) == -1) {
         redisLog(REDIS_WARNING,"I/O error writing to MASTER: %s",
             strerror(errno));
         goto error;