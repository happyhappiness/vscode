@@ -281,6 +281,7 @@ static void flushallCommand(redisClient *c);
 static void sortCommand(redisClient *c);
 static void lremCommand(redisClient *c);
 static void infoCommand(redisClient *c);
+static void mgetCommand(redisClient *c);
 
 /*================================= Globals ================================= */
 
@@ -294,6 +295,7 @@ static struct redisCommand cmdTable[] = {
     {"exists",existsCommand,2,REDIS_CMD_INLINE},
     {"incr",incrCommand,2,REDIS_CMD_INLINE},
     {"decr",decrCommand,2,REDIS_CMD_INLINE},
+    {"mget",mgetCommand,-2,REDIS_CMD_INLINE},
     {"rpush",rpushCommand,3,REDIS_CMD_BULK},
     {"lpush",lpushCommand,3,REDIS_CMD_BULK},
     {"rpop",rpopCommand,2,REDIS_CMD_INLINE},
@@ -1696,6 +1698,29 @@ static void getCommand(redisClient *c) {
     }
 }
 
+static void mgetCommand(redisClient *c) {
+    dictEntry *de;
+    int j;
+  
+    addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",c->argc-1));
+    for (j = 1; j < c->argc; j++) {
+        de = dictFind(c->dict,c->argv[j]);
+        if (de == NULL) {
+            addReply(c,shared.minus1);
+        } else {
+            robj *o = dictGetEntryVal(de);
+            
+            if (o->type != REDIS_STRING) {
+                addReply(c,shared.minus1);
+            } else {
+                addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",(int)sdslen(o->ptr)));
+                addReply(c,o);
+                addReply(c,shared.crlf);
+            }
+        }
+    }
+}
+
 static void incrDecrCommand(redisClient *c, int incr) {
     dictEntry *de;
     long long value;
@@ -2790,6 +2815,7 @@ static void infoCommand(redisClient *c) {
     );
     addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",sdslen(info)));
     addReplySds(c,info);
+    addReply(c,shared.crlf);
 }
 
 /* =============================== Replication  ============================= */