@@ -873,14 +873,13 @@ void initServerConfig() {
     server.syslog_ident = zstrdup("redis");
     server.syslog_facility = LOG_LOCAL0;
     server.daemonize = 0;
-    server.appendonly = 0;
+    server.aof_state = REDIS_AOF_OFF;
     server.appendfsync = APPENDFSYNC_EVERYSEC;
     server.no_appendfsync_on_rewrite = 0;
     server.auto_aofrewrite_perc = REDIS_AUTO_AOFREWRITE_PERC;
     server.auto_aofrewrite_min_size = REDIS_AUTO_AOFREWRITE_MIN_SIZE;
     server.auto_aofrewrite_base_size = 0;
     server.aofrewrite_scheduled = 0;
-    server.aof_wait_rewrite = 0;
     server.lastfsync = time(NULL);
     server.appendfd = -1;
     server.appendseldb = -1; /* Make sure the first time will not match */
@@ -920,7 +919,6 @@ void initServerConfig() {
     appendServerSaveParams(300,100);  /* save after 5 minutes and 100 changes */
     appendServerSaveParams(60,10000); /* save after 1 minute and 10000 changes */
     /* Replication related */
-    server.isslave = 0;
     server.masterauth = NULL;
     server.masterhost = NULL;
     server.masterport = 6379;
@@ -1069,8 +1067,9 @@ void initServer() {
     if (server.sofd > 0 && aeCreateFileEvent(server.el,server.sofd,AE_READABLE,
         acceptUnixHandler,NULL) == AE_ERR) oom("creating file event");
 
-    if (server.appendonly) {
-        server.appendfd = open(server.appendfilename,O_WRONLY|O_APPEND|O_CREAT,0644);
+    if (server.aof_state == REDIS_AOF_ON) {
+        server.appendfd = open(server.appendfilename,
+                               O_WRONLY|O_APPEND|O_CREAT,0644);
         if (server.appendfd == -1) {
             redisLog(REDIS_WARNING, "Can't open the append-only file: %s",
                 strerror(errno));
@@ -1156,7 +1155,7 @@ void call(redisClient *c) {
     slowlogPushEntryIfNeeded(c->argv,c->argc,duration);
     c->cmd->calls++;
 
-    if (server.appendonly && dirty > 0)
+    if (server.aof_state != REDIS_AOF_OFF && dirty > 0)
         feedAppendOnlyFile(c->cmd,c->db->id,c->argv,c->argc);
     if ((dirty > 0 || c->cmd->flags & REDIS_CMD_FORCE_REPLICATION) &&
         listLength(server.slaves))
@@ -1311,7 +1310,7 @@ int prepareForShutdown(int flags) {
         kill(server.bgsavechildpid,SIGKILL);
         rdbRemoveTempFile(server.bgsavechildpid);
     }
-    if (server.appendonly) {
+    if (server.aof_state != REDIS_AOF_OFF) {
         /* Kill the AOF saving child as the AOF we already have may be longer
          * but contains the full dataset anyway. */
         if (server.bgrewritechildpid != -1) {
@@ -1498,13 +1497,13 @@ sds genRedisInfoString(char *section) {
             "last_save_time:%ld\r\n"
             "bgrewriteaof_in_progress:%d\r\n",
             server.loading,
-            server.appendonly,
+            server.aof_state != REDIS_AOF_OFF,
             server.dirty,
             server.bgsavechildpid != -1,
             server.lastsave,
             server.bgrewritechildpid != -1);
 
-        if (server.appendonly) {
+        if (server.aof_state != REDIS_AOF_OFF) {
             info = sdscatprintf(info,
                 "aof_current_size:%lld\r\n"
                 "aof_base_size:%lld\r\n"
@@ -2099,7 +2098,7 @@ int main(int argc, char **argv) {
     linuxOvercommitMemoryWarning();
 #endif
     start = ustime();
-    if (server.appendonly) {
+    if (server.aof_state == REDIS_AOF_ON) {
         if (loadAppendOnlyFile(server.appendfilename) == REDIS_OK)
             redisLog(REDIS_NOTICE,"DB loaded from append only file: %.3f seconds",(float)(ustime()-start)/1000000);
     } else {