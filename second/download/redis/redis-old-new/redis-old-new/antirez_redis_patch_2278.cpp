@@ -281,6 +281,7 @@ struct redisServer {
     int shareobjects;
     /* Replication related */
     int isslave;
+    char *masterauth;
     char *masterhost;
     int masterport;
     redisClient *master;    /* client that is master for this slave */
@@ -1052,6 +1053,7 @@ static void initServerConfig() {
     appendServerSaveParams(60,10000); /* save after 1 minute and 10000 changes */
     /* Replication related */
     server.isslave = 0;
+    server.masterauth = NULL;
     server.masterhost = NULL;
     server.masterport = 6379;
     server.master = NULL;
@@ -1230,6 +1232,8 @@ static void loadServerConfig(char *filename) {
             server.masterhost = sdsnew(argv[1]);
             server.masterport = atoi(argv[2]);
             server.replstate = REDIS_REPL_CONNECT;
+        } else if (!strcasecmp(argv[0],"masterauth") && argc == 2) {
+        	server.masterauth = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"glueoutputbuf") && argc == 2) {
             if ((server.glueoutputbuf = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
@@ -5128,7 +5132,7 @@ static void updateSlavesWaitingBgsave(int bgsaveerr) {
 }
 
 static int syncWithMaster(void) {
-    char buf[1024], tmpfile[256];
+    char buf[1024], tmpfile[256], authcmd[1024];
     int dumpsize;
     int fd = anetTcpConnect(NULL,server.masterhost,server.masterport);
     int dfd;
@@ -5138,6 +5142,30 @@ static int syncWithMaster(void) {
             strerror(errno));
         return REDIS_ERR;
     }
+
+    /* AUTH with the master if required. */
+    if(server.masterauth) {
+    	snprintf(authcmd, 1024, "AUTH %s\r\n", server.masterauth);
+    	if (syncWrite(fd, authcmd, strlen(server.masterauth)+7, 5) == -1) {
+            close(fd);
+            redisLog(REDIS_WARNING,"Unable to AUTH to MASTER: %s",
+                strerror(errno));
+            return REDIS_ERR;
+    	}
+        /* Read the AUTH result.  */
+        if (syncReadLine(fd,buf,1024,3600) == -1) {
+            close(fd);
+            redisLog(REDIS_WARNING,"I/O error reading auth result from MASTER: %s",
+                strerror(errno));
+            return REDIS_ERR;
+        }
+        if (buf[0] != '+') {
+            close(fd);
+            redisLog(REDIS_WARNING,"Cannot AUTH to MASTER, is the masterauth password correct?");
+            return REDIS_ERR;
+        }
+    }
+
     /* Issue the SYNC command */
     if (syncWrite(fd,"SYNC \r\n",7,5) == -1) {
         close(fd);