@@ -120,6 +120,7 @@
 #define REDIS_SET 2
 #define REDIS_ZSET 3
 #define REDIS_HASH 4
+#define REDIS_VMPOINTER 8
 
 /* Objects encoding. Some kind of objects like Strings and Hashes can be
  * internally represented in multiple ways. The 'encoding' field of the object
@@ -247,30 +248,41 @@ static void _redisPanic(char *msg, char *file, int line);
 
 /* A redis object, that is a type able to hold a string / list / set */
 
-/* The VM object structure */
-struct redisObjectVM {
-    off_t page;         /* the page at witch the object is stored on disk */
-    off_t usedpages;    /* number of pages used on disk */
-    time_t atime;       /* Last access time */
-} vm;
-
 /* The actual Redis Object */
 typedef struct redisObject {
-    void *ptr;
-    unsigned char type;
-    unsigned char encoding;
-    unsigned char storage;  /* If this object is a key, where is the value?
-                             * REDIS_VM_MEMORY, REDIS_VM_SWAPPED, ... */
-    unsigned char vtype; /* If this object is a key, and value is swapped out,
-                          * this is the type of the swapped out object. */
+    unsigned type:4;
+    unsigned storage:2;     /* REDIS_VM_MEMORY or REDIS_VM_SWAPPING */
+    unsigned encoding:4;
+    unsigned lru:22;        /* lru time (relative to server.lruclock) */
     int refcount;
+    void *ptr;
     /* VM fields, this are only allocated if VM is active, otherwise the
      * object allocation function will just allocate
      * sizeof(redisObjct) minus sizeof(redisObjectVM), so using
      * Redis without VM active will not have any overhead. */
-    struct redisObjectVM vm;
 } robj;
 
+/* The VM pointer structure - identifies an object in the swap file.
+ *
+ * This object is stored in place of the value
+ * object in the main key->value hash table representing a database.
+ * Note that the first fields (type, storage) are the same as the redisObject
+ * structure so that vmPointer strucuters can be accessed even when casted
+ * as redisObject structures.
+ *
+ * This is useful as we don't know if a value object is or not on disk, but we
+ * are always able to read obj->storage to check this. For vmPointer
+ * structures "type" is set to REDIS_VMPOINTER (even if without this field
+ * is still possible to check the kind of object from the value of 'storage').*/
+typedef struct vmPointer {
+    unsigned type:4;
+    unsigned storage:2; /* REDIS_VM_SWAPPED or REDIS_VM_LOADING */
+    unsigned notused:26;
+    unsigned int vtype; /* type of the object stored in the swap file */
+    off_t page;         /* the page at witch the object is stored on disk */
+    off_t usedpages;    /* number of pages used on disk */
+} vmpointer;
+
 /* Macro used to initalize a Redis object allocated on the stack.
  * Note that this macro is taken near the structure definition to make sure
  * we'll update it when the structure is changed, to avoid bugs like
@@ -280,7 +292,7 @@ typedef struct redisObject {
     _var.type = REDIS_STRING; \
     _var.encoding = REDIS_ENCODING_RAW; \
     _var.ptr = _ptr; \
-    if (server.vm_enabled) _var.storage = REDIS_VM_MEMORY; \
+    _var.storage = REDIS_VM_MEMORY; \
 } while(0);
 
 typedef struct redisDb {
@@ -450,6 +462,8 @@ struct redisServer {
     list *pubsub_patterns; /* A list of pubsub_patterns */
     /* Misc */
     FILE *devnull;
+    unsigned lruclock:22;        /* clock incrementing every minute, for LRU */
+    unsigned lruclock_padding:10;
 };
 
 typedef struct pubsubPattern {
@@ -542,6 +556,9 @@ typedef struct iojob {
     int type;   /* Request type, REDIS_IOJOB_* */
     redisDb *db;/* Redis database */
     robj *key;  /* This I/O request is about swapping this key */
+    robj *id;   /* Unique identifier of this job:
+                   this is the object to swap for REDIS_IOREQ_*_SWAP, or the
+                   vmpointer objct for REDIS_IOREQ_LOAD. */
     robj *val;  /* the value to swap for REDIS_IOREQ_*_SWAP, otherwise this
                  * field is populated by the I/O thread for REDIS_IOREQ_LOAD. */
     off_t page; /* Swap page where to read/write the object */
@@ -575,8 +592,7 @@ static robj *getDecodedObject(robj *o);
 static int removeExpire(redisDb *db, robj *key);
 static int expireIfNeeded(redisDb *db, robj *key);
 static int deleteIfVolatile(redisDb *db, robj *key);
-static int deleteIfSwapped(redisDb *db, robj *key);
-static int deleteKey(redisDb *db, robj *key);
+static int dbDelete(redisDb *db, robj *key);
 static time_t getExpire(redisDb *db, robj *key);
 static int setExpire(redisDb *db, robj *key, time_t when);
 static void updateSlavesWaitingBgsave(int bgsaveerr);
@@ -598,8 +614,8 @@ static void unblockClientWaitingData(redisClient *c);
 static int handleClientsWaitingListPush(redisClient *c, robj *key, robj *ele);
 static void vmInit(void);
 static void vmMarkPagesFree(off_t page, off_t count);
-static robj *vmLoadObject(robj *key);
-static robj *vmPreviewObject(robj *key);
+static robj *vmLoadObject(robj *o);
+static robj *vmPreviewObject(robj *o);
 static int vmSwapOneObjectBlocking(void);
 static int vmSwapOneObjectThreaded(void);
 static int vmCanSwapOut(void);
@@ -635,7 +651,7 @@ static int compareStringObjects(robj *a, robj *b);
 static int equalStringObjects(robj *a, robj *b);
 static void usage();
 static int rewriteAppendOnlyFileBackground(void);
-static int vmSwapObjectBlocking(robj *key, robj *val);
+static vmpointer *vmSwapObjectBlocking(robj *val);
 static int prepareForShutdown();
 static void touchWatchedKey(redisDb *db, robj *key);
 static void touchWatchedKeysOnFlush(int dbid);
@@ -1108,7 +1124,7 @@ static void dictListDestructor(void *privdata, void *val)
     listRelease((list*)val);
 }
 
-static int sdsDictKeyCompare(void *privdata, const void *key1,
+static int dictSdsKeyCompare(void *privdata, const void *key1,
         const void *key2)
 {
     int l1,l2;
@@ -1128,18 +1144,29 @@ static void dictRedisObjectDestructor(void *privdata, void *val)
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
@@ -1152,7 +1179,7 @@ static int dictEncObjKeyCompare(void *privdata, const void *key1,
 
     o1 = getDecodedObject(o1);
     o2 = getDecodedObject(o2);
-    cmp = sdsDictKeyCompare(privdata,o1->ptr,o2->ptr);
+    cmp = dictSdsKeyCompare(privdata,o1->ptr,o2->ptr);
     decrRefCount(o1);
     decrRefCount(o2);
     return cmp;
@@ -1181,7 +1208,7 @@ static unsigned int dictEncObjHash(const void *key) {
     }
 }
 
-/* Sets type and expires */
+/* Sets type */
 static dictType setDictType = {
     dictEncObjHash,            /* hash function */
     NULL,                      /* key dup */
@@ -1201,23 +1228,23 @@ static dictType zsetDictType = {
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
 
@@ -1432,6 +1459,19 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
      * in objects at every object access, and accuracy is not needed.
      * To access a global var is faster than calling time(NULL) */
     server.unixtime = time(NULL);
+    /* We have just 21 bits per object for LRU information.
+     * So we use an (eventually wrapping) LRU clock with minutes resolution.
+     *
+     * When we need to select what object to swap, we compute the minimum
+     * time distance between the current lruclock and the object last access
+     * lruclock info. Even if clocks will wrap on overflow, there is
+     * the interesting property that we are sure that at least
+     * ABS(A-B) minutes passed between current time and timestamp B.
+     *
+     * This is not precise but we don't need at all precision, but just
+     * something statistically reasonable.
+     */
+    server.lruclock = (time(NULL)/60)&((1<<21)-1);
 
     /* We received a SIGTERM, shutting down here in a safe way, as it is
      * not ok doing so inside the signal handler. */
@@ -1530,7 +1570,11 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
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
@@ -2879,6 +2923,12 @@ static void addReplyBulk(redisClient *c, robj *obj) {
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
@@ -2938,23 +2988,20 @@ static robj *createObject(int type, void *ptr) {
         listDelNode(server.objfreelist,head);
         if (server.vm_enabled) pthread_mutex_unlock(&server.obj_freelist_mutex);
     } else {
-        if (server.vm_enabled) {
+        if (server.vm_enabled)
             pthread_mutex_unlock(&server.obj_freelist_mutex);
-            o = zmalloc(sizeof(*o));
-        } else {
-            o = zmalloc(sizeof(*o)-sizeof(struct redisObjectVM));
-        }
+        o = zmalloc(sizeof(*o));
     }
     o->type = type;
     o->encoding = REDIS_ENCODING_RAW;
     o->ptr = ptr;
     o->refcount = 1;
     if (server.vm_enabled) {
         /* Note that this code may run in the context of an I/O thread
-         * and accessing to server.unixtime in theory is an error
+         * and accessing server.lruclock in theory is an error
          * (no locks). But in practice this is safe, and even if we read
-         * garbage Redis will not fail, as it's just a statistical info */
-        o->vm.atime = server.unixtime;
+         * garbage Redis will not fail. */
+        o->lru = server.lruclock;
         o->storage = REDIS_VM_MEMORY;
     }
     return o;
@@ -3059,28 +3106,31 @@ static void incrRefCount(robj *o) {
 static void decrRefCount(void *obj) {
     robj *o = obj;
 
-    if (o->refcount <= 0) redisPanic("decrRefCount against refcount <= 0");
-    /* Object is a key of a swapped out value, or in the process of being
-     * loaded. */
+    /* Object is a swapped out value, or in the process of being loaded. */
     if (server.vm_enabled &&
         (o->storage == REDIS_VM_SWAPPED || o->storage == REDIS_VM_LOADING))
     {
-        if (o->storage == REDIS_VM_LOADING) vmCancelThreadedIOJob(obj);
-        redisAssert(o->type == REDIS_STRING);
-        freeStringObject(o);
-        vmMarkPagesFree(o->vm.page,o->vm.usedpages);
-        pthread_mutex_lock(&server.obj_freelist_mutex);
-        if (listLength(server.objfreelist) > REDIS_OBJFREELIST_MAX ||
-            !listAddNodeHead(server.objfreelist,o))
-            zfree(o);
-        pthread_mutex_unlock(&server.obj_freelist_mutex);
+        vmpointer *vp = obj;
+        if (o->storage == REDIS_VM_LOADING) vmCancelThreadedIOJob(o);
+        vmMarkPagesFree(vp->page,vp->usedpages);
         server.vm_stats_swapped_objects--;
+        zfree(vp);
         return;
     }
-    /* Object is in memory, or in the process of being swapped out. */
+
+    if (o->refcount <= 0) redisPanic("decrRefCount against refcount <= 0");
+    /* Object is in memory, or in the process of being swapped out.
+     *
+     * If the object is being swapped out, abort the operation on
+     * decrRefCount even if the refcount does not drop to 0: the object
+     * is referenced at least two times, as value of the key AND as
+     * job->val in the iojob. So if we don't invalidate the iojob, when it is
+     * done but the relevant key was removed in the meantime, the
+     * complete jobs handler will not find the key about the job and the
+     * assert will fail. */
+    if (server.vm_enabled && o->storage == REDIS_VM_SWAPPING)
+        vmCancelThreadedIOJob(o);
     if (--(o->refcount) == 0) {
-        if (server.vm_enabled && o->storage == REDIS_VM_SWAPPING)
-            vmCancelThreadedIOJob(obj);
         switch(o->type) {
         case REDIS_STRING: freeStringObject(o); break;
         case REDIS_LIST: freeListObject(o); break;
@@ -3097,64 +3147,6 @@ static void decrRefCount(void *obj) {
     }
 }
 
-static robj *lookupKey(redisDb *db, robj *key) {
-    dictEntry *de = dictFind(db->dict,key);
-    if (de) {
-        robj *key = dictGetEntryKey(de);
-        robj *val = dictGetEntryVal(de);
-
-        if (server.vm_enabled) {
-            if (key->storage == REDIS_VM_MEMORY ||
-                key->storage == REDIS_VM_SWAPPING)
-            {
-                /* If we were swapping the object out, stop it, this key
-                 * was requested. */
-                if (key->storage == REDIS_VM_SWAPPING)
-                    vmCancelThreadedIOJob(key);
-                /* Update the access time of the key for the aging algorithm. */
-                key->vm.atime = server.unixtime;
-            } else {
-                int notify = (key->storage == REDIS_VM_LOADING);
-
-                /* Our value was swapped on disk. Bring it at home. */
-                redisAssert(val == NULL);
-                val = vmLoadObject(key);
-                dictGetEntryVal(de) = val;
-
-                /* Clients blocked by the VM subsystem may be waiting for
-                 * this key... */
-                if (notify) handleClientsBlockedOnSwappedKey(db,key);
-            }
-        }
-        return val;
-    } else {
-        return NULL;
-    }
-}
-
-static robj *lookupKeyRead(redisDb *db, robj *key) {
-    expireIfNeeded(db,key);
-    return lookupKey(db,key);
-}
-
-static robj *lookupKeyWrite(redisDb *db, robj *key) {
-    deleteIfVolatile(db,key);
-    touchWatchedKey(db,key);
-    return lookupKey(db,key);
-}
-
-static robj *lookupKeyReadOrReply(redisClient *c, robj *key, robj *reply) {
-    robj *o = lookupKeyRead(c->db, key);
-    if (!o) addReply(c,reply);
-    return o;
-}
-
-static robj *lookupKeyWriteOrReply(redisClient *c, robj *key, robj *reply) {
-    robj *o = lookupKeyWrite(c->db, key);
-    if (!o) addReply(c,reply);
-    return o;
-}
-
 static int checkType(redisClient *c, robj *o, int type) {
     if (o->type != type) {
         addReply(c,shared.wrongtypeerr);
@@ -3163,21 +3155,6 @@ static int checkType(redisClient *c, robj *o, int type) {
     return 0;
 }
 
-static int deleteKey(redisDb *db, robj *key) {
-    int retval;
-
-    /* We need to protect key from destruction: after the first dictDelete()
-     * it may happen that 'key' is no longer valid if we don't increment
-     * it's count. This may happen when we get the object reference directly
-     * from the hash table with dictRandomKey() or dict iterators */
-    incrRefCount(key);
-    if (dictSize(db->expires)) dictDelete(db->expires,key);
-    retval = dictDelete(db->dict,key);
-    decrRefCount(key);
-
-    return retval == DICT_OK;
-}
-
 /* Check if the nul-terminated string 's' can be represented by a long
  * (that is, is a number that fits into long without any other space or
  * character before or after the digits).
@@ -3397,6 +3374,134 @@ static int getLongFromObjectOrReply(redisClient *c, robj *o, long *target, const
     return REDIS_OK;
 }
 
+/* =========================== Keyspace access API ========================== */
+
+static robj *lookupKey(redisDb *db, robj *key) {
+    dictEntry *de = dictFind(db->dict,key->ptr);
+    if (de) {
+        robj *val = dictGetEntryVal(de);
+
+        if (server.vm_enabled) {
+            if (val->storage == REDIS_VM_MEMORY ||
+                val->storage == REDIS_VM_SWAPPING)
+            {
+                /* If we were swapping the object out, cancel the operation */
+                if (val->storage == REDIS_VM_SWAPPING)
+                    vmCancelThreadedIOJob(val);
+                /* Update the access time for the aging algorithm. */
+                val->lru = server.lruclock;
+            } else {
+                int notify = (val->storage == REDIS_VM_LOADING);
+
+                /* Our value was swapped on disk. Bring it at home. */
+                redisAssert(val->type == REDIS_VMPOINTER);
+                val = vmLoadObject(val);
+                dictGetEntryVal(de) = val;
+
+                /* Clients blocked by the VM subsystem may be waiting for
+                 * this key... */
+                if (notify) handleClientsBlockedOnSwappedKey(db,key);
+            }
+        }
+        return val;
+    } else {
+        return NULL;
+    }
+}
+
+static robj *lookupKeyRead(redisDb *db, robj *key) {
+    expireIfNeeded(db,key);
+    return lookupKey(db,key);
+}
+
+static robj *lookupKeyWrite(redisDb *db, robj *key) {
+    deleteIfVolatile(db,key);
+    touchWatchedKey(db,key);
+    return lookupKey(db,key);
+}
+
+static robj *lookupKeyReadOrReply(redisClient *c, robj *key, robj *reply) {
+    robj *o = lookupKeyRead(c->db, key);
+    if (!o) addReply(c,reply);
+    return o;
+}
+
+static robj *lookupKeyWriteOrReply(redisClient *c, robj *key, robj *reply) {
+    robj *o = lookupKeyWrite(c->db, key);
+    if (!o) addReply(c,reply);
+    return o;
+}
+
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
+    int retval;
+
+    if (dictSize(db->expires)) dictDelete(db->expires,key->ptr);
+    retval = dictDelete(db->dict,key->ptr);
+
+    return retval == DICT_OK;
+}
+
 /*============================ RDB saving/loading =========================== */
 
 static int rdbSaveType(FILE *fp, unsigned char type) {
@@ -3751,9 +3856,12 @@ static int rdbSave(char *filename) {
 
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
@@ -3764,20 +3872,20 @@ static int rdbSave(char *filename) {
             }
             /* Save the key and associated value. This requires special
              * handling if the value is swapped out. */
-            if (!server.vm_enabled || key->storage == REDIS_VM_MEMORY ||
-                                      key->storage == REDIS_VM_SWAPPING) {
+            if (!server.vm_enabled || o->storage == REDIS_VM_MEMORY ||
+                                      o->storage == REDIS_VM_SWAPPING) {
                 /* Save type, key, value */
                 if (rdbSaveType(fp,o->type) == -1) goto werr;
-                if (rdbSaveStringObject(fp,key) == -1) goto werr;
+                if (rdbSaveStringObject(fp,&key) == -1) goto werr;
                 if (rdbSaveObject(fp,o) == -1) goto werr;
             } else {
                 /* REDIS_VM_SWAPPED or REDIS_VM_LOADING */
                 robj *po;
                 /* Get a preview of the object in memory */
-                po = vmPreviewObject(key);
+                po = vmPreviewObject(o);
                 /* Save type, key, value */
-                if (rdbSaveType(fp,key->vtype) == -1) goto werr;
-                if (rdbSaveStringObject(fp,key) == -1) goto werr;
+                if (rdbSaveType(fp,po->type) == -1) goto werr;
+                if (rdbSaveStringObject(fp,&key) == -1) goto werr;
                 if (rdbSaveObject(fp,po) == -1) goto werr;
                 /* Remove the loaded object from memory */
                 decrRefCount(po);
@@ -4097,7 +4205,6 @@ static int rdbLoad(char *filename) {
     uint32_t dbid;
     int type, retval, rdbver;
     int swap_all_values = 0;
-    dict *d = server.db[0].dict;
     redisDb *db = server.db+0;
     char buf[1024];
     time_t expiretime, now = time(NULL);
@@ -4139,7 +4246,6 @@ static int rdbLoad(char *filename) {
                 exit(1);
             }
             db = server.db+dbid;
-            d = db->dict;
             continue;
         }
         /* Read key */
@@ -4153,8 +4259,8 @@ static int rdbLoad(char *filename) {
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
@@ -4169,19 +4275,21 @@ static int rdbLoad(char *filename) {
          * to random sampling, otherwise we may try to swap already
          * swapped keys. */
         if (swap_all_values) {
-            dictEntry *de = dictFind(d,key);
+            dictEntry *de = dictFind(db->dict,key->ptr);
 
             /* de may be NULL since the key already expired */
             if (de) {
-                key = dictGetEntryKey(de);
+                vmpointer *vp;
                 val = dictGetEntryVal(de);
 
-                if (vmSwapObjectBlocking(key,val) == REDIS_OK) {
-                    dictGetEntryVal(de) = NULL;
-                }
+                if (val->refcount == 1 &&
+                    (vp = vmSwapObjectBlocking(val)) != NULL)
+                    dictGetEntryVal(de) = vp;
             }
+            decrRefCount(key);
             continue;
         }
+        decrRefCount(key);
 
         /* Flush data on disk once 32 MB of additional RAM are used... */
         force_swapout = 0;
@@ -4279,23 +4387,16 @@ static void setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj
 
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
@@ -4337,11 +4438,7 @@ static void getCommand(redisClient *c) {
 
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
@@ -4387,17 +4484,9 @@ static void msetGenericCommand(redisClient *c, int nx) {
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
@@ -4414,7 +4503,6 @@ static void msetnxCommand(redisClient *c) {
 
 static void incrDecrCommand(redisClient *c, long long incr) {
     long long value;
-    int retval;
     robj *o;
 
     o = lookupKeyWrite(c->db,c->argv[1]);
@@ -4423,13 +4511,7 @@ static void incrDecrCommand(redisClient *c, long long incr) {
 
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
@@ -4466,17 +4548,10 @@ static void appendCommand(redisClient *c) {
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
@@ -4488,7 +4563,7 @@ static void appendCommand(redisClient *c) {
 
             o = createStringObject(decoded->ptr, sdslen(decoded->ptr));
             decrRefCount(decoded);
-            dictReplace(c->db->dict,c->argv[1],o);
+            dbReplace(c->db,c->argv[1],o);
         }
         /* APPEND! */
         if (c->argv[2]->encoding == REDIS_ENCODING_RAW) {
@@ -4547,7 +4622,7 @@ static void delCommand(redisClient *c) {
     int deleted = 0, j;
 
     for (j = 1; j < c->argc; j++) {
-        if (deleteKey(c->db,c->argv[j])) {
+        if (dbDelete(c->db,c->argv[j])) {
             touchWatchedKey(c->db,c->argv[j]);
             server.dirty++;
             deleted++;
@@ -4558,7 +4633,7 @@ static void delCommand(redisClient *c) {
 
 static void existsCommand(redisClient *c) {
     expireIfNeeded(c->db,c->argv[1]);
-    if (dictFind(c->db->dict,c->argv[1])) {
+    if (dbExists(c->db,c->argv[1])) {
         addReply(c, shared.cone);
     } else {
         addReply(c, shared.czero);
@@ -4576,27 +4651,15 @@ static void selectCommand(redisClient *c) {
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
@@ -4611,15 +4674,17 @@ static void keysCommand(redisClient *c) {
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
@@ -4702,17 +4767,15 @@ static void renameGenericCommand(redisClient *c, int nx) {
 
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
@@ -4757,15 +4820,14 @@ static void moveCommand(redisClient *c) {
 
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
@@ -4788,9 +4850,8 @@ static void pushGenericCommand(redisClient *c, int where) {
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
@@ -4894,7 +4955,7 @@ static void popGenericCommand(redisClient *c, int where) {
         robj *ele = listNodeValue(ln);
         addReplyBulk(c,ele);
         listDelNode(list,ln);
-        if (listLength(list) == 0) deleteKey(c->db,c->argv[1]);
+        if (listLength(list) == 0) dbDelete(c->db,c->argv[1]);
         server.dirty++;
     }
 }
@@ -4987,7 +5048,7 @@ static void ltrimCommand(redisClient *c) {
         ln = listLast(list);
         listDelNode(list,ln);
     }
-    if (listLength(list) == 0) deleteKey(c->db,c->argv[1]);
+    if (listLength(list) == 0) dbDelete(c->db,c->argv[1]);
     server.dirty++;
     addReply(c,shared.ok);
 }
@@ -5021,7 +5082,7 @@ static void lremCommand(redisClient *c) {
         }
         ln = next;
     }
-    if (listLength(list) == 0) deleteKey(c->db,c->argv[1]);
+    if (listLength(list) == 0) dbDelete(c->db,c->argv[1]);
     addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",removed));
 }
 
@@ -5068,8 +5129,7 @@ static void rpoplpushcommand(redisClient *c) {
             if (dobj == NULL) {
                 /* Create the list if the key does not exist */
                 dobj = createListObject();
-                dictAdd(c->db->dict,c->argv[2],dobj);
-                incrRefCount(c->argv[2]);
+                dbAdd(c->db,c->argv[2],dobj);
             }
             dstlist = dobj->ptr;
             listAddNodeHead(dstlist,ele);
@@ -5081,7 +5141,7 @@ static void rpoplpushcommand(redisClient *c) {
 
         /* Finally remove the element from the source list */
         listDelNode(srclist,ln);
-        if (listLength(srclist) == 0) deleteKey(c->db,c->argv[1]);
+        if (listLength(srclist) == 0) dbDelete(c->db,c->argv[1]);
         server.dirty++;
     }
 }
@@ -5094,8 +5154,7 @@ static void saddCommand(redisClient *c) {
     set = lookupKeyWrite(c->db,c->argv[1]);
     if (set == NULL) {
         set = createSetObject();
-        dictAdd(c->db->dict,c->argv[1],set);
-        incrRefCount(c->argv[1]);
+        dbAdd(c->db,c->argv[1],set);
     } else {
         if (set->type != REDIS_SET) {
             addReply(c,shared.wrongtypeerr);
@@ -5120,7 +5179,7 @@ static void sremCommand(redisClient *c) {
     if (dictDelete(set->ptr,c->argv[2]) == DICT_OK) {
         server.dirty++;
         if (htNeedsResize(set->ptr)) dictResize(set->ptr);
-        if (dictSize((dict*)set->ptr) == 0) deleteKey(c->db,c->argv[1]);
+        if (dictSize((dict*)set->ptr) == 0) dbDelete(c->db,c->argv[1]);
         addReply(c,shared.cone);
     } else {
         addReply(c,shared.czero);
@@ -5151,13 +5210,12 @@ static void smoveCommand(redisClient *c) {
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
@@ -5203,7 +5261,7 @@ static void spopCommand(redisClient *c) {
         addReplyBulk(c,ele);
         dictDelete(set->ptr,ele);
         if (htNeedsResize(set->ptr)) dictResize(set->ptr);
-        if (dictSize((dict*)set->ptr) == 0) deleteKey(c->db,c->argv[1]);
+        if (dictSize((dict*)set->ptr) == 0) dbDelete(c->db,c->argv[1]);
         server.dirty++;
     }
 }
@@ -5247,7 +5305,7 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, unsigned long
         if (!setobj) {
             zfree(dv);
             if (dstkey) {
-                if (deleteKey(c->db,dstkey))
+                if (dbDelete(c->db,dstkey))
                     server.dirty++;
                 addReply(c,shared.czero);
             } else {
@@ -5307,10 +5365,9 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, unsigned long
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
@@ -5410,10 +5467,9 @@ static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnu
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
@@ -5769,8 +5825,7 @@ static void zaddGenericCommand(redisClient *c, robj *key, robj *ele, double scor
     zsetobj = lookupKeyWrite(c->db,key);
     if (zsetobj == NULL) {
         zsetobj = createZsetObject();
-        dictAdd(c->db->dict,key,zsetobj);
-        incrRefCount(key);
+        dbAdd(c->db,key,zsetobj);
     } else {
         if (zsetobj->type != REDIS_ZSET) {
             addReply(c,shared.wrongtypeerr);
@@ -5886,7 +5941,7 @@ static void zremCommand(redisClient *c) {
     /* Delete from the hash table */
     dictDelete(zs->dict,c->argv[2]);
     if (htNeedsResize(zs->dict)) dictResize(zs->dict);
-    if (dictSize(zs->dict) == 0) deleteKey(c->db,c->argv[1]);
+    if (dictSize(zs->dict) == 0) dbDelete(c->db,c->argv[1]);
     server.dirty++;
     addReply(c,shared.cone);
 }
@@ -5907,7 +5962,7 @@ static void zremrangebyscoreCommand(redisClient *c) {
     zs = zsetobj->ptr;
     deleted = zslDeleteRangeByScore(zs->zsl,min,max,zs->dict);
     if (htNeedsResize(zs->dict)) dictResize(zs->dict);
-    if (dictSize(zs->dict) == 0) deleteKey(c->db,c->argv[1]);
+    if (dictSize(zs->dict) == 0) dbDelete(c->db,c->argv[1]);
     server.dirty += deleted;
     addReplyLongLong(c,deleted);
 }
@@ -5945,7 +6000,7 @@ static void zremrangebyrankCommand(redisClient *c) {
      * use 1-based rank */
     deleted = zslDeleteRangeByRank(zs->zsl,start+1,end+1,zs->dict);
     if (htNeedsResize(zs->dict)) dictResize(zs->dict);
-    if (dictSize(zs->dict) == 0) deleteKey(c->db,c->argv[1]);
+    if (dictSize(zs->dict) == 0) dbDelete(c->db,c->argv[1]);
     server.dirty += deleted;
     addReplyLongLong(c, deleted);
 }
@@ -6133,10 +6188,9 @@ static void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
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
@@ -6612,8 +6666,7 @@ static robj *hashLookupWriteOrCreate(redisClient *c, robj *key) {
     robj *o = lookupKeyWrite(c->db,key);
     if (o == NULL) {
         o = createHashObject();
-        dictAdd(c->db->dict,key,o);
-        incrRefCount(key);
+        dbAdd(c->db,key,o);
     } else {
         if (o->type != REDIS_HASH) {
             addReply(c,shared.wrongtypeerr);
@@ -6737,7 +6790,7 @@ static void hdelCommand(redisClient *c) {
         checkType(c,o,REDIS_HASH)) return;
 
     if (hashDelete(o,c->argv[2])) {
-        if (hashLength(o) == 0) deleteKey(c->db,c->argv[1]);
+        if (hashLength(o) == 0) dbDelete(c->db,c->argv[1]);
         addReply(c,shared.cone);
         server.dirty++;
     } else {
@@ -7211,9 +7264,7 @@ static void sortCommand(redisClient *c) {
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
@@ -7392,18 +7443,19 @@ static void monitorCommand(redisClient *c) {
 
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
@@ -7415,7 +7467,7 @@ static time_t getExpire(redisDb *db, robj *key) {
 
     /* No expire? return ASAP */
     if (dictSize(db->expires) == 0 ||
-       (de = dictFind(db->expires,key)) == NULL) return -1;
+       (de = dictFind(db->expires,key->ptr)) == NULL) return -1;
 
     return (time_t) dictGetEntryVal(de);
 }
@@ -7426,30 +7478,30 @@ static int expireIfNeeded(redisDb *db, robj *key) {
 
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
@@ -7460,13 +7512,13 @@ static void expireGenericCommand(redisClient *c, robj *key, robj *param, long of
 
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
@@ -8235,7 +8287,7 @@ static void freeMemoryIfNeeded(void) {
                         minttl = t;
                     }
                 }
-                deleteKey(server.db+j,minkey);
+                dbDelete(server.db+j,minkey);
             }
         }
         if (!freed) return; /* nothing to free... */
@@ -8244,6 +8296,48 @@ static void freeMemoryIfNeeded(void) {
 
 /* ============================== Append Only file ========================== */
 
+/* Called when the user switches from "appendonly yes" to "appendonly no"
+ * at runtime using the CONFIG command. */
+static void stopAppendOnly(void) {
+    flushAppendOnlyFile();
+    aof_fsync(server.appendfd);
+    close(server.appendfd);
+
+    server.appendfd = -1;
+    server.appendseldb = -1;
+    server.appendonly = 0;
+    /* rewrite operation in progress? kill it, wait child exit */
+    if (server.bgsavechildpid != -1) {
+        int statloc;
+
+        if (kill(server.bgsavechildpid,SIGKILL) != -1)
+            wait3(&statloc,0,NULL);
+        /* reset the buffer accumulating changes while the child saves */
+        sdsfree(server.bgrewritebuf);
+        server.bgrewritebuf = sdsempty();
+        server.bgsavechildpid = -1;
+    }
+}
+
+/* Called when the user switches from "appendonly no" to "appendonly yes"
+ * at runtime using the CONFIG command. */
+static int startAppendOnly(void) {
+    server.appendonly = 1;
+    server.lastfsync = time(NULL);
+    server.appendfd = open(server.appendfilename,O_WRONLY|O_APPEND|O_CREAT,0644);
+    if (server.appendfd == -1) {
+        redisLog(REDIS_WARNING,"Used tried to switch on AOF via CONFIG, but I can't open the AOF file: %s",strerror(errno));
+        return REDIS_ERR;
+    }
+    if (rewriteAppendOnlyFileBackground() == REDIS_ERR) {
+        server.appendonly = 0;
+        close(server.appendfd);
+        redisLog(REDIS_WARNING,"Used tried to switch on AOF via CONFIG, I can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.",strerror(errno));
+        return REDIS_ERR;
+    }
+    return REDIS_OK;
+}
+
 /* Write the append only file buffer on disk.
  *
  * Since we are required to write the AOF before replying to the client,
@@ -8598,32 +8692,34 @@ static int rewriteAppendOnlyFile(char *filename) {
 
         /* Iterate this DB writing every entry */
         while((de = dictNext(di)) != NULL) {
-            robj *key, *o;
+            sds keystr = dictGetEntryKey(de);
+            robj key, *o;
             time_t expiretime;
             int swapped;
 
-            key = dictGetEntryKey(de);
+            keystr = dictGetEntryKey(de);
+            o = dictGetEntryVal(de);
+            initStaticStringObject(key,keystr);
             /* If the value for this key is swapped, load a preview in memory.
              * We use a "swapped" flag to remember if we need to free the
              * value object instead to just increment the ref count anyway
              * in order to avoid copy-on-write of pages if we are forked() */
-            if (!server.vm_enabled || key->storage == REDIS_VM_MEMORY ||
-                key->storage == REDIS_VM_SWAPPING) {
-                o = dictGetEntryVal(de);
+            if (!server.vm_enabled || o->storage == REDIS_VM_MEMORY ||
+                o->storage == REDIS_VM_SWAPPING) {
                 swapped = 0;
             } else {
-                o = vmPreviewObject(key);
+                o = vmPreviewObject(o);
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
@@ -8637,7 +8733,7 @@ static int rewriteAppendOnlyFile(char *filename) {
                     robj *eleobj = listNodeValue(ln);
 
                     if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                    if (fwriteBulkObject(fp,key) == 0) goto werr;
+                    if (fwriteBulkObject(fp,&key) == 0) goto werr;
                     if (fwriteBulkObject(fp,eleobj) == 0) goto werr;
                 }
             } else if (o->type == REDIS_SET) {
@@ -8651,7 +8747,7 @@ static int rewriteAppendOnlyFile(char *filename) {
                     robj *eleobj = dictGetEntryKey(de);
 
                     if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                    if (fwriteBulkObject(fp,key) == 0) goto werr;
+                    if (fwriteBulkObject(fp,&key) == 0) goto werr;
                     if (fwriteBulkObject(fp,eleobj) == 0) goto werr;
                 }
                 dictReleaseIterator(di);
@@ -8667,7 +8763,7 @@ static int rewriteAppendOnlyFile(char *filename) {
                     double *score = dictGetEntryVal(de);
 
                     if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                    if (fwriteBulkObject(fp,key) == 0) goto werr;
+                    if (fwriteBulkObject(fp,&key) == 0) goto werr;
                     if (fwriteBulkDouble(fp,*score) == 0) goto werr;
                     if (fwriteBulkObject(fp,eleobj) == 0) goto werr;
                 }
@@ -8683,7 +8779,7 @@ static int rewriteAppendOnlyFile(char *filename) {
 
                     while((p = zipmapNext(p,&field,&flen,&val,&vlen)) != NULL) {
                         if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                        if (fwriteBulkObject(fp,key) == 0) goto werr;
+                        if (fwriteBulkObject(fp,&key) == 0) goto werr;
                         if (fwriteBulkString(fp,(char*)field,flen) == -1)
                             return -1;
                         if (fwriteBulkString(fp,(char*)val,vlen) == -1)
@@ -8698,7 +8794,7 @@ static int rewriteAppendOnlyFile(char *filename) {
                         robj *val = dictGetEntryVal(de);
 
                         if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                        if (fwriteBulkObject(fp,key) == 0) goto werr;
+                        if (fwriteBulkObject(fp,&key) == 0) goto werr;
                         if (fwriteBulkObject(fp,field) == -1) return -1;
                         if (fwriteBulkObject(fp,val) == -1) return -1;
                     }
@@ -8713,7 +8809,7 @@ static int rewriteAppendOnlyFile(char *filename) {
                 /* If this key is already expired skip it */
                 if (expiretime < now) continue;
                 if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                if (fwriteBulkObject(fp,key) == 0) goto werr;
+                if (fwriteBulkObject(fp,&key) == 0) goto werr;
                 if (fwriteBulkLong(fp,expiretime) == 0) goto werr;
             }
             if (swapped) decrRefCount(o);
@@ -8836,50 +8932,19 @@ static void aofRemoveTempFile(pid_t childpid) {
  * as a fully non-blocking VM.
  */
 
-/* Called when the user switches from "appendonly yes" to "appendonly no"
- * at runtime using the CONFIG command. */
-static void stopAppendOnly(void) {
-    flushAppendOnlyFile();
-    aof_fsync(server.appendfd);
-    close(server.appendfd);
+/* =================== Virtual Memory - Blocking Side  ====================== */
 
-    server.appendfd = -1;
-    server.appendseldb = -1;
-    server.appendonly = 0;
-    /* rewrite operation in progress? kill it, wait child exit */
-    if (server.bgsavechildpid != -1) {
-        int statloc;
+/* Create a VM pointer object. This kind of objects are used in place of
+ * values in the key -> value hash table, for swapped out objects. */
+static vmpointer *createVmPointer(int vtype) {
+    vmpointer *vp = zmalloc(sizeof(vmpointer));
 
-        if (kill(server.bgsavechildpid,SIGKILL) != -1)
-            wait3(&statloc,0,NULL);
-        /* reset the buffer accumulating changes while the child saves */
-        sdsfree(server.bgrewritebuf);
-        server.bgrewritebuf = sdsempty();
-        server.bgsavechildpid = -1;
-    }
-}
-
-/* Called when the user switches from "appendonly no" to "appendonly yes"
- * at runtime using the CONFIG command. */
-static int startAppendOnly(void) {
-    server.appendonly = 1;
-    server.lastfsync = time(NULL);
-    server.appendfd = open(server.appendfilename,O_WRONLY|O_APPEND|O_CREAT,0644);
-    if (server.appendfd == -1) {
-        redisLog(REDIS_WARNING,"Used tried to switch on AOF via CONFIG, but I can't open the AOF file: %s",strerror(errno));
-        return REDIS_ERR;
-    }
-    if (rewriteAppendOnlyFileBackground() == REDIS_ERR) {
-        server.appendonly = 0;
-        close(server.appendfd);
-        redisLog(REDIS_WARNING,"Used tried to switch on AOF via CONFIG, I can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.",strerror(errno));
-        return REDIS_ERR;
-    }
-    return REDIS_OK;
+    vp->type = REDIS_VMPOINTER;
+    vp->storage = REDIS_VM_SWAPPED;
+    vp->vtype = vtype;
+    return vp;
 }
 
-/* =================== Virtual Memory - Blocking Side  ====================== */
-
 static void vmInit(void) {
     off_t totsize;
     int pipefds[2];
@@ -9094,30 +9159,33 @@ static int vmWriteObjectOnSwap(robj *o, off_t page) {
     return REDIS_OK;
 }
 
-/* Swap the 'val' object relative to 'key' into disk. Store all the information
- * needed to later retrieve the object into the key object.
+/* Transfers the 'val' object to disk. Store all the information
+ * a 'vmpointer' object containing all the information needed to load the
+ * object back later is returned.
+ *
  * If we can't find enough contiguous empty pages to swap the object on disk
- * REDIS_ERR is returned. */
-static int vmSwapObjectBlocking(robj *key, robj *val) {
+ * NULL is returned. */
+static vmpointer *vmSwapObjectBlocking(robj *val) {
     off_t pages = rdbSavedObjectPages(val,NULL);
     off_t page;
+    vmpointer *vp;
+
+    assert(val->storage == REDIS_VM_MEMORY);
+    assert(val->refcount == 1);
+    if (vmFindContiguousPages(&page,pages) == REDIS_ERR) return NULL;
+    if (vmWriteObjectOnSwap(val,page) == REDIS_ERR) return NULL;
 
-    assert(key->storage == REDIS_VM_MEMORY);
-    assert(key->refcount == 1);
-    if (vmFindContiguousPages(&page,pages) == REDIS_ERR) return REDIS_ERR;
-    if (vmWriteObjectOnSwap(val,page) == REDIS_ERR) return REDIS_ERR;
-    key->vm.page = page;
-    key->vm.usedpages = pages;
-    key->storage = REDIS_VM_SWAPPED;
-    key->vtype = val->type;
+    vp = createVmPointer(val->type);
+    vp->page = page;
+    vp->usedpages = pages;
     decrRefCount(val); /* Deallocate the object from memory. */
     vmMarkPagesUsed(page,pages);
-    redisLog(REDIS_DEBUG,"VM: object %s swapped out at %lld (%lld pages)",
-        (unsigned char*) key->ptr,
+    redisLog(REDIS_DEBUG,"VM: object %p swapped out at %lld (%lld pages)",
+        (void*) val,
         (unsigned long long) page, (unsigned long long) pages);
     server.vm_stats_swapped_objects++;
     server.vm_stats_swapouts++;
-    return REDIS_OK;
+    return vp;
 }
 
 static robj *vmReadObjectFromSwap(off_t page, int type) {
@@ -9139,46 +9207,47 @@ static robj *vmReadObjectFromSwap(off_t page, int type) {
     return o;
 }
 
-/* Load the value object relative to the 'key' object from swap to memory.
+/* Load the specified object from swap to memory.
  * The newly allocated object is returned.
  *
  * If preview is true the unserialized object is returned to the caller but
- * no changes are made to the key object, nor the pages are marked as freed */
-static robj *vmGenericLoadObject(robj *key, int preview) {
+ * the pages are not marked as freed, nor the vp object is freed. */
+static robj *vmGenericLoadObject(vmpointer *vp, int preview) {
     robj *val;
 
-    redisAssert(key->storage == REDIS_VM_SWAPPED || key->storage == REDIS_VM_LOADING);
-    val = vmReadObjectFromSwap(key->vm.page,key->vtype);
+    redisAssert(vp->type == REDIS_VMPOINTER &&
+        (vp->storage == REDIS_VM_SWAPPED || vp->storage == REDIS_VM_LOADING));
+    val = vmReadObjectFromSwap(vp->page,vp->vtype);
     if (!preview) {
-        key->storage = REDIS_VM_MEMORY;
-        key->vm.atime = server.unixtime;
-        vmMarkPagesFree(key->vm.page,key->vm.usedpages);
-        redisLog(REDIS_DEBUG, "VM: object %s loaded from disk",
-            (unsigned char*) key->ptr);
+        redisLog(REDIS_DEBUG, "VM: object %p loaded from disk", (void*)vp);
+        vmMarkPagesFree(vp->page,vp->usedpages);
+        zfree(vp);
         server.vm_stats_swapped_objects--;
     } else {
-        redisLog(REDIS_DEBUG, "VM: object %s previewed from disk",
-            (unsigned char*) key->ptr);
+        redisLog(REDIS_DEBUG, "VM: object %p previewed from disk", (void*)vp);
     }
     server.vm_stats_swapins++;
     return val;
 }
 
-/* Plain object loading, from swap to memory */
-static robj *vmLoadObject(robj *key) {
+/* Plain object loading, from swap to memory.
+ *
+ * 'o' is actually a redisVmPointer structure that will be freed by the call.
+ * The return value is the loaded object. */
+static robj *vmLoadObject(robj *o) {
     /* If we are loading the object in background, stop it, we
      * need to load this object synchronously ASAP. */
-    if (key->storage == REDIS_VM_LOADING)
-        vmCancelThreadedIOJob(key);
-    return vmGenericLoadObject(key,0);
+    if (o->storage == REDIS_VM_LOADING)
+        vmCancelThreadedIOJob(o);
+    return vmGenericLoadObject((vmpointer*)o,0);
 }
 
 /* Just load the value on disk, without to modify the key.
  * This is useful when we want to perform some operation on the value
  * without to really bring it from swap to memory, like while saving the
  * dataset or rewriting the append only log. */
-static robj *vmPreviewObject(robj *key) {
-    return vmGenericLoadObject(key,1);
+static robj *vmPreviewObject(robj *o) {
+    return vmGenericLoadObject((vmpointer*)o,1);
 }
 
 /* How a good candidate is this object for swapping?
@@ -9193,14 +9262,16 @@ static robj *vmPreviewObject(robj *key) {
  * proportionally, this is why we use the logarithm. This algorithm is
  * just a first try and will probably be tuned later. */
 static double computeObjectSwappability(robj *o) {
-    time_t age = server.unixtime - o->vm.atime;
+    /* actual age can be >= minage, but not < minage. As we use wrapping
+     * 21 bit clocks with minutes resolution for the LRU. */
+    time_t minage = abs(server.lruclock - o->lru);
     long asize = 0;
     list *l;
     dict *d;
     struct dictEntry *de;
     int z;
 
-    if (age <= 0) return 0;
+    if (minage <= 0) return 0;
     switch(o->type) {
     case REDIS_STRING:
         if (o->encoding != REDIS_ENCODING_RAW) {
@@ -9219,8 +9290,7 @@ static double computeObjectSwappability(robj *o) {
             long elesize;
 
             elesize = (ele->encoding == REDIS_ENCODING_RAW) ?
-                            (sizeof(*o)+sdslen(ele->ptr)) :
-                            sizeof(*o);
+                            (sizeof(*o)+sdslen(ele->ptr)) : sizeof(*o);
             asize += (sizeof(listNode)+elesize)*listLength(l);
         }
         break;
@@ -9238,8 +9308,7 @@ static double computeObjectSwappability(robj *o) {
             de = dictGetRandomKey(d);
             ele = dictGetEntryKey(de);
             elesize = (ele->encoding == REDIS_ENCODING_RAW) ?
-                            (sizeof(*o)+sdslen(ele->ptr)) :
-                            sizeof(*o);
+                            (sizeof(*o)+sdslen(ele->ptr)) : sizeof(*o);
             asize += (sizeof(struct dictEntry)+elesize)*dictSize(d);
             if (z) asize += sizeof(zskiplistNode)*dictSize(d);
         }
@@ -9266,18 +9335,16 @@ static double computeObjectSwappability(robj *o) {
                 de = dictGetRandomKey(d);
                 ele = dictGetEntryKey(de);
                 elesize = (ele->encoding == REDIS_ENCODING_RAW) ?
-                                (sizeof(*o)+sdslen(ele->ptr)) :
-                                sizeof(*o);
+                                (sizeof(*o)+sdslen(ele->ptr)) : sizeof(*o);
                 ele = dictGetEntryVal(de);
                 elesize = (ele->encoding == REDIS_ENCODING_RAW) ?
-                                (sizeof(*o)+sdslen(ele->ptr)) :
-                                sizeof(*o);
+                                (sizeof(*o)+sdslen(ele->ptr)) : sizeof(*o);
                 asize += (sizeof(struct dictEntry)+elesize)*dictSize(d);
             }
         }
         break;
     }
-    return (double)age*log(1+asize);
+    return (double)minage*log(1+asize);
 }
 
 /* Try to swap an object that's a good candidate for swapping.
@@ -9291,7 +9358,8 @@ static int vmSwapOneObject(int usethreads) {
     struct dictEntry *best = NULL;
     double best_swappability = 0;
     redisDb *best_db = NULL;
-    robj *key, *val;
+    robj *val;
+    sds key;
 
     for (j = 0; j < server.dbnum; j++) {
         redisDb *db = server.db+j;
@@ -9307,16 +9375,14 @@ static int vmSwapOneObject(int usethreads) {
 
             if (maxtries) maxtries--;
             de = dictGetRandomKey(db->dict);
-            key = dictGetEntryKey(de);
             val = dictGetEntryVal(de);
             /* Only swap objects that are currently in memory.
              *
-             * Also don't swap shared objects if threaded VM is on, as we
-             * try to ensure that the main thread does not touch the
+             * Also don't swap shared objects: not a good idea in general and
+             * we need to ensure that the main thread does not touch the
              * object while the I/O thread is using it, but we can't
              * control other keys without adding additional mutex. */
-            if (key->storage != REDIS_VM_MEMORY ||
-                (server.vm_max_threads != 0 && val->refcount != 1)) {
+            if (val->storage != REDIS_VM_MEMORY || val->refcount != 1) {
                 if (maxtries) i--; /* don't count this try */
                 continue;
             }
@@ -9333,21 +9399,19 @@ static int vmSwapOneObject(int usethreads) {
     val = dictGetEntryVal(best);
 
     redisLog(REDIS_DEBUG,"Key with best swappability: %s, %f",
-        key->ptr, best_swappability);
+        key, best_swappability);
 
-    /* Unshare the key if needed */
-    if (key->refcount > 1) {
-        robj *newkey = dupStringObject(key);
-        decrRefCount(key);
-        key = dictGetEntryKey(best) = newkey;
-    }
     /* Swap it */
     if (usethreads) {
-        vmSwapObjectThreaded(key,val,best_db);
+        robj *keyobj = createStringObject(key,sdslen(key));
+        vmSwapObjectThreaded(keyobj,val,best_db);
+        decrRefCount(keyobj);
         return REDIS_OK;
     } else {
-        if (vmSwapObjectBlocking(key,val) == REDIS_OK) {
-            dictGetEntryVal(best) = NULL;
+        vmpointer *vp;
+
+        if ((vp = vmSwapObjectBlocking(val)) != NULL) {
+            dictGetEntryVal(best) = vp;
             return REDIS_OK;
         } else {
             return REDIS_ERR;
@@ -9370,30 +9434,20 @@ static int vmCanSwapOut(void) {
     return (server.bgsavechildpid == -1 && server.bgrewritechildpid == -1);
 }
 
-/* Delete a key if swapped. Returns 1 if the key was found, was swapped
- * and was deleted. Otherwise 0 is returned. */
-static int deleteIfSwapped(redisDb *db, robj *key) {
-    dictEntry *de;
-    robj *foundkey;
-
-    if ((de = dictFind(db->dict,key)) == NULL) return 0;
-    foundkey = dictGetEntryKey(de);
-    if (foundkey->storage == REDIS_VM_MEMORY) return 0;
-    deleteKey(db,key);
-    return 1;
-}
-
 /* =================== Virtual Memory - Threaded I/O  ======================= */
 
 static void freeIOJob(iojob *j) {
     if ((j->type == REDIS_IOJOB_PREPARE_SWAP ||
         j->type == REDIS_IOJOB_DO_SWAP ||
         j->type == REDIS_IOJOB_LOAD) && j->val != NULL)
+    {
+         /* we fix the storage type, otherwise decrRefCount() will try to
+          * kill the I/O thread Job (that does no longer exists). */
+        if (j->val->storage == REDIS_VM_SWAPPING)
+            j->val->storage = REDIS_VM_MEMORY;
         decrRefCount(j->val);
-    /* We don't decrRefCount the j->key field as we did't incremented
-     * the count creating IO Jobs. This is because the key field here is
-     * just used as an indentifier and if a key is removed the Job should
-     * never be touched again. */
+    }
+    decrRefCount(j->key);
     zfree(j);
 }
 
@@ -9414,7 +9468,6 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
     while((retval = read(fd,buf,1)) == 1) {
         iojob *j;
         listNode *ln;
-        robj *key;
         struct dictEntry *de;
 
         redisLog(REDIS_DEBUG,"Processing I/O completed job");
@@ -9437,27 +9490,26 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
         }
         /* Post process it in the main thread, as there are things we
          * can do just here to avoid race conditions and/or invasive locks */
-        redisLog(REDIS_DEBUG,"Job %p type: %d, key at %p (%s) refcount: %d\n", (void*) j, j->type, (void*)j->key, (char*)j->key->ptr, j->key->refcount);
-        de = dictFind(j->db->dict,j->key);
-        assert(de != NULL);
-        key = dictGetEntryKey(de);
+        redisLog(REDIS_DEBUG,"COMPLETED Job type: %d, ID %p, key: %s", j->type, (void*)j->id, (unsigned char*)j->key->ptr);
+        de = dictFind(j->db->dict,j->key->ptr);
+        redisAssert(de != NULL);
         if (j->type == REDIS_IOJOB_LOAD) {
             redisDb *db;
+            vmpointer *vp = dictGetEntryVal(de);
 
             /* Key loaded, bring it at home */
-            key->storage = REDIS_VM_MEMORY;
-            key->vm.atime = server.unixtime;
-            vmMarkPagesFree(key->vm.page,key->vm.usedpages);
+            vmMarkPagesFree(vp->page,vp->usedpages);
             redisLog(REDIS_DEBUG, "VM: object %s loaded from disk (threaded)",
-                (unsigned char*) key->ptr);
+                (unsigned char*) j->key->ptr);
             server.vm_stats_swapped_objects--;
             server.vm_stats_swapins++;
             dictGetEntryVal(de) = j->val;
             incrRefCount(j->val);
             db = j->db;
-            freeIOJob(j);
             /* Handle clients waiting for this key to be loaded. */
-            handleClientsBlockedOnSwappedKey(db,key);
+            handleClientsBlockedOnSwappedKey(db,j->key);
+            freeIOJob(j);
+            zfree(vp);
         } else if (j->type == REDIS_IOJOB_PREPARE_SWAP) {
             /* Now we know the amount of pages required to swap this object.
              * Let's find some space for it, and queue this task again
@@ -9467,8 +9519,8 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
             {
                 /* Ooops... no space or we can't swap as there is
                  * a fork()ed Redis trying to save stuff on disk. */
+                j->val->storage = REDIS_VM_MEMORY; /* undo operation */
                 freeIOJob(j);
-                key->storage = REDIS_VM_MEMORY; /* undo operation */
             } else {
                 /* Note that we need to mark this pages as used now,
                  * if the job will be canceled, we'll mark them as freed
@@ -9480,28 +9532,29 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
                 unlockThreadedIO();
             }
         } else if (j->type == REDIS_IOJOB_DO_SWAP) {
-            robj *val;
+            vmpointer *vp;
 
             /* Key swapped. We can finally free some memory. */
-            if (key->storage != REDIS_VM_SWAPPING) {
-                printf("key->storage: %d\n",key->storage);
-                printf("key->name: %s\n",(char*)key->ptr);
-                printf("key->refcount: %d\n",key->refcount);
+            if (j->val->storage != REDIS_VM_SWAPPING) {
+                vmpointer *vp = (vmpointer*) j->id;
+                printf("storage: %d\n",vp->storage);
+                printf("key->name: %s\n",(char*)j->key->ptr);
                 printf("val: %p\n",(void*)j->val);
                 printf("val->type: %d\n",j->val->type);
                 printf("val->ptr: %s\n",(char*)j->val->ptr);
             }
-            redisAssert(key->storage == REDIS_VM_SWAPPING);
-            val = dictGetEntryVal(de);
-            key->vm.page = j->page;
-            key->vm.usedpages = j->pages;
-            key->storage = REDIS_VM_SWAPPED;
-            key->vtype = j->val->type;
-            decrRefCount(val); /* Deallocate the object from memory. */
-            dictGetEntryVal(de) = NULL;
+            redisAssert(j->val->storage == REDIS_VM_SWAPPING);
+            vp = createVmPointer(j->val->type);
+            vp->page = j->page;
+            vp->usedpages = j->pages;
+            dictGetEntryVal(de) = vp;
+            /* Fix the storage otherwise decrRefCount will attempt to
+             * remove the associated I/O job */
+            j->val->storage = REDIS_VM_MEMORY;
+            decrRefCount(j->val);
             redisLog(REDIS_DEBUG,
                 "VM: object %s swapped out at %lld (%lld pages) (threaded)",
-                (unsigned char*) key->ptr,
+                (unsigned char*) j->key->ptr,
                 (unsigned long long) j->page, (unsigned long long) j->pages);
             server.vm_stats_swapped_objects++;
             server.vm_stats_swapouts++;
@@ -9556,7 +9609,7 @@ static void vmCancelThreadedIOJob(robj *o) {
     assert(o->storage == REDIS_VM_LOADING || o->storage == REDIS_VM_SWAPPING);
 again:
     lockThreadedIO();
-    /* Search for a matching key in one of the queues */
+    /* Search for a matching object in one of the queues */
     for (i = 0; i < 3; i++) {
         listNode *ln;
         listIter li;
@@ -9566,9 +9619,9 @@ static void vmCancelThreadedIOJob(robj *o) {
             iojob *job = ln->value;
 
             if (job->canceled) continue; /* Skip this, already canceled. */
-            if (job->key == o) {
-                redisLog(REDIS_DEBUG,"*** CANCELED %p (%s) (type %d) (LIST ID %d)\n",
-                    (void*)job, (char*)o->ptr, job->type, i);
+            if (job->id == o) {
+                redisLog(REDIS_DEBUG,"*** CANCELED %p (key %s) (type %d) (LIST ID %d)\n",
+                    (void*)job, (char*)job->key->ptr, job->type, i);
                 /* Mark the pages as free since the swap didn't happened
                  * or happened but is now discarded. */
                 if (i != 1 && job->type == REDIS_IOJOB_DO_SWAP)
@@ -9616,12 +9669,14 @@ static void vmCancelThreadedIOJob(robj *o) {
                 else if (o->storage == REDIS_VM_SWAPPING)
                     o->storage = REDIS_VM_MEMORY;
                 unlockThreadedIO();
+                redisLog(REDIS_DEBUG,"*** DONE");
                 return;
             }
         }
     }
     unlockThreadedIO();
-    assert(1 != 1); /* We should never reach this */
+    printf("Not found: %p\n", (void*)o);
+    redisAssert(1 != 1); /* We should never reach this */
 }
 
 static void *IOThreadEntryPoint(void *arg) {
@@ -9654,7 +9709,8 @@ static void *IOThreadEntryPoint(void *arg) {
 
         /* Process the Job */
         if (j->type == REDIS_IOJOB_LOAD) {
-            j->val = vmReadObjectFromSwap(j->page,j->key->vtype);
+            vmpointer *vp = (vmpointer*)j->id;
+            j->val = vmReadObjectFromSwap(j->page,vp->vtype);
         } else if (j->type == REDIS_IOJOB_PREPARE_SWAP) {
             FILE *fp = fopen("/dev/null","w+");
             j->pages = rdbSavedObjectPages(j->val,fp);
@@ -9750,18 +9806,16 @@ static void queueIOJob(iojob *j) {
 static int vmSwapObjectThreaded(robj *key, robj *val, redisDb *db) {
     iojob *j;
 
-    assert(key->storage == REDIS_VM_MEMORY);
-    assert(key->refcount == 1);
-
     j = zmalloc(sizeof(*j));
     j->type = REDIS_IOJOB_PREPARE_SWAP;
     j->db = db;
     j->key = key;
-    j->val = val;
+    incrRefCount(key);
+    j->id = j->val = val;
     incrRefCount(val);
     j->canceled = 0;
     j->thread = (pthread_t) -1;
-    key->storage = REDIS_VM_SWAPPING;
+    val->storage = REDIS_VM_SWAPPING;
 
     lockThreadedIO();
     queueIOJob(j);
@@ -9783,9 +9837,9 @@ static int waitForSwappedKey(redisClient *c, robj *key) {
 
     /* If the key does not exist or is already in RAM we don't need to
      * block the client at all. */
-    de = dictFind(c->db->dict,key);
+    de = dictFind(c->db->dict,key->ptr);
     if (de == NULL) return 0;
-    o = dictGetEntryKey(de);
+    o = dictGetEntryVal(de);
     if (o->storage == REDIS_VM_MEMORY) {
         return 0;
     } else if (o->storage == REDIS_VM_SWAPPING) {
@@ -9819,14 +9873,16 @@ static int waitForSwappedKey(redisClient *c, robj *key) {
     /* Are we already loading the key from disk? If not create a job */
     if (o->storage == REDIS_VM_SWAPPED) {
         iojob *j;
+        vmpointer *vp = (vmpointer*)o;
 
         o->storage = REDIS_VM_LOADING;
         j = zmalloc(sizeof(*j));
         j->type = REDIS_IOJOB_LOAD;
         j->db = c->db;
-        j->key = o;
-        j->key->vtype = o->vtype;
-        j->page = o->vm.page;
+        j->id = (robj*)vp;
+        j->key = key;
+        incrRefCount(key);
+        j->page = vp->page;
         j->val = NULL;
         j->canceled = 0;
         j->thread = (pthread_t) -1;
@@ -9951,6 +10007,8 @@ static int dontWaitForSwappedKey(redisClient *c, robj *key) {
     return listLength(c->io_keys) == 0;
 }
 
+/* Every time we now a key was loaded back in memory, we handle clients
+ * waiting for this key if any. */
 static void handleClientsBlockedOnSwappedKey(redisDb *db, robj *key) {
     struct dictEntry *de;
     list *l;
@@ -10569,7 +10627,7 @@ static void touchWatchedKeysOnFlush(int dbid) {
              * key exists, mark the client as dirty, as the key will be
              * removed. */
             if (dbid == -1 || wk->db->id == dbid) {
-                if (dictFind(wk->db->dict, wk->key) != NULL)
+                if (dictFind(wk->db->dict, wk->key->ptr) != NULL)
                     c->flags |= REDIS_DIRTY_CAS;
             }
         }
@@ -10680,27 +10738,22 @@ static void computeDatasetDigest(unsigned char *final) {
 
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
@@ -10769,6 +10822,7 @@ static void computeDatasetDigest(unsigned char *final) {
             if (expiretime != -1) xorDigest(digest,"!!expire!!",10);
             /* We can finally xor the key-val digest to the final digest */
             xorDigest(final,digest,20);
+            decrRefCount(keyobj);
         }
         dictReleaseIterator(di);
     }
@@ -10798,17 +10852,16 @@ static void debugCommand(redisClient *c) {
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
-        if (!server.vm_enabled || (key->storage == REDIS_VM_MEMORY ||
-                                   key->storage == REDIS_VM_SWAPPING)) {
+        if (!server.vm_enabled || (val->storage == REDIS_VM_MEMORY ||
+                                   val->storage == REDIS_VM_SWAPPING)) {
             char *strenc;
             char buf[128];
 
@@ -10819,23 +10872,25 @@ static void debugCommand(redisClient *c) {
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
+            vmpointer *vp = (vmpointer*) val;
             addReplySds(c,sdscatprintf(sdsempty(),
-                "+Key at:%p refcount:%d, value swapped at: page %llu "
+                "+Value swapped at: page %llu "
                 "using %llu pages\r\n",
-                (void*)key, key->refcount, (unsigned long long) key->vm.page,
-                (unsigned long long) key->vm.usedpages));
+                (unsigned long long) vp->page,
+                (unsigned long long) vp->usedpages));
         }
     } else if (!strcasecmp(c->argv[1]->ptr,"swapin") && c->argc == 3) {
         lookupKeyRead(c->db,c->argv[2]);
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"swapout") && c->argc == 3) {
-        dictEntry *de = dictFind(c->db->dict,c->argv[2]);
-        robj *key, *val;
+        dictEntry *de = dictFind(c->db->dict,c->argv[2]->ptr);
+        robj *val;
+        vmpointer *vp;
 
         if (!server.vm_enabled) {
             addReplySds(c,sdsnew("-ERR Virtual Memory is disabled\r\n"));
@@ -10845,19 +10900,14 @@ static void debugCommand(redisClient *c) {
             addReply(c,shared.nokeyerr);
             return;
         }
-        key = dictGetEntryKey(de);
         val = dictGetEntryVal(de);
-        /* If the key is shared we want to create a copy */
-        if (key->refcount > 1) {
-            robj *newkey = dupStringObject(key);
-            decrRefCount(key);
-            key = dictGetEntryKey(de) = newkey;
-        }
         /* Swap it */
-        if (key->storage != REDIS_VM_MEMORY) {
+        if (val->storage != REDIS_VM_MEMORY) {
             addReplySds(c,sdsnew("-ERR This key is not in memory\r\n"));
-        } else if (vmSwapObjectBlocking(key,val) == REDIS_OK) {
-            dictGetEntryVal(de) = NULL;
+        } else if (val->refcount != 1) {
+            addReplySds(c,sdsnew("-ERR Object is shared\r\n"));
+        } else if ((vp = vmSwapObjectBlocking(val)) != NULL) {
+            dictGetEntryVal(de) = vp;
             addReply(c,shared.ok);
         } else {
             addReply(c,shared.err);
@@ -10878,7 +10928,8 @@ static void debugCommand(redisClient *c) {
             }
             snprintf(buf,sizeof(buf),"value:%lu",j);
             val = createStringObject(buf,strlen(buf));
-            dictAdd(c->db->dict,key,val);
+            dbAdd(c->db,key,val);
+            decrRefCount(key);
         }
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"digest") && c->argc == 2) {