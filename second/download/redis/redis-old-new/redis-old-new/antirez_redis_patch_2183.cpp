@@ -6787,7 +6787,7 @@ static void updateSlavesWaitingBgsave(int bgsaveerr) {
 
 static int syncWithMaster(void) {
     char buf[1024], tmpfile[256], authcmd[1024];
-    int dumpsize;
+    long dumpsize;
     int fd = anetTcpConnect(NULL,server.masterhost,server.masterport);
     int dfd;
 
@@ -6839,8 +6839,8 @@ static int syncWithMaster(void) {
         redisLog(REDIS_WARNING,"Bad protocol from MASTER, the first byte is not '$', are you sure the host and port are right?");
         return REDIS_ERR;
     }
-    dumpsize = atoi(buf+1);
-    redisLog(REDIS_NOTICE,"Receiving %d bytes data dump from MASTER",dumpsize);
+    dumpsize = strtol(buf+1,NULL,10);
+    redisLog(REDIS_NOTICE,"Receiving %ld bytes data dump from MASTER",dumpsize);
     /* Read the bulk write data on a temp file */
     snprintf(tmpfile,256,"temp-%d.%ld.rdb",(int)time(NULL),(long int)random());
     dfd = open(tmpfile,O_CREAT|O_WRONLY,0644);