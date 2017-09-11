@@ -204,7 +204,7 @@ void aof_background_fsync(int fd) {
 /* Called when the user switches from "appendonly yes" to "appendonly no"
  * at runtime using the CONFIG command. */
 void stopAppendOnly(void) {
-    redisAssert(server.aof_state != REDIS_AOF_OFF);
+    serverAssert(server.aof_state != REDIS_AOF_OFF);
     flushAppendOnlyFile(1);
     aof_fsync(server.aof_fd);
     close(server.aof_fd);
@@ -235,7 +235,7 @@ void stopAppendOnly(void) {
 int startAppendOnly(void) {
     server.aof_last_fsync = server.unixtime;
     server.aof_fd = open(server.aof_filename,O_WRONLY|O_APPEND|O_CREAT,0644);
-    redisAssert(server.aof_state == REDIS_AOF_OFF);
+    serverAssert(server.aof_state == REDIS_AOF_OFF);
     if (server.aof_fd == -1) {
         serverLog(REDIS_WARNING,"Redis needs to enable the AOF but can't open the append only file: %s",strerror(errno));
         return REDIS_ERR;
@@ -685,9 +685,9 @@ int loadAppendOnlyFile(char *filename) {
         cmd->proc(fakeClient);
 
         /* The fake client should not have a reply */
-        redisAssert(fakeClient->bufpos == 0 && listLength(fakeClient->reply) == 0);
+        serverAssert(fakeClient->bufpos == 0 && listLength(fakeClient->reply) == 0);
         /* The fake client should never get blocked */
-        redisAssert((fakeClient->flags & REDIS_BLOCKED) == 0);
+        serverAssert((fakeClient->flags & REDIS_BLOCKED) == 0);
 
         /* Clean up. Command code may have changed argv/argc so we use the
          * argv/argc of the client instead of the local variables. */
@@ -860,12 +860,12 @@ int rewriteSortedSetObject(rio *r, robj *key, robj *o) {
         double score;
 
         eptr = ziplistIndex(zl,0);
-        redisAssert(eptr != NULL);
+        serverAssert(eptr != NULL);
         sptr = ziplistNext(zl,eptr);
-        redisAssert(sptr != NULL);
+        serverAssert(sptr != NULL);
 
         while (eptr != NULL) {
-            redisAssert(ziplistGet(eptr,&vstr,&vlen,&vll));
+            serverAssert(ziplistGet(eptr,&vstr,&vlen,&vll));
             score = zzlGetScore(sptr);
 
             if (count == 0) {