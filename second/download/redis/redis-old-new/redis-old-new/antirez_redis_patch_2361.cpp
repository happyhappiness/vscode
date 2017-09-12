@@ -171,6 +171,7 @@ struct redisServer {
     int maxidletime;
     int dbnum;
     int daemonize;
+    char *pidfile;
     int bgsaveinprogress;
     struct saveparam *saveparams;
     int saveparamslen;
@@ -715,6 +716,7 @@ static void initServerConfig() {
     server.bindaddr = NULL;
     server.glueoutputbuf = 1;
     server.daemonize = 0;
+    server.pidfile = "/var/run/redis.pid";
     server.dbfilename = "dump.rdb";
     ResetServerSaveParams();
 
@@ -878,6 +880,8 @@ static void loadServerConfig(char *filename) {
             else {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
+        } else if (!strcmp(argv[0],"pidfile") && argc == 2) {
+          server.pidfile = zstrdup(argv[1]);
         } else {
             err = "Bad directive or wrong number of arguments"; goto loaderr;
         }
@@ -1899,6 +1903,9 @@ static void bgsaveCommand(redisClient *c) {
 static void shutdownCommand(redisClient *c) {
     redisLog(REDIS_WARNING,"User requested shutdown, saving DB...");
     if (saveDb(server.dbfilename) == REDIS_OK) {
+        if (server.daemonize) {
+          unlink(server.pidfile);
+        }
         redisLog(REDIS_WARNING,"Server exit now, bye bye...");
         exit(1);
     } else {
@@ -3033,7 +3040,7 @@ static void daemonize(void) {
         if (fd > STDERR_FILENO) close(fd);
     }
     /* Try to write the pid file */
-    fp = fopen("/var/run/redis.pid","w");
+    fp = fopen(server.pidfile,"w");
     if (fp) {
         fprintf(fp,"%d\n",getpid());
         fclose(fp);