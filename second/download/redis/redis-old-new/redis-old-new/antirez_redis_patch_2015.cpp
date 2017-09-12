@@ -45,8 +45,7 @@ robj *lookupKeyRead(redisDb *db, robj *key) {
 }
 
 robj *lookupKeyWrite(redisDb *db, robj *key) {
-    deleteIfVolatile(db,key);
-    touchWatchedKey(db,key);
+    expireIfNeeded(db,key);
     return lookupKey(db,key);
 }
 
@@ -322,7 +321,6 @@ void renameGenericCommand(redisClient *c, int nx) {
         return;
 
     incrRefCount(o);
-    deleteIfVolatile(c->db,c->argv[2]);
     if (dbAdd(c->db,c->argv[2],o) == REDIS_ERR) {
         if (nx) {
             decrRefCount(o);
@@ -332,6 +330,7 @@ void renameGenericCommand(redisClient *c, int nx) {
         dbReplace(c->db,c->argv[2],o);
     }
     dbDelete(c->db,c->argv[1]);
+    touchWatchedKey(c->db,c->argv[1]);
     touchWatchedKey(c->db,c->argv[2]);
     server.dirty++;
     addReply(c,nx ? shared.cone : shared.ok);
@@ -375,7 +374,6 @@ void moveCommand(redisClient *c) {
     }
 
     /* Try to add the element to the target DB */
-    deleteIfVolatile(dst,c->argv[1]);
     if (dbAdd(dst,c->argv[1],o) == REDIS_ERR) {
         addReply(c,shared.czero);
         return;
@@ -396,23 +394,16 @@ int removeExpire(redisDb *db, robj *key) {
     /* An expire may only be removed if there is a corresponding entry in the
      * main dict. Otherwise, the key will never be freed. */
     redisAssert(dictFind(db->dict,key->ptr) != NULL);
-    if (dictDelete(db->expires,key->ptr) == DICT_OK) {
-        return 1;
-    } else {
-        return 0;
-    }
+    return dictDelete(db->expires,key->ptr) == DICT_OK;
 }
 
-int setExpire(redisDb *db, robj *key, time_t when) {
+void setExpire(redisDb *db, robj *key, time_t when) {
     dictEntry *de;
 
     /* Reuse the sds from the main dict in the expire dict */
-    redisAssert((de = dictFind(db->dict,key->ptr)) != NULL);
-    if (dictAdd(db->expires,dictGetEntryKey(de),(void*)when) == DICT_ERR) {
-        return 0;
-    } else {
-        return 1;
-    }
+    de = dictFind(db->dict,key->ptr);
+    redisAssert(de != NULL);
+    dictReplace(db->expires,dictGetEntryKey(de),(void*)when);
 }
 
 /* Return the expire time of the specified key, or -1 if no expire
@@ -430,8 +421,46 @@ time_t getExpire(redisDb *db, robj *key) {
     return (time_t) dictGetEntryVal(de);
 }
 
+/* Propagate expires into slaves and the AOF file.
+ * When a key expires in the master, a DEL operation for this key is sent
+ * to all the slaves and the AOF file if enabled.
+ *
+ * This way the key expiry is centralized in one place, and since both
+ * AOF and the master->slave link guarantee operation ordering, everything
+ * will be consistent even if we allow write operations against expiring
+ * keys. */
+void propagateExpire(redisDb *db, robj *key) {
+    struct redisCommand *cmd;
+    robj *argv[2];
+
+    cmd = lookupCommand("del");
+    argv[0] = createStringObject("DEL",3);
+    argv[1] = key;
+    incrRefCount(key);
+
+    if (server.appendonly)
+        feedAppendOnlyFile(cmd,db->id,argv,2);
+    if (listLength(server.slaves))
+        replicationFeedSlaves(server.slaves,db->id,argv,2);
+
+    decrRefCount(argv[0]);
+    decrRefCount(argv[1]);
+}
+
 int expireIfNeeded(redisDb *db, robj *key) {
     time_t when = getExpire(db,key);
+
+    /* If we are running in the context of a slave, return ASAP:
+     * the slave key expiration is controlled by the master that will
+     * send us synthesized DEL operations for expired keys.
+     *
+     * Still we try to return the right information to the caller, 
+     * that is, 0 if we think the key should be still valid, 1 if
+     * we think the key is expired at this time. */
+    if (server.masterhost != NULL) {
+        return time(NULL) > when;
+    }
+
     if (when < 0) return 0;
 
     /* Return when this key has not expired */
@@ -440,15 +469,7 @@ int expireIfNeeded(redisDb *db, robj *key) {
     /* Delete the key */
     server.stat_expiredkeys++;
     server.dirty++;
-    return dbDelete(db,key);
-}
-
-int deleteIfVolatile(redisDb *db, robj *key) {
-    if (getExpire(db,key) < 0) return 0;
-
-    /* Delete the key */
-    server.stat_expiredkeys++;
-    server.dirty++;
+    propagateExpire(db,key);
     return dbDelete(db,key);
 }
 
@@ -472,15 +493,14 @@ void expireGenericCommand(redisClient *c, robj *key, robj *param, long offset) {
     if (seconds <= 0) {
         if (dbDelete(c->db,key)) server.dirty++;
         addReply(c, shared.cone);
+        touchWatchedKey(c->db,key);
         return;
     } else {
         time_t when = time(NULL)+seconds;
-        if (setExpire(c->db,key,when)) {
-            addReply(c,shared.cone);
-            server.dirty++;
-        } else {
-            addReply(c,shared.czero);
-        }
+        setExpire(c->db,key,when);
+        addReply(c,shared.cone);
+        touchWatchedKey(c->db,key);
+        server.dirty++;
         return;
     }
 }
@@ -505,4 +525,18 @@ void ttlCommand(redisClient *c) {
     addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",ttl));
 }
 
+void persistCommand(redisClient *c) {
+    dictEntry *de;
 
+    de = dictFind(c->db->dict,c->argv[1]->ptr);
+    if (de == NULL) {
+        addReply(c,shared.czero);
+    } else {
+        if (removeExpire(c->db,c->argv[1])) {
+            addReply(c,shared.cone);
+            server.dirty++;
+        } else {
+            addReply(c,shared.czero);
+        }
+    }
+}