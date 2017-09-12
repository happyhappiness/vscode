@@ -327,10 +327,11 @@ static int deleteIfVolatile(redisDb *db, robj *key);
 static int deleteKey(redisDb *db, robj *key);
 static time_t getExpire(redisDb *db, robj *key);
 static int setExpire(redisDb *db, robj *key, time_t when);
-static void updateSalvesWaitingBgsave(int bgsaveerr);
+static void updateSlavesWaitingBgsave(int bgsaveerr);
 static void freeMemoryIfNeeded(void);
 static int processCommand(redisClient *c);
 static void setupSigSegvAction(void);
+static void rdbRemoveTempFile(pid_t childpid);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -778,10 +779,11 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
             } else {
                 redisLog(REDIS_WARNING,
                     "Background saving terminated by signal");
+                rdbRemoveTempFile(server.bgsavechildpid);
             }
             server.bgsaveinprogress = 0;
             server.bgsavechildpid = -1;
-            updateSalvesWaitingBgsave(exitcode == 0 ? REDIS_OK : REDIS_ERR);
+            updateSlavesWaitingBgsave(exitcode == 0 ? REDIS_OK : REDIS_ERR);
         }
     } else {
         /* If there is not a background saving in progress check if
@@ -1900,7 +1902,7 @@ static int rdbSave(char *filename) {
     int j;
     time_t now = time(NULL);
 
-    snprintf(tmpfile,256,"temp-%d.%ld.rdb",(int)time(NULL),(long int)random());
+    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
     fp = fopen(tmpfile,"w");
     if (!fp) {
         redisLog(REDIS_WARNING, "Failed saving the DB: %s", strerror(errno));
@@ -2027,6 +2029,13 @@ static int rdbSaveBackground(char *filename) {
     return REDIS_OK; /* unreached */
 }
 
+static void rdbRemoveTempFile(pid_t childpid) {
+    char tmpfile[256];
+
+    snprintf(tmpfile,256,"temp-%d.rdb", (int) childpid);
+    unlink(tmpfile);
+}
+
 static int rdbLoadType(FILE *fp) {
     unsigned char type;
     if (fread(&type,1,1,fp) == 0) return -1;
@@ -2544,19 +2553,26 @@ static void bgsaveCommand(redisClient *c) {
 
 static void shutdownCommand(redisClient *c) {
     redisLog(REDIS_WARNING,"User requested shutdown, saving DB...");
+    /* Kill the saving child if there is a background saving in progress.
+       We want to avoid race conditions, for instance our saving child may
+       overwrite the synchronous saving did by SHUTDOWN. */
     if (server.bgsaveinprogress) {
         redisLog(REDIS_WARNING,"There is a live saving child. Killing it!");
-        signal(SIGCHLD, SIG_IGN);
         kill(server.bgsavechildpid,SIGKILL);
+        rdbRemoveTempFile(server.bgsavechildpid);
     }
+    /* SYNC SAVE */
     if (rdbSave(server.dbfilename) == REDIS_OK) {
         if (server.daemonize)
             unlink(server.pidfile);
         redisLog(REDIS_WARNING,"%zu bytes used at exit",zmalloc_used_memory());
         redisLog(REDIS_WARNING,"Server exit now, bye bye...");
         exit(1);
     } else {
-        signal(SIGCHLD, SIG_DFL);
+        /* Ooops.. error saving! The best we can do is to continue operating.
+         * Note that if there was a background saving process, in the next
+         * cron() Redis will be notified that the background saving aborted,
+         * handling special stuff like slaves pending for synchronization... */
         redisLog(REDIS_WARNING,"Error trying to save the DB, can't exit"); 
         addReplySds(c,sdsnew("-ERR can't quit, problems saving the DB\r\n"));
     }
@@ -3939,7 +3955,13 @@ static void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
 }
 
-static void updateSalvesWaitingBgsave(int bgsaveerr) {
+/* This function is called at the end of every backgrond saving.
+ * The argument bgsaveerr is REDIS_OK if the background saving succeeded
+ * otherwise REDIS_ERR is passed to the function.
+ *
+ * The goal of this function is to handle slaves waiting for a successful
+ * background saving in order to perform non-blocking synchronization. */
+static void updateSlavesWaitingBgsave(int bgsaveerr) {
     listNode *ln;
     int startbgsave = 0;
 
@@ -4183,7 +4205,7 @@ static struct redisFunctionSym symsTable[] = {
 {"deleteKey", (unsigned long)deleteKey},
 {"getExpire", (unsigned long)getExpire},
 {"setExpire", (unsigned long)setExpire},
-{"updateSalvesWaitingBgsave", (unsigned long)updateSalvesWaitingBgsave},
+{"updateSlavesWaitingBgsave", (unsigned long)updateSlavesWaitingBgsave},
 {"freeMemoryIfNeeded", (unsigned long)freeMemoryIfNeeded},
 {"authCommand", (unsigned long)authCommand},
 {"pingCommand", (unsigned long)pingCommand},
@@ -4246,6 +4268,7 @@ static struct redisFunctionSym symsTable[] = {
 {"processCommand", (unsigned long)processCommand},
 {"setupSigSegvAction", (unsigned long)setupSigSegvAction},
 {"readQueryFromClient", (unsigned long)readQueryFromClient},
+{"rdbRemoveTempFile", (unsigned long)rdbRemoveTempFile},
 {NULL,0}
 };
 