@@ -399,10 +399,13 @@ static void infoCommand(redisClient *c);
 static void mgetCommand(redisClient *c);
 static void monitorCommand(redisClient *c);
 static void expireCommand(redisClient *c);
-static void getSetCommand(redisClient *c);
+static void getsetCommand(redisClient *c);
 static void ttlCommand(redisClient *c);
 static void slaveofCommand(redisClient *c);
 static void debugCommand(redisClient *c);
+static void msetCommand(redisClient *c);
+static void msetnxCommand(redisClient *c);
+
 /*================================= Globals ================================= */
 
 /* Global vars */
@@ -441,7 +444,9 @@ static struct redisCommand cmdTable[] = {
     {"smembers",sinterCommand,2,REDIS_CMD_INLINE},
     {"incrby",incrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM},
     {"decrby",decrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM},
-    {"getset",getSetCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM},
+    {"getset",getsetCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM},
+    {"mset",msetCommand,-3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM},
+    {"msetnx",msetnxCommand,-3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM},
     {"randomkey",randomkeyCommand,1,REDIS_CMD_INLINE},
     {"select",selectCommand,2,REDIS_CMD_INLINE},
     {"move",moveCommand,3,REDIS_CMD_INLINE},
@@ -2596,7 +2601,7 @@ static void getCommand(redisClient *c) {
     }
 }
 
-static void getSetCommand(redisClient *c) {
+static void getsetCommand(redisClient *c) {
     getCommand(c);
     if (dictAdd(c->db->dict,c->argv[1],c->argv[2]) == DICT_ERR) {
         dictReplace(c->db->dict,c->argv[1],c->argv[2]);
@@ -4094,6 +4099,42 @@ static void ttlCommand(redisClient *c) {
     addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",ttl));
 }
 
+static void msetGenericCommand(redisClient *c, int nx) {
+    int j;
+
+    if ((c->argc % 2) == 0) {
+        addReplySds(c,sdsnew("-ERR wrong number of arguments\r\n"));
+        return;
+    }
+    /* Handle the NX flag. The MSETNX semantic is to return zero and don't
+     * set nothing at all if at least one already key exists. */
+    if (nx) {
+        for (j = 1; j < c->argc; j += 2) {
+            if (dictFind(c->db->dict,c->argv[j]) != NULL) {
+                addReply(c, shared.czero);
+                return;
+            }
+        }
+    }
+
+    for (j = 1; j < c->argc; j += 2) {
+        dictAdd(c->db->dict,c->argv[j],c->argv[j+1]);
+        incrRefCount(c->argv[j]);
+        incrRefCount(c->argv[j+1]);
+        removeExpire(c->db,c->argv[j]);
+    }
+    server.dirty += (c->argc-1)/2;
+    addReply(c, nx ? shared.cone : shared.ok);
+}
+
+static void msetCommand(redisClient *c) {
+    msetGenericCommand(c,0);
+}
+
+static void msetnxCommand(redisClient *c) {
+    msetGenericCommand(c,1);
+}
+
 /* =============================== Replication  ============================= */
 
 static int syncWrite(int fd, char *ptr, ssize_t size, int timeout) {
@@ -4586,14 +4627,17 @@ static struct redisFunctionSym symsTable[] = {
 {"mgetCommand", (unsigned long)mgetCommand},
 {"monitorCommand", (unsigned long)monitorCommand},
 {"expireCommand", (unsigned long)expireCommand},
-{"getSetCommand", (unsigned long)getSetCommand},
+{"getsetCommand", (unsigned long)getsetCommand},
 {"ttlCommand", (unsigned long)ttlCommand},
 {"slaveofCommand", (unsigned long)slaveofCommand},
 {"debugCommand", (unsigned long)debugCommand},
 {"processCommand", (unsigned long)processCommand},
 {"setupSigSegvAction", (unsigned long)setupSigSegvAction},
 {"readQueryFromClient", (unsigned long)readQueryFromClient},
 {"rdbRemoveTempFile", (unsigned long)rdbRemoveTempFile},
+{"msetGenericCommand", (unsigned long)msetGenericCommand},
+{"msetCommand", (unsigned long)msetCommand},
+{"msetnxCommand", (unsigned long)msetnxCommand},
 {NULL,0}
 };
 