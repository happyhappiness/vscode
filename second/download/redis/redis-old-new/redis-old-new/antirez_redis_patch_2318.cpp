@@ -85,7 +85,6 @@
 
 /* Hash table parameters */
 #define REDIS_HT_MINFILL        10      /* Minimal hash table fill 10% */
-#define REDIS_HT_MINSLOTS       16384   /* Never resize the HT under this */
 
 /* Command flags */
 #define REDIS_CMD_BULK          1       /* Bulk write command */
@@ -370,6 +369,7 @@ static void sremCommand(redisClient *c);
 static void smoveCommand(redisClient *c);
 static void sismemberCommand(redisClient *c);
 static void scardCommand(redisClient *c);
+static void spopCommand(redisClient *c);
 static void sinterCommand(redisClient *c);
 static void sinterstoreCommand(redisClient *c);
 static void sunionCommand(redisClient *c);
@@ -417,6 +417,7 @@ static struct redisCommand cmdTable[] = {
     {"smove",smoveCommand,4,REDIS_CMD_BULK},
     {"sismember",sismemberCommand,3,REDIS_CMD_BULK},
     {"scard",scardCommand,2,REDIS_CMD_INLINE},
+    {"spop",spopCommand,2,REDIS_CMD_INLINE},
     {"sinter",sinterCommand,-2,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM},
     {"sinterstore",sinterstoreCommand,-3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM},
     {"sunion",sunionCommand,-2,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM},
@@ -691,22 +692,28 @@ static void closeTimedoutClients(void) {
     }
 }
 
+static int htNeedsResize(dict *dict) {
+    long long size, used;
+
+    size = dictSlots(dict);
+    used = dictSize(dict);
+    return (size && used && size > DICT_HT_INITIAL_SIZE &&
+            (used*100/size < REDIS_HT_MINFILL));
+}
+
 /* If the percentage of used slots in the HT reaches REDIS_HT_MINFILL
  * we resize the hash table to save memory */
 static void tryResizeHashTables(void) {
     int j;
 
     for (j = 0; j < server.dbnum; j++) {
-        long long size, used;
-
-        size = dictSlots(server.db[j].dict);
-        used = dictSize(server.db[j].dict);
-        if (size && used && size > REDIS_HT_MINSLOTS &&
-            (used*100/size < REDIS_HT_MINFILL)) {
-            redisLog(REDIS_NOTICE,"The hash table %d is too sparse, resize it...",j);
+        if (htNeedsResize(server.db[j].dict)) {
+            redisLog(REDIS_DEBUG,"The hash table %d is too sparse, resize it...",j);
             dictResize(server.db[j].dict);
-            redisLog(REDIS_NOTICE,"Hash table %d resized.",j);
+            redisLog(REDIS_DEBUG,"Hash table %d resized.",j);
         }
+        if (htNeedsResize(server.db[j].expires))
+            dictResize(server.db[j].expires);
     }
 }
 
@@ -2961,6 +2968,7 @@ static void sremCommand(redisClient *c) {
         }
         if (dictDelete(set->ptr,c->argv[2]) == DICT_OK) {
             server.dirty++;
+            if (htNeedsResize(set->ptr)) dictResize(set->ptr);
             addReply(c,shared.cone);
         } else {
             addReply(c,shared.czero);
@@ -3040,6 +3048,34 @@ static void scardCommand(redisClient *c) {
     }
 }
 
+static void spopCommand(redisClient *c) {
+    robj *set;
+    dictEntry *de;
+
+    set = lookupKeyWrite(c->db,c->argv[1]);
+    if (set == NULL) {
+        addReply(c,shared.nullbulk);
+    } else {
+        if (set->type != REDIS_SET) {
+            addReply(c,shared.wrongtypeerr);
+            return;
+        }
+        de = dictGetRandomKey(set->ptr);
+        if (de == NULL) {
+            addReply(c,shared.nullbulk);
+        } else {
+            robj *ele = dictGetEntryKey(de);
+
+            addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",sdslen(ele->ptr)));
+            addReply(c,ele);
+            addReply(c,shared.crlf);
+            dictDelete(set->ptr,ele);
+            if (htNeedsResize(set->ptr)) dictResize(set->ptr);
+            server.dirty++;
+        }
+    }
+}
+
 static int qsortCompareSetsByCardinality(const void *s1, const void *s2) {
     dict **d1 = (void*) s1, **d2 = (void*) s2;
 
@@ -4170,6 +4206,7 @@ static struct redisFunctionSym symsTable[] = {
 {"smoveCommand", (unsigned long)smoveCommand},
 {"sismemberCommand", (unsigned long)sismemberCommand},
 {"scardCommand", (unsigned long)scardCommand},
+{"spopCommand", (unsigned long)spopCommand},
 {"sinterCommand", (unsigned long)sinterCommand},
 {"sinterstoreCommand", (unsigned long)sinterstoreCommand},
 {"sunionCommand", (unsigned long)sunionCommand},
@@ -4296,6 +4333,9 @@ static void setupSigSegvAction(void) {
     act.sa_sigaction = segvHandler;
     sigaction (SIGSEGV, &act, NULL);
     sigaction (SIGBUS, &act, NULL);
+    sigaction (SIGFPE, &act, NULL);
+    sigaction (SIGILL, &act, NULL);
+    sigaction (SIGBUS, &act, NULL);
     return;
 }
 #else /* HAVE_BACKTRACE */