@@ -261,6 +261,9 @@ struct redisServer {
     int maxidletime;
     int dbnum;
     int daemonize;
+    int appendonly;
+    int appendfd;
+    int appendseldb;
     char *pidfile;
     int bgsaveinprogress;
     pid_t bgsavechildpid;
@@ -269,6 +272,7 @@ struct redisServer {
     char *logfile;
     char *bindaddr;
     char *dbfilename;
+    char *appendfilename;
     char *requirepass;
     int shareobjects;
     /* Replication related */
@@ -364,6 +368,7 @@ static void incrRefCount(robj *o);
 static int rdbSaveBackground(char *filename);
 static robj *createStringObject(char *ptr, size_t len);
 static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int dictid, robj **argv, int argc);
+static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int argc);
 static int syncWithMaster(void);
 static robj *tryObjectSharing(robj *o);
 static int tryObjectEncoding(robj *o);
@@ -1023,8 +1028,12 @@ static void initServerConfig() {
     server.bindaddr = NULL;
     server.glueoutputbuf = 1;
     server.daemonize = 0;
+    server.appendonly = 0;
+    server.appendfd = -1;
+    server.appendseldb = -1; /* Make sure the first time will not match */
     server.pidfile = "/var/run/redis.pid";
     server.dbfilename = "dump.rdb";
+    server.appendfilename = "appendonly.log";
     server.requirepass = NULL;
     server.shareobjects = 0;
     server.sharingpoolsize = 1024;
@@ -1084,6 +1093,15 @@ static void initServer() {
     server.stat_numconnections = 0;
     server.stat_starttime = time(NULL);
     aeCreateTimeEvent(server.el, 1000, serverCron, NULL, NULL);
+
+    if (server.appendonly) {
+        server.appendfd = open(server.appendfilename,O_WRONLY|O_APPEND|O_CREAT);
+        if (server.appendfd == -1) {
+            redisLog(REDIS_WARNING, "Can't open the append-only file: %s",
+                strerror(errno));
+            exit(1);
+        }
+    }
 }
 
 /* Empty the whole database */
@@ -1223,6 +1241,10 @@ static void loadServerConfig(char *filename) {
             if ((server.daemonize = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
+        } else if (!strcasecmp(argv[0],"appendonly") && argc == 2) {
+            if ((server.appendonly = yesnotoi(argv[1])) == -1) {
+                err = "argument must be 'yes' or 'no'"; goto loaderr;
+            }
         } else if (!strcasecmp(argv[0],"requirepass") && argc == 2) {
           server.requirepass = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"pidfile") && argc == 2) {
@@ -1538,6 +1560,8 @@ static int processCommand(redisClient *c) {
     /* Exec the command */
     dirty = server.dirty;
     cmd->proc(c);
+    if (server.appendonly != 0)
+        feedAppendOnlyFile(cmd,c->db->id,c->argv,c->argc);
     if (server.dirty-dirty != 0 && listLength(server.slaves))
         replicationFeedSlaves(server.slaves,cmd,c->db->id,c->argv,c->argc);
     if (listLength(server.monitors))
@@ -1622,6 +1646,54 @@ static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int di
     if (outv != static_outv) zfree(outv);
 }
 
+/* TODO: translate EXPIREs into EXPIRETOs */
+static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int argc) {
+    sds buf = sdsempty();
+    int j;
+    ssize_t nwritten;
+
+    /* The DB this command was targetting is not the same as the last command
+     * we appendend. To issue a SELECT command is needed. */
+    if (dictid != server.appendseldb) {
+        char seldb[64];
+
+        snprintf(seldb,sizeof(seldb),"%d",dictid);
+        buf = sdscatprintf(buf,"*2\r\n$6\r\nSELECT\r\n$%d\r\n%s\r\n",
+            strlen(seldb),seldb);
+    }
+    /* Append the actual command */
+    buf = sdscatprintf(buf,"*%d\r\n",argc);
+    for (j = 0; j < argc; j++) {
+        robj *o = argv[j];
+
+        if (o->encoding != REDIS_ENCODING_RAW)
+            o = getDecodedObject(o);
+        buf = sdscatprintf(buf,"$%d\r\n",sdslen(o->ptr));
+        buf = sdscatlen(buf,o->ptr,sdslen(o->ptr));
+        buf = sdscatlen(buf,"\r\n",2);
+        if (o != argv[j])
+            decrRefCount(o);
+    }
+    /* We want to perform a single write. This should be guaranteed atomic
+     * at least if the filesystem we are writing is a real physical one.
+     * While this will save us against the server being killed I don't think
+     * there is much to do about the whole server stopping for power problems
+     * or alike */
+     nwritten = write(server.appendfd,buf,sdslen(buf));
+     if (nwritten != (unsigned)sdslen(buf)) {
+        /* Ooops, we are in troubles. The best thing to do for now is
+         * to simply exit instead to give the illusion that everything is
+         * working as expected. */
+         if (nwritten == -1) {
+            redisLog(REDIS_WARNING,"Aborting on error writing to the append-only file: %s",strerror(errno));
+         } else {
+            redisLog(REDIS_WARNING,"Aborting on short write while writing to the append-only file: %s",strerror(errno));
+         }
+         abort();
+     }
+     fsync(server.appendfd); /* Let's try to get this data on the disk */
+}
+
 static void processInputBuffer(redisClient *c) {
 again:
     if (c->bulklen == -1) {