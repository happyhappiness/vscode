@@ -592,8 +592,7 @@ static robj *getDecodedObject(robj *o);
 static int removeExpire(redisDb *db, robj *key);
 static int expireIfNeeded(redisDb *db, robj *key);
 static int deleteIfVolatile(redisDb *db, robj *key);
-static int deleteIfSwapped(redisDb *db, robj *key);
-static int deleteKey(redisDb *db, robj *key);
+static int dbDelete(redisDb *db, robj *key);
 static time_t getExpire(redisDb *db, robj *key);
 static int setExpire(redisDb *db, robj *key, time_t when);
 static void updateSlavesWaitingBgsave(int bgsaveerr);
@@ -1125,7 +1124,7 @@ static void dictListDestructor(void *privdata, void *val)
     listRelease((list*)val);
 }
 
-static int sdsDictKeyCompare(void *privdata, const void *key1,
+static int dictSdsKeyCompare(void *privdata, const void *key1,
         const void *key2)
 {
     int l1,l2;
@@ -1145,18 +1144,29 @@ static void dictRedisObjectDestructor(void *privdata, void *val)
     decrRefCount(val);
 }
 
+static void dictSdsDestructor(void *privdata, void *val)
+{
+    DICT_NOTUSED(privdata);
+
+    sdsfree(val);
+}
+
 static int dictObjKeyCompare(void *privdata, const void *key1,
         const void *key2)
 {
     const robj *o1 = key1, *o2 = key2;
-    return sdsDictKeyCompare(privdata,o1->ptr,o2->ptr);
+    return dictSdsKeyCompare(privdata,o1->ptr,o2->ptr);
 }
 
 static unsigned int dictObjHash(const void *key) {
     const robj *o = key;
     return dictGenHashFunction(o->ptr, sdslen((sds)o->ptr));
 }
 
+static unsigned int dictSdsHash(const void *key) {
+    return dictGenHashFunction((unsigned char*)key, sdslen((char*)key));
+}
+
 static int dictEncObjKeyCompare(void *privdata, const void *key1,
         const void *key2)
 {
@@ -1169,7 +1179,7 @@ static int dictEncObjKeyCompare(void *privdata, const void *key1,
 
     o1 = getDecodedObject(o1);
     o2 = getDecodedObject(o2);
-    cmp = sdsDictKeyCompare(privdata,o1->ptr,o2->ptr);
+    cmp = dictSdsKeyCompare(privdata,o1->ptr,o2->ptr);
     decrRefCount(o1);
     decrRefCount(o2);
     return cmp;
@@ -1198,7 +1208,7 @@ static unsigned int dictEncObjHash(const void *key) {
     }
 }
 
-/* Sets type and expires */
+/* Sets type */
 static dictType setDictType = {
     dictEncObjHash,            /* hash function */
     NULL,                      /* key dup */
@@ -1218,23 +1228,23 @@ static dictType zsetDictType = {
     dictVanillaFree            /* val destructor of malloc(sizeof(double)) */
 };
 
-/* Db->dict */
+/* Db->dict, keys are sds strings, vals are Redis objects. */
 static dictType dbDictType = {
-    dictObjHash,                /* hash function */
+    dictSdsHash,                /* hash function */
     NULL,                       /* key dup */
     NULL,                       /* val dup */
-    dictObjKeyCompare,          /* key compare */
-    dictRedisObjectDestructor,  /* key destructor */
+    dictSdsKeyCompare,          /* key compare */
+    dictSdsDestructor,          /* key destructor */
     dictRedisObjectDestructor   /* val destructor */
 };
 
 /* Db->expires */
 static dictType keyptrDictType = {
-    dictObjHash,               /* hash function */
+    dictSdsHash,               /* hash function */
     NULL,                      /* key dup */
     NULL,                      /* val dup */
-    dictObjKeyCompare,         /* key compare */
-    dictRedisObjectDestructor, /* key destructor */
+    dictSdsKeyCompare,         /* key compare */
+    dictSdsDestructor,         /* key destructor */
     NULL                       /* val destructor */
 };
 
@@ -1560,7 +1570,11 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
                 if ((de = dictGetRandomKey(db->expires)) == NULL) break;
                 t = (time_t) dictGetEntryVal(de);
                 if (now > t) {
-                    deleteKey(db,dictGetEntryKey(de));
+                    sds key = dictGetEntryKey(de);
+                    robj *keyobj = createStringObject(key,sdslen(key));
+
+                    dbDelete(db,keyobj);
+                    decrRefCount(keyobj);
                     expired++;
                     server.stat_expiredkeys++;
                 }
@@ -2909,6 +2923,12 @@ static void addReplyBulk(redisClient *c, robj *obj) {
     addReply(c,shared.crlf);
 }
 
+static void addReplyBulkSds(redisClient *c, sds s) {
+    robj *o = createStringObject(s, sdslen(s));
+    addReplyBulk(c,o);
+    decrRefCount(o);
+}
+
 /* In the CONFIG command we need to add vanilla C string as bulk replies */
 static void addReplyBulkCString(redisClient *c, char *s) {
     if (s == NULL) {
@@ -3357,9 +3377,8 @@ static int getLongFromObjectOrReply(redisClient *c, robj *o, long *target, const
 /* =========================== Keyspace access API ========================== */
 
 static robj *lookupKey(redisDb *db, robj *key) {
-    dictEntry *de = dictFind(db->dict,key);
+    dictEntry *de = dictFind(db->dict,key->ptr);
     if (de) {
-        robj *key = dictGetEntryKey(de);
         robj *val = dictGetEntryVal(de);
 
         if (server.vm_enabled) {
@@ -3369,7 +3388,7 @@ static robj *lookupKey(redisDb *db, robj *key) {
                 /* If we were swapping the object out, cancel the operation */
                 if (val->storage == REDIS_VM_SWAPPING)
                     vmCancelThreadedIOJob(val);
-                /* Update the access time of the key for the aging algorithm. */
+                /* Update the access time for the aging algorithm. */
                 val->lru = server.lruclock;
             } else {
                 int notify = (val->storage == REDIS_VM_LOADING);
@@ -3413,17 +3432,72 @@ static robj *lookupKeyWriteOrReply(redisClient *c, robj *key, robj *reply) {
     return o;
 }
 
-static int deleteKey(redisDb *db, robj *key) {
+/* Add the key to the DB. If the key already exists REDIS_ERR is returned,
+ * otherwise REDIS_OK is returned, and the caller should increment the
+ * refcount of 'val'. */
+static int dbAdd(redisDb *db, robj *key, robj *val) {
+    /* Perform a lookup before adding the key, as we need to copy the
+     * key value. */
+    if (dictFind(db->dict, key->ptr) != NULL) {
+        return REDIS_ERR;
+    } else {
+        sds copy = sdsdup(key->ptr);
+        dictAdd(db->dict, copy, val);
+        return REDIS_OK;
+    }
+}
+
+/* If the key does not exist, this is just like dbAdd(). Otherwise
+ * the value associated to the key is replaced with the new one.
+ *
+ * On update (key already existed) 0 is returned. Otherwise 1. */
+static int dbReplace(redisDb *db, robj *key, robj *val) {
+    if (dictFind(db->dict,key->ptr) == NULL) {
+        sds copy = sdsdup(key->ptr);
+        dictAdd(db->dict, copy, val);
+        return 1;
+    } else {
+        dictReplace(db->dict, key->ptr, val);
+        return 0;
+    }
+}
+
+static int dbExists(redisDb *db, robj *key) {
+    return dictFind(db->dict,key->ptr) != NULL;
+}
+
+/* Return a random key, in form of a Redis object.
+ * If there are no keys, NULL is returned.
+ *
+ * The function makes sure to return keys not already expired. */
+static robj *dbRandomKey(redisDb *db) {
+    struct dictEntry *de;
+
+    while(1) {
+        sds key;
+        robj *keyobj;
+
+        de = dictGetRandomKey(db->dict);
+        if (de == NULL) return NULL;
+
+        key = dictGetEntryKey(de);
+        keyobj = createStringObject(key,sdslen(key));
+        if (dictFind(db->expires,key)) {
+            if (expireIfNeeded(db,keyobj)) {
+                decrRefCount(keyobj);
+                continue; /* search for another key. This expired. */
+            }
+        }
+        return keyobj;
+    }
+}
+
+/* Delete a key, value, and associated expiration entry if any, from the DB */
+static int dbDelete(redisDb *db, robj *key) {
     int retval;
 
-    /* We need to protect key from destruction: after the first dictDelete()
-     * it may happen that 'key' is no longer valid if we don't increment
-     * it's count. This may happen when we get the object reference directly
-     * from the hash table with dictRandomKey() or dict iterators */
-    incrRefCount(key);
-    if (dictSize(db->expires)) dictDelete(db->expires,key);
-    retval = dictDelete(db->dict,key);
-    decrRefCount(key);
+    if (dictSize(db->expires)) dictDelete(db->expires,key->ptr);
+    retval = dictDelete(db->dict,key->ptr);
 
     return retval == DICT_OK;
 }
@@ -3782,9 +3856,12 @@ static int rdbSave(char *filename) {
 
         /* Iterate this DB writing every entry */
         while((de = dictNext(di)) != NULL) {
-            robj *key = dictGetEntryKey(de);
-            robj *o = dictGetEntryVal(de);
-            time_t expiretime = getExpire(db,key);
+            sds keystr = dictGetEntryKey(de);
+            robj key, *o = dictGetEntryVal(de);
+            time_t expiretime;
+            
+            initStaticStringObject(key,keystr);
+            expiretime = getExpire(db,&key);
 
             /* Save the expire time */
             if (expiretime != -1) {
@@ -3799,7 +3876,7 @@ static int rdbSave(char *filename) {
                                       o->storage == REDIS_VM_SWAPPING) {
                 /* Save type, key, value */
                 if (rdbSaveType(fp,o->type) == -1) goto werr;
-                if (rdbSaveStringObject(fp,key) == -1) goto werr;
+                if (rdbSaveStringObject(fp,&key) == -1) goto werr;
                 if (rdbSaveObject(fp,o) == -1) goto werr;
             } else {
                 /* REDIS_VM_SWAPPED or REDIS_VM_LOADING */
@@ -3808,7 +3885,7 @@ static int rdbSave(char *filename) {
                 po = vmPreviewObject(o);
                 /* Save type, key, value */
                 if (rdbSaveType(fp,po->type) == -1) goto werr;
-                if (rdbSaveStringObject(fp,key) == -1) goto werr;
+                if (rdbSaveStringObject(fp,&key) == -1) goto werr;
                 if (rdbSaveObject(fp,po) == -1) goto werr;
                 /* Remove the loaded object from memory */
                 decrRefCount(po);
@@ -4128,7 +4205,6 @@ static int rdbLoad(char *filename) {
     uint32_t dbid;
     int type, retval, rdbver;
     int swap_all_values = 0;
-    dict *d = server.db[0].dict;
     redisDb *db = server.db+0;
     char buf[1024];
     time_t expiretime, now = time(NULL);
@@ -4170,7 +4246,6 @@ static int rdbLoad(char *filename) {
                 exit(1);
             }
             db = server.db+dbid;
-            d = db->dict;
             continue;
         }
         /* Read key */
@@ -4184,8 +4259,8 @@ static int rdbLoad(char *filename) {
             continue;
         }
         /* Add the new object in the hash table */
-        retval = dictAdd(d,key,val);
-        if (retval == DICT_ERR) {
+        retval = dbAdd(db,key,val);
+        if (retval == REDIS_ERR) {
             redisLog(REDIS_WARNING,"Loading DB, duplicated key (%s) found! Unrecoverable error, exiting now.", key->ptr);
             exit(1);
         }
@@ -4200,20 +4275,21 @@ static int rdbLoad(char *filename) {
          * to random sampling, otherwise we may try to swap already
          * swapped keys. */
         if (swap_all_values) {
-            dictEntry *de = dictFind(d,key);
+            dictEntry *de = dictFind(db->dict,key->ptr);
 
             /* de may be NULL since the key already expired */
             if (de) {
                 vmpointer *vp;
-                key = dictGetEntryKey(de);
                 val = dictGetEntryVal(de);
 
                 if (val->refcount == 1 &&
                     (vp = vmSwapObjectBlocking(val)) != NULL)
                     dictGetEntryVal(de) = vp;
             }
+            decrRefCount(key);
             continue;
         }
+        decrRefCount(key);
 
         /* Flush data on disk once 32 MB of additional RAM are used... */
         force_swapout = 0;
@@ -4311,23 +4387,16 @@ static void setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj
 
     touchWatchedKey(c->db,key);
     if (nx) deleteIfVolatile(c->db,key);
-    retval = dictAdd(c->db->dict,key,val);
-    if (retval == DICT_ERR) {
+    retval = dbAdd(c->db,key,val);
+    if (retval == REDIS_ERR) {
         if (!nx) {
-            /* If the key is about a swapped value, we want a new key object
-             * to overwrite the old. So we delete the old key in the database.
-             * This will also make sure that swap pages about the old object
-             * will be marked as free. */
-            if (server.vm_enabled && deleteIfSwapped(c->db,key))
-                incrRefCount(key);
-            dictReplace(c->db->dict,key,val);
+            dbReplace(c->db,key,val);
             incrRefCount(val);
         } else {
             addReply(c,shared.czero);
             return;
         }
     } else {
-        incrRefCount(key);
         incrRefCount(val);
     }
     server.dirty++;
@@ -4369,11 +4438,7 @@ static void getCommand(redisClient *c) {
 
 static void getsetCommand(redisClient *c) {
     if (getGenericCommand(c) == REDIS_ERR) return;
-    if (dictAdd(c->db->dict,c->argv[1],c->argv[2]) == DICT_ERR) {
-        dictReplace(c->db->dict,c->argv[1],c->argv[2]);
-    } else {
-        incrRefCount(c->argv[1]);
-    }
+    dbReplace(c->db,c->argv[1],c->argv[2]);
     incrRefCount(c->argv[2]);
     server.dirty++;
     removeExpire(c->db,c->argv[1]);
@@ -4419,17 +4484,9 @@ static void msetGenericCommand(redisClient *c, int nx) {
     }
 
     for (j = 1; j < c->argc; j += 2) {
-        int retval;
-
         c->argv[j+1] = tryObjectEncoding(c->argv[j+1]);
-        retval = dictAdd(c->db->dict,c->argv[j],c->argv[j+1]);
-        if (retval == DICT_ERR) {
-            dictReplace(c->db->dict,c->argv[j],c->argv[j+1]);
-            incrRefCount(c->argv[j+1]);
-        } else {
-            incrRefCount(c->argv[j]);
-            incrRefCount(c->argv[j+1]);
-        }
+        dbReplace(c->db,c->argv[j],c->argv[j+1]);
+        incrRefCount(c->argv[j+1]);
         removeExpire(c->db,c->argv[j]);
     }
     server.dirty += (c->argc-1)/2;
@@ -4446,7 +4503,6 @@ static void msetnxCommand(redisClient *c) {
 
 static void incrDecrCommand(redisClient *c, long long incr) {
     long long value;
-    int retval;
     robj *o;
 
     o = lookupKeyWrite(c->db,c->argv[1]);
@@ -4455,13 +4511,7 @@ static void incrDecrCommand(redisClient *c, long long incr) {
 
     value += incr;
     o = createStringObjectFromLongLong(value);
-    retval = dictAdd(c->db->dict,c->argv[1],o);
-    if (retval == DICT_ERR) {
-        dictReplace(c->db->dict,c->argv[1],o);
-        removeExpire(c->db,c->argv[1]);
-    } else {
-        incrRefCount(c->argv[1]);
-    }
+    dbReplace(c->db,c->argv[1],o);
     server.dirty++;
     addReply(c,shared.colon);
     addReply(c,o);
@@ -4498,17 +4548,10 @@ static void appendCommand(redisClient *c) {
     o = lookupKeyWrite(c->db,c->argv[1]);
     if (o == NULL) {
         /* Create the key */
-        retval = dictAdd(c->db->dict,c->argv[1],c->argv[2]);
-        incrRefCount(c->argv[1]);
+        retval = dbAdd(c->db,c->argv[1],c->argv[2]);
         incrRefCount(c->argv[2]);
         totlen = stringObjectLen(c->argv[2]);
     } else {
-        dictEntry *de;
-
-        de = dictFind(c->db->dict,c->argv[1]);
-        assert(de != NULL);
-
-        o = dictGetEntryVal(de);
         if (o->type != REDIS_STRING) {
             addReply(c,shared.wrongtypeerr);
             return;
@@ -4520,7 +4563,7 @@ static void appendCommand(redisClient *c) {
 
             o = createStringObject(decoded->ptr, sdslen(decoded->ptr));
             decrRefCount(decoded);
-            dictReplace(c->db->dict,c->argv[1],o);
+            dbReplace(c->db,c->argv[1],o);
         }
         /* APPEND! */
         if (c->argv[2]->encoding == REDIS_ENCODING_RAW) {
@@ -4579,7 +4622,7 @@ static void delCommand(redisClient *c) {
     int deleted = 0, j;
 
     for (j = 1; j < c->argc; j++) {
-        if (deleteKey(c->db,c->argv[j])) {
+        if (dbDelete(c->db,c->argv[j])) {
             touchWatchedKey(c->db,c->argv[j]);
             server.dirty++;
             deleted++;
@@ -4590,7 +4633,7 @@ static void delCommand(redisClient *c) {
 
 static void existsCommand(redisClient *c) {
     expireIfNeeded(c->db,c->argv[1]);
-    if (dictFind(c->db->dict,c->argv[1])) {
+    if (dbExists(c->db,c->argv[1])) {
         addReply(c, shared.cone);
     } else {
         addReply(c, shared.czero);
@@ -4608,27 +4651,15 @@ static void selectCommand(redisClient *c) {
 }
 
 static void randomkeyCommand(redisClient *c) {
-    dictEntry *de;
     robj *key;
 
-    while(1) {
-        de = dictGetRandomKey(c->db->dict);
-        if (!de || expireIfNeeded(c->db,dictGetEntryKey(de)) == 0) break;
-    }
-
-    if (de == NULL) {
+    if ((key = dbRandomKey(c->db)) == NULL) {
         addReply(c,shared.nullbulk);
         return;
     }
 
-    key = dictGetEntryKey(de);
-    if (server.vm_enabled) {
-        key = dupStringObject(key);
-        addReplyBulk(c,key);
-        decrRefCount(key);
-    } else {
-        addReplyBulk(c,key);
-    }
+    addReplyBulk(c,key);
+    decrRefCount(key);
 }
 
 static void keysCommand(redisClient *c) {
@@ -4643,15 +4674,17 @@ static void keysCommand(redisClient *c) {
     addReply(c,lenobj);
     decrRefCount(lenobj);
     while((de = dictNext(di)) != NULL) {
-        robj *keyobj = dictGetEntryKey(de);
+        sds key = dictGetEntryKey(de);
+        robj *keyobj;
 
-        sds key = keyobj->ptr;
         if ((pattern[0] == '*' && pattern[1] == '\0') ||
             stringmatchlen(pattern,plen,key,sdslen(key),0)) {
+            keyobj = createStringObject(key,sdslen(key));
             if (expireIfNeeded(c->db,keyobj) == 0) {
                 addReplyBulk(c,keyobj);
                 numkeys++;
             }
+            decrRefCount(keyobj);
         }
     }
     dictReleaseIterator(di);
@@ -4734,17 +4767,15 @@ static void renameGenericCommand(redisClient *c, int nx) {
 
     incrRefCount(o);
     deleteIfVolatile(c->db,c->argv[2]);
-    if (dictAdd(c->db->dict,c->argv[2],o) == DICT_ERR) {
+    if (dbAdd(c->db,c->argv[2],o) == REDIS_ERR) {
         if (nx) {
             decrRefCount(o);
             addReply(c,shared.czero);
             return;
         }
-        dictReplace(c->db->dict,c->argv[2],o);
-    } else {
-        incrRefCount(c->argv[2]);
+        dbReplace(c->db,c->argv[2],o);
     }
-    deleteKey(c->db,c->argv[1]);
+    dbDelete(c->db,c->argv[1]);
     touchWatchedKey(c->db,c->argv[2]);
     server.dirty++;
     addReply(c,nx ? shared.cone : shared.ok);
@@ -4789,15 +4820,14 @@ static void moveCommand(redisClient *c) {
 
     /* Try to add the element to the target DB */
     deleteIfVolatile(dst,c->argv[1]);
-    if (dictAdd(dst->dict,c->argv[1],o) == DICT_ERR) {
+    if (dbAdd(dst,c->argv[1],o) == REDIS_ERR) {
         addReply(c,shared.czero);
         return;
     }
-    incrRefCount(c->argv[1]);
     incrRefCount(o);
 
     /* OK! key moved, free the entry in the source DB */
-    deleteKey(src,c->argv[1]);
+    dbDelete(src,c->argv[1]);
     server.dirty++;
     addReply(c,shared.cone);
 }
@@ -4820,9 +4850,8 @@ static void pushGenericCommand(redisClient *c, int where) {
         } else {
             listAddNodeTail(list,c->argv[2]);
         }
-        dictAdd(c->db->dict,c->argv[1],lobj);
-        incrRefCount(c->argv[1]);
         incrRefCount(c->argv[2]);
+        dbAdd(c->db,c->argv[1],lobj);
     } else {
         if (lobj->type != REDIS_LIST) {
             addReply(c,shared.wrongtypeerr);
@@ -4926,7 +4955,7 @@ static void popGenericCommand(redisClient *c, int where) {
         robj *ele = listNodeValue(ln);
         addReplyBulk(c,ele);
         listDelNode(list,ln);
-        if (listLength(list) == 0) deleteKey(c->db,c->argv[1]);
+        if (listLength(list) == 0) dbDelete(c->db,c->argv[1]);
         server.dirty++;
     }
 }
@@ -5019,7 +5048,7 @@ static void ltrimCommand(redisClient *c) {
         ln = listLast(list);
         listDelNode(list,ln);
     }
-    if (listLength(list) == 0) deleteKey(c->db,c->argv[1]);
+    if (listLength(list) == 0) dbDelete(c->db,c->argv[1]);
     server.dirty++;
     addReply(c,shared.ok);
 }
@@ -5053,7 +5082,7 @@ static void lremCommand(redisClient *c) {
         }
         ln = next;
     }
-    if (listLength(list) == 0) deleteKey(c->db,c->argv[1]);
+    if (listLength(list) == 0) dbDelete(c->db,c->argv[1]);
     addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",removed));
 }
 
@@ -5100,8 +5129,7 @@ static void rpoplpushcommand(redisClient *c) {
             if (dobj == NULL) {
                 /* Create the list if the key does not exist */
                 dobj = createListObject();
-                dictAdd(c->db->dict,c->argv[2],dobj);
-                incrRefCount(c->argv[2]);
+                dbAdd(c->db,c->argv[2],dobj);
             }
             dstlist = dobj->ptr;
             listAddNodeHead(dstlist,ele);
@@ -5113,7 +5141,7 @@ static void rpoplpushcommand(redisClient *c) {
 
         /* Finally remove the element from the source list */
         listDelNode(srclist,ln);
-        if (listLength(srclist) == 0) deleteKey(c->db,c->argv[1]);
+        if (listLength(srclist) == 0) dbDelete(c->db,c->argv[1]);
         server.dirty++;
     }
 }
@@ -5126,8 +5154,7 @@ static void saddCommand(redisClient *c) {
     set = lookupKeyWrite(c->db,c->argv[1]);
     if (set == NULL) {
         set = createSetObject();
-        dictAdd(c->db->dict,c->argv[1],set);
-        incrRefCount(c->argv[1]);
+        dbAdd(c->db,c->argv[1],set);
     } else {
         if (set->type != REDIS_SET) {
             addReply(c,shared.wrongtypeerr);
@@ -5152,7 +5179,7 @@ static void sremCommand(redisClient *c) {
     if (dictDelete(set->ptr,c->argv[2]) == DICT_OK) {
         server.dirty++;
         if (htNeedsResize(set->ptr)) dictResize(set->ptr);
-        if (dictSize((dict*)set->ptr) == 0) deleteKey(c->db,c->argv[1]);
+        if (dictSize((dict*)set->ptr) == 0) dbDelete(c->db,c->argv[1]);
         addReply(c,shared.cone);
     } else {
         addReply(c,shared.czero);
@@ -5183,13 +5210,12 @@ static void smoveCommand(redisClient *c) {
         return;
     }
     if (dictSize((dict*)srcset->ptr) == 0 && srcset != dstset)
-        deleteKey(c->db,c->argv[1]);
+        dbDelete(c->db,c->argv[1]);
     server.dirty++;
     /* Add the element to the destination set */
     if (!dstset) {
         dstset = createSetObject();
-        dictAdd(c->db->dict,c->argv[2],dstset);
-        incrRefCount(c->argv[2]);
+        dbAdd(c->db,c->argv[2],dstset);
     }
     if (dictAdd(dstset->ptr,c->argv[3],NULL) == DICT_OK)
         incrRefCount(c->argv[3]);
@@ -5235,7 +5261,7 @@ static void spopCommand(redisClient *c) {
         addReplyBulk(c,ele);
         dictDelete(set->ptr,ele);
         if (htNeedsResize(set->ptr)) dictResize(set->ptr);
-        if (dictSize((dict*)set->ptr) == 0) deleteKey(c->db,c->argv[1]);
+        if (dictSize((dict*)set->ptr) == 0) dbDelete(c->db,c->argv[1]);
         server.dirty++;
     }
 }
@@ -5279,7 +5305,7 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, unsigned long
         if (!setobj) {
             zfree(dv);
             if (dstkey) {
-                if (deleteKey(c->db,dstkey))
+                if (dbDelete(c->db,dstkey))
                     server.dirty++;
                 addReply(c,shared.czero);
             } else {
@@ -5339,10 +5365,9 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, unsigned long
     if (dstkey) {
         /* Store the resulting set into the target, if the intersection
          * is not an empty set. */
-        deleteKey(c->db,dstkey);
+        dbDelete(c->db,dstkey);
         if (dictSize((dict*)dstset->ptr) > 0) {
-            dictAdd(c->db->dict,dstkey,dstset);
-            incrRefCount(dstkey);
+            dbAdd(c->db,dstkey,dstset);
             addReplyLongLong(c,dictSize((dict*)dstset->ptr));
         } else {
             decrRefCount(dstset);
@@ -5442,10 +5467,9 @@ static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnu
     } else {
         /* If we have a target key where to store the resulting set
          * create this key with the result set inside */
-        deleteKey(c->db,dstkey);
+        dbDelete(c->db,dstkey);
         if (dictSize((dict*)dstset->ptr) > 0) {
-            dictAdd(c->db->dict,dstkey,dstset);
-            incrRefCount(dstkey);
+            dbAdd(c->db,dstkey,dstset);
             addReplyLongLong(c,dictSize((dict*)dstset->ptr));
         } else {
             decrRefCount(dstset);
@@ -5801,8 +5825,7 @@ static void zaddGenericCommand(redisClient *c, robj *key, robj *ele, double scor
     zsetobj = lookupKeyWrite(c->db,key);
     if (zsetobj == NULL) {
         zsetobj = createZsetObject();
-        dictAdd(c->db->dict,key,zsetobj);
-        incrRefCount(key);
+        dbAdd(c->db,key,zsetobj);
     } else {
         if (zsetobj->type != REDIS_ZSET) {
             addReply(c,shared.wrongtypeerr);
@@ -5918,7 +5941,7 @@ static void zremCommand(redisClient *c) {
     /* Delete from the hash table */
     dictDelete(zs->dict,c->argv[2]);
     if (htNeedsResize(zs->dict)) dictResize(zs->dict);
-    if (dictSize(zs->dict) == 0) deleteKey(c->db,c->argv[1]);
+    if (dictSize(zs->dict) == 0) dbDelete(c->db,c->argv[1]);
     server.dirty++;
     addReply(c,shared.cone);
 }
@@ -5939,7 +5962,7 @@ static void zremrangebyscoreCommand(redisClient *c) {
     zs = zsetobj->ptr;
     deleted = zslDeleteRangeByScore(zs->zsl,min,max,zs->dict);
     if (htNeedsResize(zs->dict)) dictResize(zs->dict);
-    if (dictSize(zs->dict) == 0) deleteKey(c->db,c->argv[1]);
+    if (dictSize(zs->dict) == 0) dbDelete(c->db,c->argv[1]);
     server.dirty += deleted;
     addReplyLongLong(c,deleted);
 }
@@ -5977,7 +6000,7 @@ static void zremrangebyrankCommand(redisClient *c) {
      * use 1-based rank */
     deleted = zslDeleteRangeByRank(zs->zsl,start+1,end+1,zs->dict);
     if (htNeedsResize(zs->dict)) dictResize(zs->dict);
-    if (dictSize(zs->dict) == 0) deleteKey(c->db,c->argv[1]);
+    if (dictSize(zs->dict) == 0) dbDelete(c->db,c->argv[1]);
     server.dirty += deleted;
     addReplyLongLong(c, deleted);
 }
@@ -6165,10 +6188,9 @@ static void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
         redisAssert(op == REDIS_OP_INTER || op == REDIS_OP_UNION);
     }
 
-    deleteKey(c->db,dstkey);
+    dbDelete(c->db,dstkey);
     if (dstzset->zsl->length) {
-        dictAdd(c->db->dict,dstkey,dstobj);
-        incrRefCount(dstkey);
+        dbAdd(c->db,dstkey,dstobj);
         addReplyLongLong(c, dstzset->zsl->length);
         server.dirty++;
     } else {
@@ -6644,8 +6666,7 @@ static robj *hashLookupWriteOrCreate(redisClient *c, robj *key) {
     robj *o = lookupKeyWrite(c->db,key);
     if (o == NULL) {
         o = createHashObject();
-        dictAdd(c->db->dict,key,o);
-        incrRefCount(key);
+        dbAdd(c->db,key,o);
     } else {
         if (o->type != REDIS_HASH) {
             addReply(c,shared.wrongtypeerr);
@@ -6769,7 +6790,7 @@ static void hdelCommand(redisClient *c) {
         checkType(c,o,REDIS_HASH)) return;
 
     if (hashDelete(o,c->argv[2])) {
-        if (hashLength(o) == 0) deleteKey(c->db,c->argv[1]);
+        if (hashLength(o) == 0) dbDelete(c->db,c->argv[1]);
         addReply(c,shared.cone);
         server.dirty++;
     } else {
@@ -7243,9 +7264,7 @@ static void sortCommand(redisClient *c) {
                 }
             }
         }
-        if (dictReplace(c->db->dict,storekey,listObject)) {
-            incrRefCount(storekey);
-        }
+        dbReplace(c->db,storekey,listObject);
         /* Note: we add 1 because the DB is dirty anyway since even if the
          * SORT result is empty a new key is set and maybe the old content
          * replaced. */
@@ -7424,18 +7443,19 @@ static void monitorCommand(redisClient *c) {
 
 /* ================================= Expire ================================= */
 static int removeExpire(redisDb *db, robj *key) {
-    if (dictDelete(db->expires,key) == DICT_OK) {
+    if (dictDelete(db->expires,key->ptr) == DICT_OK) {
         return 1;
     } else {
         return 0;
     }
 }
 
 static int setExpire(redisDb *db, robj *key, time_t when) {
-    if (dictAdd(db->expires,key,(void*)when) == DICT_ERR) {
+    sds copy = sdsdup(key->ptr);
+    if (dictAdd(db->expires,copy,(void*)when) == DICT_ERR) {
+        sdsfree(copy);
         return 0;
     } else {
-        incrRefCount(key);
         return 1;
     }
 }
@@ -7447,7 +7467,7 @@ static time_t getExpire(redisDb *db, robj *key) {
 
     /* No expire? return ASAP */
     if (dictSize(db->expires) == 0 ||
-       (de = dictFind(db->expires,key)) == NULL) return -1;
+       (de = dictFind(db->expires,key->ptr)) == NULL) return -1;
 
     return (time_t) dictGetEntryVal(de);
 }
@@ -7458,30 +7478,30 @@ static int expireIfNeeded(redisDb *db, robj *key) {
 
     /* No expire? return ASAP */
     if (dictSize(db->expires) == 0 ||
-       (de = dictFind(db->expires,key)) == NULL) return 0;
+       (de = dictFind(db->expires,key->ptr)) == NULL) return 0;
 
     /* Lookup the expire */
     when = (time_t) dictGetEntryVal(de);
     if (time(NULL) <= when) return 0;
 
     /* Delete the key */
-    dictDelete(db->expires,key);
+    dbDelete(db,key);
     server.stat_expiredkeys++;
-    return dictDelete(db->dict,key) == DICT_OK;
+    return 1;
 }
 
 static int deleteIfVolatile(redisDb *db, robj *key) {
     dictEntry *de;
 
     /* No expire? return ASAP */
     if (dictSize(db->expires) == 0 ||
-       (de = dictFind(db->expires,key)) == NULL) return 0;
+       (de = dictFind(db->expires,key->ptr)) == NULL) return 0;
 
     /* Delete the key */
     server.dirty++;
     server.stat_expiredkeys++;
-    dictDelete(db->expires,key);
-    return dictDelete(db->dict,key) == DICT_OK;
+    dictDelete(db->expires,key->ptr);
+    return dictDelete(db->dict,key->ptr) == DICT_OK;
 }
 
 static void expireGenericCommand(redisClient *c, robj *key, robj *param, long offset) {
@@ -7492,13 +7512,13 @@ static void expireGenericCommand(redisClient *c, robj *key, robj *param, long of
 
     seconds -= offset;
 
-    de = dictFind(c->db->dict,key);
+    de = dictFind(c->db->dict,key->ptr);
     if (de == NULL) {
         addReply(c,shared.czero);
         return;
     }
     if (seconds <= 0) {
-        if (deleteKey(c->db,key)) server.dirty++;
+        if (dbDelete(c->db,key)) server.dirty++;
         addReply(c, shared.cone);
         return;
     } else {
@@ -8267,7 +8287,7 @@ static void freeMemoryIfNeeded(void) {
                         minttl = t;
                     }
                 }
-                deleteKey(server.db+j,minkey);
+                dbDelete(server.db+j,minkey);
             }
         }
         if (!freed) return; /* nothing to free... */
@@ -8672,12 +8692,14 @@ static int rewriteAppendOnlyFile(char *filename) {
 
         /* Iterate this DB writing every entry */
         while((de = dictNext(di)) != NULL) {
-            robj *key, *o;
+            sds keystr = dictGetEntryKey(de);
+            robj key, *o;
             time_t expiretime;
             int swapped;
 
-            key = dictGetEntryKey(de);
+            keystr = dictGetEntryKey(de);
             o = dictGetEntryVal(de);
+            initStaticStringObject(key,keystr);
             /* If the value for this key is swapped, load a preview in memory.
              * We use a "swapped" flag to remember if we need to free the
              * value object instead to just increment the ref count anyway
@@ -8689,15 +8711,15 @@ static int rewriteAppendOnlyFile(char *filename) {
                 o = vmPreviewObject(o);
                 swapped = 1;
             }
-            expiretime = getExpire(db,key);
+            expiretime = getExpire(db,&key);
 
             /* Save the key and associated value */
             if (o->type == REDIS_STRING) {
                 /* Emit a SET command */
                 char cmd[]="*3\r\n$3\r\nSET\r\n";
                 if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
                 /* Key and value */
-                if (fwriteBulkObject(fp,key) == 0) goto werr;
+                if (fwriteBulkObject(fp,&key) == 0) goto werr;
                 if (fwriteBulkObject(fp,o) == 0) goto werr;
             } else if (o->type == REDIS_LIST) {
                 /* Emit the RPUSHes needed to rebuild the list */
@@ -8711,7 +8733,7 @@ static int rewriteAppendOnlyFile(char *filename) {
                     robj *eleobj = listNodeValue(ln);
 
                     if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                    if (fwriteBulkObject(fp,key) == 0) goto werr;
+                    if (fwriteBulkObject(fp,&key) == 0) goto werr;
                     if (fwriteBulkObject(fp,eleobj) == 0) goto werr;
                 }
             } else if (o->type == REDIS_SET) {
@@ -8725,7 +8747,7 @@ static int rewriteAppendOnlyFile(char *filename) {
                     robj *eleobj = dictGetEntryKey(de);
 
                     if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                    if (fwriteBulkObject(fp,key) == 0) goto werr;
+                    if (fwriteBulkObject(fp,&key) == 0) goto werr;
                     if (fwriteBulkObject(fp,eleobj) == 0) goto werr;
                 }
                 dictReleaseIterator(di);
@@ -8741,7 +8763,7 @@ static int rewriteAppendOnlyFile(char *filename) {
                     double *score = dictGetEntryVal(de);
 
                     if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                    if (fwriteBulkObject(fp,key) == 0) goto werr;
+                    if (fwriteBulkObject(fp,&key) == 0) goto werr;
                     if (fwriteBulkDouble(fp,*score) == 0) goto werr;
                     if (fwriteBulkObject(fp,eleobj) == 0) goto werr;
                 }
@@ -8757,7 +8779,7 @@ static int rewriteAppendOnlyFile(char *filename) {
 
                     while((p = zipmapNext(p,&field,&flen,&val,&vlen)) != NULL) {
                         if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                        if (fwriteBulkObject(fp,key) == 0) goto werr;
+                        if (fwriteBulkObject(fp,&key) == 0) goto werr;
                         if (fwriteBulkString(fp,(char*)field,flen) == -1)
                             return -1;
                         if (fwriteBulkString(fp,(char*)val,vlen) == -1)
@@ -8772,7 +8794,7 @@ static int rewriteAppendOnlyFile(char *filename) {
                         robj *val = dictGetEntryVal(de);
 
                         if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                        if (fwriteBulkObject(fp,key) == 0) goto werr;
+                        if (fwriteBulkObject(fp,&key) == 0) goto werr;
                         if (fwriteBulkObject(fp,field) == -1) return -1;
                         if (fwriteBulkObject(fp,val) == -1) return -1;
                     }
@@ -8787,7 +8809,7 @@ static int rewriteAppendOnlyFile(char *filename) {
                 /* If this key is already expired skip it */
                 if (expiretime < now) continue;
                 if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                if (fwriteBulkObject(fp,key) == 0) goto werr;
+                if (fwriteBulkObject(fp,&key) == 0) goto werr;
                 if (fwriteBulkLong(fp,expiretime) == 0) goto werr;
             }
             if (swapped) decrRefCount(o);
@@ -9410,17 +9432,6 @@ static int vmCanSwapOut(void) {
     return (server.bgsavechildpid == -1 && server.bgrewritechildpid == -1);
 }
 
-/* Delete a key if swapped. Returns 1 if the key was found, was swapped
- * and was deleted. Otherwise 0 is returned. */
-static int deleteIfSwapped(redisDb *db, robj *key) {
-    robj *val;
-
-    if ((val = dictFetchValue(db->dict,key)) == NULL) return 0;
-    if (val->storage == REDIS_VM_MEMORY) return 0;
-    deleteKey(db,key);
-    return 1;
-}
-
 /* =================== Virtual Memory - Threaded I/O  ======================= */
 
 static void freeIOJob(iojob *j) {
@@ -9826,7 +9837,7 @@ static int waitForSwappedKey(redisClient *c, robj *key) {
 
     /* If the key does not exist or is already in RAM we don't need to
      * block the client at all. */
-    de = dictFind(c->db->dict,key);
+    de = dictFind(c->db->dict,key->ptr);
     if (de == NULL) return 0;
     o = dictGetEntryVal(de);
     if (o->storage == REDIS_VM_MEMORY) {
@@ -10616,7 +10627,7 @@ static void touchWatchedKeysOnFlush(int dbid) {
              * key exists, mark the client as dirty, as the key will be
              * removed. */
             if (dbid == -1 || wk->db->id == dbid) {
-                if (dictFind(wk->db->dict, wk->key) != NULL)
+                if (dictFind(wk->db->dict, wk->key->ptr) != NULL)
                     c->flags |= REDIS_DIRTY_CAS;
             }
         }
@@ -10727,27 +10738,22 @@ static void computeDatasetDigest(unsigned char *final) {
 
         /* Iterate this DB writing every entry */
         while((de = dictNext(di)) != NULL) {
-            robj *key, *o, *kcopy;
+            sds key;
+            robj *keyobj, *o;
             time_t expiretime;
 
             memset(digest,0,20); /* This key-val digest */
             key = dictGetEntryKey(de);
+            keyobj = createStringObject(key,sdslen(key));
+
+            mixDigest(digest,key,sdslen(key));
+
+            /* Make sure the key is loaded if VM is active */
+            o = lookupKeyRead(db,keyobj);
 
-            if (!server.vm_enabled) {
-                mixObjectDigest(digest,key);
-                o = dictGetEntryVal(de);
-            } else {
-                /* Don't work with the key directly as when VM is active
-                 * this is unsafe: TODO: fix decrRefCount to check if the
-                 * count really reached 0 to avoid this mess */
-                kcopy = dupStringObject(key);
-                mixObjectDigest(digest,kcopy);
-                o = lookupKeyRead(db,kcopy);
-                decrRefCount(kcopy);
-            }
             aux = htonl(o->type);
             mixDigest(digest,&aux,sizeof(aux));
-            expiretime = getExpire(db,key);
+            expiretime = getExpire(db,keyobj);
 
             /* Save the key and associated value */
             if (o->type == REDIS_STRING) {
@@ -10816,6 +10822,7 @@ static void computeDatasetDigest(unsigned char *final) {
             if (expiretime != -1) xorDigest(digest,"!!expire!!",10);
             /* We can finally xor the key-val digest to the final digest */
             xorDigest(final,digest,20);
+            decrRefCount(keyobj);
         }
         dictReleaseIterator(di);
     }
@@ -10845,14 +10852,13 @@ static void debugCommand(redisClient *c) {
         redisLog(REDIS_WARNING,"Append Only File loaded by DEBUG LOADAOF");
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"object") && c->argc == 3) {
-        dictEntry *de = dictFind(c->db->dict,c->argv[2]);
-        robj *key, *val;
+        dictEntry *de = dictFind(c->db->dict,c->argv[2]->ptr);
+        robj *val;
 
         if (!de) {
             addReply(c,shared.nokeyerr);
             return;
         }
-        key = dictGetEntryKey(de);
         val = dictGetEntryVal(de);
         if (!server.vm_enabled || (val->storage == REDIS_VM_MEMORY ||
                                    val->storage == REDIS_VM_SWAPPING)) {
@@ -10866,24 +10872,24 @@ static void debugCommand(redisClient *c) {
                 strenc = buf;
             }
             addReplySds(c,sdscatprintf(sdsempty(),
-                "+Key at:%p refcount:%d, value at:%p refcount:%d "
+                "+Value at:%p refcount:%d "
                 "encoding:%s serializedlength:%lld\r\n",
-                (void*)key, key->refcount, (void*)val, val->refcount,
+                (void*)val, val->refcount,
                 strenc, (long long) rdbSavedObjectLen(val,NULL)));
         } else {
             vmpointer *vp = (vmpointer*) val;
             addReplySds(c,sdscatprintf(sdsempty(),
-                "+Key at:%p refcount:%d, value swapped at: page %llu "
+                "+Value swapped at: page %llu "
                 "using %llu pages\r\n",
-                (void*)key, key->refcount, (unsigned long long) vp->page,
+                (unsigned long long) vp->page,
                 (unsigned long long) vp->usedpages));
         }
     } else if (!strcasecmp(c->argv[1]->ptr,"swapin") && c->argc == 3) {
         lookupKeyRead(c->db,c->argv[2]);
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"swapout") && c->argc == 3) {
-        dictEntry *de = dictFind(c->db->dict,c->argv[2]);
-        robj *key, *val;
+        dictEntry *de = dictFind(c->db->dict,c->argv[2]->ptr);
+        robj *val;
         vmpointer *vp;
 
         if (!server.vm_enabled) {
@@ -10894,7 +10900,6 @@ static void debugCommand(redisClient *c) {
             addReply(c,shared.nokeyerr);
             return;
         }
-        key = dictGetEntryKey(de);
         val = dictGetEntryVal(de);
         /* Swap it */
         if (val->storage != REDIS_VM_MEMORY) {
@@ -10923,7 +10928,8 @@ static void debugCommand(redisClient *c) {
             }
             snprintf(buf,sizeof(buf),"value:%lu",j);
             val = createStringObject(buf,strlen(buf));
-            dictAdd(c->db->dict,key,val);
+            dbAdd(c->db,key,val);
+            decrRefCount(key);
         }
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"digest") && c->argc == 2) {