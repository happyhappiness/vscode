@@ -7157,7 +7157,7 @@ static int syncWithMaster(void) {
     char buf[1024], tmpfile[256], authcmd[1024];
     long dumpsize;
     int fd = anetTcpConnect(NULL,server.masterhost,server.masterport);
-    int dfd;
+    int dfd, maxtries = 5;
 
     if (fd == -1) {
         redisLog(REDIS_WARNING,"Unable to connect to MASTER: %s",
@@ -7210,8 +7210,12 @@ static int syncWithMaster(void) {
     dumpsize = strtol(buf+1,NULL,10);
     redisLog(REDIS_NOTICE,"Receiving %ld bytes data dump from MASTER",dumpsize);
     /* Read the bulk write data on a temp file */
-    snprintf(tmpfile,256,"temp-%d.%ld.rdb",(int)time(NULL),(long int)random());
-    dfd = open(tmpfile,O_CREAT|O_WRONLY,0644);
+    while(maxtries--) {
+        snprintf(tmpfile,256,
+            "temp-%d.%ld.rdb",(int)time(NULL),(long int)getpid());
+        dfd = open(tmpfile,O_CREAT|O_WRONLY|O_EXCL,0644);
+        if (dfd != -1) break;
+    }
     if (dfd == -1) {
         close(fd);
         redisLog(REDIS_WARNING,"Opening the temp file needed for MASTER <-> SLAVE synchronization: %s",strerror(errno));