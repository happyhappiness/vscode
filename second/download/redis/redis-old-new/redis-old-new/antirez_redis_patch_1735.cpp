@@ -437,7 +437,8 @@ int rdbSave(char *filename) {
     snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
     fp = fopen(tmpfile,"w");
     if (!fp) {
-        redisLog(REDIS_WARNING, "Failed saving the DB: %s", strerror(errno));
+        redisLog(REDIS_WARNING, "Failed opening .rdb for saving: %s",
+            strerror(errno));
         return REDIS_ERR;
     }
     if (fwrite("REDIS0001",9,1,fp) == 0) goto werr;
@@ -973,7 +974,7 @@ void backgroundSaveDoneHandler(int exitcode, int bysignal) {
 }
 
 void saveCommand(redisClient *c) {
-    if (server.bgsavechildpid != -1 || server.bgsavethread != (pthread-t)-1) {
+    if (server.bgsavechildpid != -1 || server.bgsavethread != (pthread_t)-1) {
         addReplyError(c,"Background save already in progress");
         return;
     }
@@ -985,7 +986,7 @@ void saveCommand(redisClient *c) {
 }
 
 void bgsaveCommand(redisClient *c) {
-    if (server.bgsavechildpid != -1 || server.bgsavethread != (pthread-t)-1) {
+    if (server.bgsavechildpid != -1 || server.bgsavethread != (pthread_t)-1) {
         addReplyError(c,"Background save already in progress");
         return;
     }