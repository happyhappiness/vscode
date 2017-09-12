@@ -45,7 +45,7 @@ robj *lookupKeyRead(redisDb *db, robj *key) {
 }
 
 robj *lookupKeyWrite(redisDb *db, robj *key) {
-    deleteIfVolatile(db,key);
+    expireIfNeeded(db,key);
     return lookupKey(db,key);
 }
 
@@ -123,6 +123,11 @@ robj *dbRandomKey(redisDb *db) {
 
 /* Delete a key, value, and associated expiration entry if any, from the DB */
 int dbDelete(redisDb *db, robj *key) {
+    /* If VM is enabled make sure to awake waiting clients for this key:
+     * deleting the key will kill the I/O thread bringing the key from swap
+     * to memory, so the client will never be notified and unblocked if we
+     * don't do it now. */
+    if (server.vm_enabled) handleClientsBlockedOnSwappedKey(db,key);
     /* Deleting an entry from the expires dict will not free the sds of
      * the key, because it is shared with the main dictionary. */
     if (dictSize(db->expires) > 0) dictDelete(db->expires,key->ptr);
@@ -199,7 +204,7 @@ void selectCommand(redisClient *c) {
     int id = atoi(c->argv[1]->ptr);
 
     if (selectDb(c,id) == REDIS_ERR) {
-        addReplySds(c,sdsnew("-ERR invalid DB index\r\n"));
+        addReplyError(c,"invalid DB index");
     } else {
         addReply(c,shared.ok);
     }
@@ -221,19 +226,17 @@ void keysCommand(redisClient *c) {
     dictIterator *di;
     dictEntry *de;
     sds pattern = c->argv[1]->ptr;
-    int plen = sdslen(pattern);
+    int plen = sdslen(pattern), allkeys;
     unsigned long numkeys = 0;
-    robj *lenobj = createObject(REDIS_STRING,NULL);
+    void *replylen = addDeferredMultiBulkLength(c);
 
     di = dictGetIterator(c->db->dict);
-    addReply(c,lenobj);
-    decrRefCount(lenobj);
+    allkeys = (pattern[0] == '*' && pattern[1] == '\0');
     while((de = dictNext(di)) != NULL) {
         sds key = dictGetEntryKey(de);
         robj *keyobj;
 
-        if ((pattern[0] == '*' && pattern[1] == '\0') ||
-            stringmatchlen(pattern,plen,key,sdslen(key),0)) {
+        if (allkeys || stringmatchlen(pattern,plen,key,sdslen(key),0)) {
             keyobj = createStringObject(key,sdslen(key));
             if (expireIfNeeded(c->db,keyobj) == 0) {
                 addReplyBulk(c,keyobj);
@@ -243,17 +246,15 @@ void keysCommand(redisClient *c) {
         }
     }
     dictReleaseIterator(di);
-    lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",numkeys);
+    setDeferredMultiBulkLength(c,replylen,numkeys);
 }
 
 void dbsizeCommand(redisClient *c) {
-    addReplySds(c,
-        sdscatprintf(sdsempty(),":%lu\r\n",dictSize(c->db->dict)));
+    addReplyLongLong(c,dictSize(c->db->dict));
 }
 
 void lastsaveCommand(redisClient *c) {
-    addReplySds(c,
-        sdscatprintf(sdsempty(),":%lu\r\n",server.lastsave));
+    addReplyLongLong(c,server.lastsave);
 }
 
 void typeCommand(redisClient *c) {
@@ -262,24 +263,23 @@ void typeCommand(redisClient *c) {
 
     o = lookupKeyRead(c->db,c->argv[1]);
     if (o == NULL) {
-        type = "+none";
+        type = "none";
     } else {
         switch(o->type) {
-        case REDIS_STRING: type = "+string"; break;
-        case REDIS_LIST: type = "+list"; break;
-        case REDIS_SET: type = "+set"; break;
-        case REDIS_ZSET: type = "+zset"; break;
-        case REDIS_HASH: type = "+hash"; break;
-        default: type = "+unknown"; break;
+        case REDIS_STRING: type = "string"; break;
+        case REDIS_LIST: type = "list"; break;
+        case REDIS_SET: type = "set"; break;
+        case REDIS_ZSET: type = "zset"; break;
+        case REDIS_HASH: type = "hash"; break;
+        default: type = "unknown"; break;
         }
     }
-    addReplySds(c,sdsnew(type));
-    addReply(c,shared.crlf);
+    addReplyStatus(c,type);
 }
 
 void saveCommand(redisClient *c) {
     if (server.bgsavechildpid != -1) {
-        addReplySds(c,sdsnew("-ERR background save in progress\r\n"));
+        addReplyError(c,"Background save already in progress");
         return;
     }
     if (rdbSave(server.dbfilename) == REDIS_OK) {
@@ -291,12 +291,11 @@ void saveCommand(redisClient *c) {
 
 void bgsaveCommand(redisClient *c) {
     if (server.bgsavechildpid != -1) {
-        addReplySds(c,sdsnew("-ERR background save already in progress\r\n"));
+        addReplyError(c,"Background save already in progress");
         return;
     }
     if (rdbSaveBackground(server.dbfilename) == REDIS_OK) {
-        char *status = "+Background saving started\r\n";
-        addReplySds(c,sdsnew(status));
+        addReplyStatus(c,"Background saving started");
     } else {
         addReply(c,shared.err);
     }
@@ -305,7 +304,7 @@ void bgsaveCommand(redisClient *c) {
 void shutdownCommand(redisClient *c) {
     if (prepareForShutdown() == REDIS_OK)
         exit(0);
-    addReplySds(c, sdsnew("-ERR Errors trying to SHUTDOWN. Check logs.\r\n"));
+    addReplyError(c,"Errors trying to SHUTDOWN. Check logs.");
 }
 
 void renameGenericCommand(redisClient *c, int nx) {
@@ -321,7 +320,6 @@ void renameGenericCommand(redisClient *c, int nx) {
         return;
 
     incrRefCount(o);
-    deleteIfVolatile(c->db,c->argv[2]);
     if (dbAdd(c->db,c->argv[2],o) == REDIS_ERR) {
         if (nx) {
             decrRefCount(o);
@@ -375,7 +373,6 @@ void moveCommand(redisClient *c) {
     }
 
     /* Try to add the element to the target DB */
-    deleteIfVolatile(dst,c->argv[1]);
     if (dbAdd(dst,c->argv[1],o) == REDIS_ERR) {
         addReply(c,shared.czero);
         return;
@@ -396,23 +393,16 @@ int removeExpire(redisDb *db, robj *key) {
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
@@ -430,8 +420,46 @@ time_t getExpire(redisDb *db, robj *key) {
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
@@ -440,15 +468,7 @@ int expireIfNeeded(redisDb *db, robj *key) {
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
 
@@ -458,7 +478,7 @@ int deleteIfVolatile(redisDb *db, robj *key) {
 
 void expireGenericCommand(redisClient *c, robj *key, robj *param, long offset) {
     dictEntry *de;
-    time_t seconds;
+    long seconds;
 
     if (getLongFromObjectOrReply(c, param, &seconds, NULL) != REDIS_OK) return;
 
@@ -476,13 +496,10 @@ void expireGenericCommand(redisClient *c, robj *key, robj *param, long offset) {
         return;
     } else {
         time_t when = time(NULL)+seconds;
-        if (setExpire(c->db,key,when)) {
-            addReply(c,shared.cone);
-            touchWatchedKey(c->db,key);
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
@@ -496,13 +513,28 @@ void expireatCommand(redisClient *c) {
 }
 
 void ttlCommand(redisClient *c) {
-    time_t expire;
-    int ttl = -1;
+    time_t expire, ttl = -1;
 
     expire = getExpire(c->db,c->argv[1]);
     if (expire != -1) {
-        ttl = (int) (expire-time(NULL));
+        ttl = (expire-time(NULL));
         if (ttl < 0) ttl = -1;
     }
-    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",ttl));
+    addReplyLongLong(c,(long long)ttl);
+}
+
+void persistCommand(redisClient *c) {
+    dictEntry *de;
+
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
 }