@@ -71,6 +71,7 @@
 #define REDIS_CONFIGLINE_MAX    1024
 #define REDIS_OBJFREELIST_MAX   1000000 /* Max number of objects to cache */
 #define REDIS_MAX_SYNC_TIME     60      /* Slave can't take more to sync */
+#define REDIS_EXPIRELOOKUPS_PER_CRON    100 /* try to expire 100 keys/second */
 
 /* Hash table parameters */
 #define REDIS_HT_MINFILL        10      /* Minimal hash table fill 10% */
@@ -285,6 +286,7 @@ static robj *tryObjectSharing(robj *o);
 static int removeExpire(redisDb *db, robj *key);
 static int expireIfNeeded(redisDb *db, robj *key);
 static int deleteIfVolatile(redisDb *db, robj *key);
+static int deleteKey(redisDb *db, robj *key);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -628,7 +630,7 @@ void closeTimedoutClients(void) {
 }
 
 int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
-    int j, size, used, loops = server.cronloops++;
+    int j, loops = server.cronloops++;
     REDIS_NOTUSED(eventLoop);
     REDIS_NOTUSED(id);
     REDIS_NOTUSED(clientData);
@@ -639,10 +641,13 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
     /* If the percentage of used slots in the HT reaches REDIS_HT_MINFILL
      * we resize the hash table to save memory */
     for (j = 0; j < server.dbnum; j++) {
+        int size, used, vkeys;
+
         size = dictSlots(server.db[j].dict);
         used = dictSize(server.db[j].dict);
+        vkeys = dictSize(server.db[j].expires);
         if (!(loops % 5) && used > 0) {
-            redisLog(REDIS_DEBUG,"DB %d: %d keys in %d slots HT.",j,used,size);
+            redisLog(REDIS_DEBUG,"DB %d: %d keys (%d volatile) in %d slots HT.",j,used,vkeys,size);
             /* dictPrintStats(server.dict); */
         }
         if (size && used && size > REDIS_HT_MINSLOTS &&
@@ -698,6 +703,30 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
             }
          }
     }
+
+    /* Try to expire a few timed out keys */
+    for (j = 0; j < server.dbnum; j++) {
+        redisDb *db = server.db+j;
+        int num = dictSize(db->expires);
+
+        if (num) {
+            time_t now = time(NULL);
+
+            if (num > REDIS_EXPIRELOOKUPS_PER_CRON)
+                num = REDIS_EXPIRELOOKUPS_PER_CRON;
+            while (num--) {
+                dictEntry *de;
+                time_t t;
+
+                if ((de = dictGetRandomKey(db->expires)) == NULL) break;
+                t = (time_t) dictGetEntryVal(de);
+                if (now > t) {
+                    deleteKey(db,dictGetEntryKey(de));
+                }
+            }
+        }
+    }
+
     /* Check if we should connect to a MASTER */
     if (server.replstate == REDIS_REPL_CONNECT) {
         redisLog(REDIS_NOTICE,"Connecting to MASTER...");
@@ -1446,10 +1475,19 @@ static void freeHashObject(robj *o) {
 
 static void incrRefCount(robj *o) {
     o->refcount++;
+#ifdef DEBUG_REFCOUNT
+    if (o->type == REDIS_STRING)
+        printf("Increment '%s'(%p), now is: %d\n",o->ptr,o,o->refcount);
+#endif
 }
 
 static void decrRefCount(void *obj) {
     robj *o = obj;
+
+#ifdef DEBUG_REFCOUNT
+    if (o->type == REDIS_STRING)
+        printf("Decrement '%s'(%p), now is: %d\n",o->ptr,o,o->refcount-1);
+#endif
     if (--(o->refcount) == 0) {
         switch(o->type) {
         case REDIS_STRING: freeStringObject(o); break;
@@ -1525,8 +1563,18 @@ static robj *lookupKeyWrite(redisDb *db, robj *key) {
 }
 
 static int deleteKey(redisDb *db, robj *key) {
+    int retval;
+
+    /* We need to protect key from destruction: after the first dictDelete()
+     * it may happen that 'key' is no longer valid if we don't increment
+     * it's count. This may happen when we get the object reference directly
+     * from the hash table with dictRandomKey() or dict iterators */
+    incrRefCount(key);
     if (dictSize(db->expires)) dictDelete(db->expires,key);
-    return dictDelete(db->dict,key) == DICT_OK;
+    retval = dictDelete(db->dict,key);
+    decrRefCount(key);
+
+    return retval == DICT_OK;
 }
 
 /*============================ DB saving/loading ============================ */