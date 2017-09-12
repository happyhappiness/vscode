@@ -157,6 +157,7 @@
 #define REDIS_SLAVE 2       /* This client is a slave server */
 #define REDIS_MASTER 4      /* This client is a master server */
 #define REDIS_MONITOR 8      /* This client is a slave monitor, see MONITOR */
+#define REDIS_MULTI 16      /* This client is in a MULTI context */
 
 /* Slave replication state - slave side */
 #define REDIS_REPL_NONE 0   /* No active replication */
@@ -230,6 +231,18 @@ typedef struct redisDb {
     int id;
 } redisDb;
 
+/* Client MULTI/EXEC state */
+typedef struct multiCmd {
+    robj **argv;
+    int argc;
+    struct redisCommand *cmd;
+} multiCmd;
+
+typedef struct multiState {
+    multiCmd *commands;     /* Array of MULTI commands */
+    int count;              /* Total number of MULTI commands */
+} multiState;
+
 /* With multiplexing we need to take per-clinet state.
  * Clients are taken in a liked list. */
 typedef struct redisClient {
@@ -245,12 +258,14 @@ typedef struct redisClient {
     int sentlen;
     time_t lastinteraction; /* time of the last interaction, used for timeout */
     int flags;              /* REDIS_CLOSE | REDIS_SLAVE | REDIS_MONITOR */
+                            /* REDIS_MULTI */
     int slaveseldb;         /* slave selected db, if this client is a slave */
     int authenticated;      /* when requirepass is non-NULL */
     int replstate;          /* replication state if this is a slave */
     int repldbfd;           /* replication DB file descriptor */
-    long repldboff;          /* replication DB file offset */
+    long repldboff;         /* replication DB file offset */
     off_t repldbsize;       /* replication DB file size */
+    multiState mstate;      /* MULTI/EXEC state */
 } redisClient;
 
 struct saveparam {
@@ -368,7 +383,7 @@ typedef struct zset {
 
 struct sharedObjectsStruct {
     robj *crlf, *ok, *err, *emptybulk, *czero, *cone, *pong, *space,
-    *colon, *nullbulk, *nullmultibulk,
+    *colon, *nullbulk, *nullmultibulk, *queued,
     *emptymultibulk, *wrongtypeerr, *nokeyerr, *syntaxerr, *sameobjecterr,
     *outofrangeerr, *plus,
     *select0, *select1, *select2, *select3, *select4,
@@ -419,6 +434,9 @@ static zskiplist *zslCreate(void);
 static void zslFree(zskiplist *zsl);
 static void zslInsert(zskiplist *zsl, double score, robj *obj);
 static void sendReplyToClientWritev(aeEventLoop *el, int fd, void *privdata, int mask);
+static void initClientMultiState(redisClient *c);
+static void freeClientMultiState(redisClient *c);
+static void queueMultiCommand(redisClient *c, struct redisCommand *cmd);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -493,6 +511,8 @@ static void zcardCommand(redisClient *c);
 static void zremCommand(redisClient *c);
 static void zscoreCommand(redisClient *c);
 static void zremrangebyscoreCommand(redisClient *c);
+static void multiCommand(redisClient *c);
+static void execCommand(redisClient *c);
 
 /*================================= Globals ================================= */
 
@@ -564,6 +584,8 @@ static struct redisCommand cmdTable[] = {
     {"shutdown",shutdownCommand,1,REDIS_CMD_INLINE},
     {"lastsave",lastsaveCommand,1,REDIS_CMD_INLINE},
     {"type",typeCommand,2,REDIS_CMD_INLINE},
+    {"multi",multiCommand,1,REDIS_CMD_INLINE},
+    {"exec",execCommand,1,REDIS_CMD_INLINE},
     {"sync",syncCommand,1,REDIS_CMD_INLINE},
     {"flushdb",flushdbCommand,1,REDIS_CMD_INLINE},
     {"flushall",flushallCommand,1,REDIS_CMD_INLINE},
@@ -1083,6 +1105,7 @@ static void createSharedObjects(void) {
     shared.nullmultibulk = createObject(REDIS_STRING,sdsnew("*-1\r\n"));
     shared.emptymultibulk = createObject(REDIS_STRING,sdsnew("*0\r\n"));
     shared.pong = createObject(REDIS_STRING,sdsnew("+PONG\r\n"));
+    shared.queued = createObject(REDIS_STRING,sdsnew("+QUEUED\r\n"));
     shared.wrongtypeerr = createObject(REDIS_STRING,sdsnew(
         "-ERR Operation against a key holding the wrong kind of value\r\n"));
     shared.nokeyerr = createObject(REDIS_STRING,sdsnew(
@@ -1432,6 +1455,7 @@ static void freeClient(redisClient *c) {
     }
     zfree(c->argv);
     zfree(c->mbargv);
+    freeClientMultiState(c);
     zfree(c);
 }
 
@@ -1622,6 +1646,21 @@ static void resetClient(redisClient *c) {
     c->multibulk = 0;
 }
 
+/* Call() is the core of Redis execution of a command */
+static void call(redisClient *c, struct redisCommand *cmd) {
+    long long dirty;
+
+    dirty = server.dirty;
+    cmd->proc(c);
+    if (server.appendonly && server.dirty-dirty)
+        feedAppendOnlyFile(cmd,c->db->id,c->argv,c->argc);
+    if (server.dirty-dirty && listLength(server.slaves))
+        replicationFeedSlaves(server.slaves,cmd,c->db->id,c->argv,c->argc);
+    if (listLength(server.monitors))
+        replicationFeedSlaves(server.monitors,cmd,c->db->id,c->argv,c->argc);
+    server.stat_numcommands++;
+}
+
 /* If this function gets called we already read a whole
  * command, argments are in the client argv/argc fields.
  * processCommand() execute the command or prepare the
@@ -1632,7 +1671,6 @@ static void resetClient(redisClient *c) {
  * if 0 is returned the client was destroied (i.e. after QUIT). */
 static int processCommand(redisClient *c) {
     struct redisCommand *cmd;
-    long long dirty;
 
     /* Free some memory if needed (maxmemory setting) */
     if (server.maxmemory) freeMemoryIfNeeded();
@@ -1773,15 +1811,12 @@ static int processCommand(redisClient *c) {
     }
 
     /* Exec the command */
-    dirty = server.dirty;
-    cmd->proc(c);
-    if (server.appendonly && server.dirty-dirty)
-        feedAppendOnlyFile(cmd,c->db->id,c->argv,c->argc);
-    if (server.dirty-dirty && listLength(server.slaves))
-        replicationFeedSlaves(server.slaves,cmd,c->db->id,c->argv,c->argc);
-    if (listLength(server.monitors))
-        replicationFeedSlaves(server.monitors,cmd,c->db->id,c->argv,c->argc);
-    server.stat_numcommands++;
+    if (c->flags & REDIS_MULTI && cmd->proc != execCommand) {
+        queueMultiCommand(c,cmd);
+        addReply(c,shared.queued);
+    } else {
+        call(c,cmd);
+    }
 
     /* Prepare the client for the next command */
     if (c->flags & REDIS_CLOSE) {
@@ -2007,6 +2042,7 @@ static redisClient *createClient(int fd) {
         return NULL;
     }
     listAddNodeTail(server.clients,c);
+    initClientMultiState(c);
     return c;
 }
 
@@ -5287,6 +5323,75 @@ static void ttlCommand(redisClient *c) {
     addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",ttl));
 }
 
+/* ================================ MULTI/EXEC ============================== */
+
+/* Client state initialization for MULTI/EXEC */
+static void initClientMultiState(redisClient *c) {
+    c->mstate.commands = NULL;
+    c->mstate.count = 0;
+}
+
+/* Release all the resources associated with MULTI/EXEC state */
+static void freeClientMultiState(redisClient *c) {
+    int j;
+
+    for (j = 0; j < c->mstate.count; j++) {
+        int i;
+        multiCmd *mc = c->mstate.commands+j;
+
+        for (i = 0; i < mc->argc; i++)
+            decrRefCount(mc->argv[i]);
+        zfree(mc->argv);
+    }
+    zfree(c->mstate.commands);
+}
+
+/* Add a new command into the MULTI commands queue */
+static void queueMultiCommand(redisClient *c, struct redisCommand *cmd) {
+    multiCmd *mc;
+    int j;
+
+    c->mstate.commands = zrealloc(c->mstate.commands,
+            sizeof(multiCmd)*(c->mstate.count+1));
+    mc = c->mstate.commands+c->mstate.count;
+    mc->cmd = cmd;
+    mc->argc = c->argc;
+    mc->argv = zmalloc(sizeof(robj*)*c->argc);
+    memcpy(mc->argv,c->argv,sizeof(robj*)*c->argc);
+    for (j = 0; j < c->argc; j++)
+        incrRefCount(mc->argv[j]);
+    c->mstate.count++;
+}
+
+static void multiCommand(redisClient *c) {
+    c->flags |= REDIS_MULTI;
+}
+
+static void execCommand(redisClient *c) {
+    int j;
+    robj **orig_argv;
+    int orig_argc;
+
+    if (!(c->flags & REDIS_MULTI)) {
+        addReplySds(c,sdsnew("-ERR EXEC without MULTI\r\n"));
+        return;
+    }
+
+    orig_argv = c->argv;
+    orig_argc = c->argc;
+    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->mstate.count));
+    for (j = 0; j < c->mstate.count; j++) {
+        c->argc = c->mstate.commands[j].argc;
+        c->argv = c->mstate.commands[j].argv;
+        call(c,c->mstate.commands[j].cmd);
+    }
+    c->argv = orig_argv;
+    c->argc = orig_argc;
+    freeClientMultiState(c);
+    initClientMultiState(c);
+    c->flags &= (~REDIS_MULTI);
+}
+
 /* =============================== Replication  ============================= */
 
 static int syncWrite(int fd, char *ptr, ssize_t size, int timeout) {