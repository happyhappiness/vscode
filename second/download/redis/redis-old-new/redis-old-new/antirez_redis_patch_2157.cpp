@@ -696,6 +696,7 @@ static void hkeysCommand(redisClient *c);
 static void hvalsCommand(redisClient *c);
 static void hgetallCommand(redisClient *c);
 static void hexistsCommand(redisClient *c);
+static void configCommand(redisClient *c);
 
 /*================================= Globals ================================= */
 
@@ -797,6 +798,7 @@ static struct redisCommand cmdTable[] = {
     {"ttl",ttlCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
     {"slaveof",slaveofCommand,3,REDIS_CMD_INLINE,NULL,0,0,0},
     {"debug",debugCommand,-2,REDIS_CMD_INLINE,NULL,0,0,0},
+    {"config",configCommand,-2,REDIS_CMD_BULK,NULL,0,0,0},
     {NULL,NULL,0,0,NULL,0,0,0}
 };
 
@@ -805,7 +807,7 @@ static void usage();
 /*============================ Utility functions ============================ */
 
 /* Glob-style pattern matching. */
-int stringmatchlen(const char *pattern, int patternLen,
+static int stringmatchlen(const char *pattern, int patternLen,
         const char *string, int stringLen, int nocase)
 {
     while(patternLen) {
@@ -927,6 +929,10 @@ int stringmatchlen(const char *pattern, int patternLen,
     return 0;
 }
 
+static int stringmatch(const char *pattern, const char *string, int nocase) {
+    return stringmatchlen(pattern,strlen(pattern),string,strlen(string),nocase);
+}
+
 static void redisLog(int level, const char *fmt, ...) {
     va_list ap;
     FILE *fp;
@@ -1495,9 +1501,9 @@ static void initServerConfig() {
     server.lastfsync = time(NULL);
     server.appendfd = -1;
     server.appendseldb = -1; /* Make sure the first time will not match */
-    server.pidfile = "/var/run/redis.pid";
-    server.dbfilename = "dump.rdb";
-    server.appendfilename = "appendonly.aof";
+    server.pidfile = zstrdup("/var/run/redis.pid");
+    server.dbfilename = zstrdup("dump.rdb");
+    server.appendfilename = zstrdup("appendonly.aof");
     server.requirepass = NULL;
     server.shareobjects = 0;
     server.rdbcompression = 1;
@@ -1762,8 +1768,10 @@ static void loadServerConfig(char *filename) {
         } else if (!strcasecmp(argv[0],"requirepass") && argc == 2) {
             server.requirepass = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"pidfile") && argc == 2) {
+            zfree(server.pidfile);
             server.pidfile = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"dbfilename") && argc == 2) {
+            zfree(server.dbfilename);
             server.dbfilename = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"vm-enabled") && argc == 2) {
             if ((server.vm_enabled = yesnotoi(argv[1])) == -1) {
@@ -2560,6 +2568,17 @@ static void addReplyBulk(redisClient *c, robj *obj) {
     addReply(c,shared.crlf);
 }
 
+/* In the CONFIG command we need to add vanilla C string as bulk replies */
+static void addReplyBulkCString(redisClient *c, char *s) {
+    if (s == NULL) {
+        addReply(c,shared.nullbulk);
+    } else {
+        robj *o = createStringObject(s,strlen(s));
+        addReplyBulk(c,o);
+        decrRefCount(o);
+    }
+}
+
 static void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     int cport, cfd;
     char cip[128];
@@ -6126,6 +6145,10 @@ static void flushdbCommand(redisClient *c) {
 static void flushallCommand(redisClient *c) {
     server.dirty += emptyDb();
     addReply(c,shared.ok);
+    if (server.bgsavechildpid != -1) {
+        kill(server.bgsavechildpid,SIGKILL);
+        rdbRemoveTempFile(server.bgsavechildpid);
+    }
     rdbSave(server.dbfilename);
     server.dirty++;
 }
@@ -9043,6 +9066,94 @@ static void handleClientsBlockedOnSwappedKey(redisDb *db, robj *key) {
     }
 }
 
+/* =========================== Remote Configuration ========================= */
+
+static void configSetCommand(redisClient *c) {
+    robj *o = getDecodedObject(c->argv[3]);
+    if (!strcasecmp(c->argv[2]->ptr,"dbfilename")) {
+        zfree(server.dbfilename);
+        server.dbfilename = zstrdup(o->ptr);
+    } else if (!strcasecmp(c->argv[2]->ptr,"requirepass")) {
+        zfree(server.requirepass);
+        server.requirepass = zstrdup(o->ptr);
+    } else if (!strcasecmp(c->argv[2]->ptr,"masterauth")) {
+        zfree(server.masterauth);
+        server.masterauth = zstrdup(o->ptr);
+    } else if (!strcasecmp(c->argv[2]->ptr,"maxmemory")) {
+        server.maxmemory = strtoll(o->ptr, NULL, 10);
+    } else {
+        addReplySds(c,sdscatprintf(sdsempty(),
+            "-ERR not supported CONFIG parameter %s\r\n",
+            (char*)c->argv[2]->ptr));
+        decrRefCount(o);
+        return;
+    }
+    decrRefCount(o);
+    addReply(c,shared.ok);
+}
+
+static void configGetCommand(redisClient *c) {
+    robj *o = getDecodedObject(c->argv[2]);
+    robj *lenobj = createObject(REDIS_STRING,NULL);
+    char *pattern = o->ptr;
+    int matches = 0;
+
+    addReply(c,lenobj);
+    decrRefCount(lenobj);
+
+    if (stringmatch(pattern,"dbfilename",0)) {
+        addReplyBulkCString(c,"dbfilename");
+        addReplyBulkCString(c,server.dbfilename);
+        matches++;
+    }
+    if (stringmatch(pattern,"requirepass",0)) {
+        addReplyBulkCString(c,"requirepass");
+        addReplyBulkCString(c,server.requirepass);
+        matches++;
+    }
+    if (stringmatch(pattern,"masterauth",0)) {
+        addReplyBulkCString(c,"masterauth");
+        addReplyBulkCString(c,server.masterauth);
+        matches++;
+    }
+    if (stringmatch(pattern,"maxmemory",0)) {
+        char buf[128];
+
+        snprintf(buf,128,"%llu\n",server.maxmemory);
+        addReplyBulkCString(c,"maxmemory");
+        addReplyBulkCString(c,buf);
+        matches++;
+    }
+    decrRefCount(o);
+    lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",matches*2);
+}
+
+static void configCommand(redisClient *c) {
+    if (!strcasecmp(c->argv[1]->ptr,"set")) {
+        if (c->argc != 4) goto badarity;
+        configSetCommand(c);
+    } else if (!strcasecmp(c->argv[1]->ptr,"get")) {
+        if (c->argc != 3) goto badarity;
+        configGetCommand(c);
+    } else if (!strcasecmp(c->argv[1]->ptr,"resetstat")) {
+        if (c->argc != 2) goto badarity;
+        server.stat_numcommands = 0;
+        server.stat_numconnections = 0;
+        server.stat_expiredkeys = 0;
+        server.stat_starttime = time(NULL);
+        addReply(c,shared.ok);
+    } else {
+        addReplySds(c,sdscatprintf(sdsempty(),
+            "-ERR CONFIG subcommand must be one of GET, SET, RESETSTAT\r\n"));
+    }
+    return;
+
+badarity:
+    addReplySds(c,sdscatprintf(sdsempty(),
+        "-ERR Wrong number of arguments for CONFIG %s\r\n",
+        (char*) c->argv[1]->ptr));
+}
+
 /* ================================= Debugging ============================== */
 
 static void debugCommand(redisClient *c) {