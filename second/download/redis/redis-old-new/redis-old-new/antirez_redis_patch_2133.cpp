@@ -705,6 +705,7 @@ static void substrCommand(redisClient *c);
 static void zrankCommand(redisClient *c);
 static void zrevrankCommand(redisClient *c);
 static void hsetCommand(redisClient *c);
+static void hsetnxCommand(redisClient *c);
 static void hgetCommand(redisClient *c);
 static void hmsetCommand(redisClient *c);
 static void hmgetCommand(redisClient *c);
@@ -783,6 +784,7 @@ static struct redisCommand cmdTable[] = {
     {"zrank",zrankCommand,3,REDIS_CMD_BULK,NULL,1,1,1},
     {"zrevrank",zrevrankCommand,3,REDIS_CMD_BULK,NULL,1,1,1},
     {"hset",hsetCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"hsetnx",hsetnxCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
     {"hget",hgetCommand,3,REDIS_CMD_BULK,NULL,1,1,1},
     {"hmset",hmsetCommand,-4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
     {"hmget",hmgetCommand,-3,REDIS_CMD_BULK,NULL,1,1,1},
@@ -6042,325 +6044,332 @@ static void zrevrankCommand(redisClient *c) {
     zrankGenericCommand(c, 1);
 }
 
-/* =================================== Hashes =============================== */
-static void hsetCommand(redisClient *c) {
-    int update = 0;
-    robj *o = lookupKeyWrite(c->db,c->argv[1]);
+/* ========================= Hashes utility functions ======================= */
+#define REDIS_HASH_KEY 1
+#define REDIS_HASH_VALUE 2
 
-    if (o == NULL) {
-        o = createHashObject();
-        dictAdd(c->db->dict,c->argv[1],o);
-        incrRefCount(c->argv[1]);
-    } else {
-        if (o->type != REDIS_HASH) {
-            addReply(c,shared.wrongtypeerr);
+/* Check the length of a number of objects to see if we need to convert a
+ * zipmap to a real hash. Note that we only check string encoded objects
+ * as their string length can be queried in constant time. */
+static void hashTryConversion(robj *subject, robj **argv, int start, int end) {
+    int i;
+    if (subject->encoding != REDIS_ENCODING_ZIPMAP) return;
+
+    for (i = start; i <= end; i++) {
+        if (argv[i]->encoding == REDIS_ENCODING_RAW &&
+            sdslen(argv[i]->ptr) > server.hash_max_zipmap_value)
+        {
+            convertToRealHash(subject);
             return;
         }
     }
-    /* We want to convert the zipmap into an hash table right now if the
-     * entry to be added is too big. Note that we check if the object
-     * is integer encoded before to try fetching the length in the test below.
-     * This is because integers are small, but currently stringObjectLen()
-     * performs a slow conversion: not worth it. */
-    if (o->encoding == REDIS_ENCODING_ZIPMAP &&
-        ((c->argv[2]->encoding == REDIS_ENCODING_RAW &&
-          sdslen(c->argv[2]->ptr) > server.hash_max_zipmap_value) ||
-         (c->argv[3]->encoding == REDIS_ENCODING_RAW &&
-          sdslen(c->argv[3]->ptr) > server.hash_max_zipmap_value)))
-    {
-        convertToRealHash(o);
+}
+
+/* Get the value from a hash identified by key. Returns either a string
+ * object or NULL if the value cannot be found. The refcount of the object
+ * is always increased by 1 when the value was found. */
+static robj *hashGet(robj *o, robj *key) {
+    robj *value = NULL;
+    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
+        unsigned char *v;
+        unsigned int vlen;
+        key = getDecodedObject(key);
+        if (zipmapGet(o->ptr,key->ptr,sdslen(key->ptr),&v,&vlen)) {
+            value = createStringObject((char*)v,vlen);
+        }
+        decrRefCount(key);
+    } else {
+        dictEntry *de = dictFind(o->ptr,key);
+        if (de != NULL) {
+            value = dictGetEntryVal(de);
+            incrRefCount(value);
+        }
     }
+    return value;
+}
 
+/* Test if the key exists in the given hash. Returns 1 if the key
+ * exists and 0 when it doesn't. */
+static int hashExists(robj *o, robj *key) {
     if (o->encoding == REDIS_ENCODING_ZIPMAP) {
-        unsigned char *zm = o->ptr;
-        robj *valobj = getDecodedObject(c->argv[3]);
+        key = getDecodedObject(key);
+        if (zipmapExists(o->ptr,key->ptr,sdslen(key->ptr))) {
+            decrRefCount(key);
+            return 1;
+        }
+        decrRefCount(key);
+    } else {
+        if (dictFind(o->ptr,key) != NULL) {
+            return 1;
+        }
+    }
+    return 0;
+}
 
-        zm = zipmapSet(zm,c->argv[2]->ptr,sdslen(c->argv[2]->ptr),
-            valobj->ptr,sdslen(valobj->ptr),&update);
-        decrRefCount(valobj);
-        o->ptr = zm;
+/* Add an element, discard the old if the key already exists.
+ * Return 0 on insert and 1 on update. */
+static int hashSet(robj *o, robj *key, robj *value) {
+    int update = 0;
+    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
+        key = getDecodedObject(key);
+        value = getDecodedObject(value);
+        o->ptr = zipmapSet(o->ptr,
+            key->ptr,sdslen(key->ptr),
+            value->ptr,sdslen(value->ptr), &update);
+        decrRefCount(key);
+        decrRefCount(value);
 
-        /* And here there is the second check for hash conversion. */
-        if (zipmapLen(zm) > server.hash_max_zipmap_entries)
+        /* Check if the zipmap needs to be upgraded to a real hash table */
+        if (zipmapLen(o->ptr) > server.hash_max_zipmap_entries)
             convertToRealHash(o);
     } else {
-        c->argv[2] = tryObjectEncoding(c->argv[2]);
-        /* note that c->argv[3] is already encoded, as the latest arg
-         * of a bulk command is always integer encoded if possible. */
-        if (dictReplace(o->ptr,c->argv[2],c->argv[3])) {
-            incrRefCount(c->argv[2]);
+        value = tryObjectEncoding(value);
+        if (dictReplace(o->ptr,key,value)) {
+            /* Insert */
+            incrRefCount(key);
         } else {
+            /* Update */
             update = 1;
         }
-        incrRefCount(c->argv[3]);
+        incrRefCount(value);
     }
-    server.dirty++;
-    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",update == 0));
+    return update;
 }
 
-static void hmsetCommand(redisClient *c) {
-    int i;
-    robj *o, *key, *val;
-
-    if ((c->argc % 2) == 1) {
-        addReplySds(c,sdsnew("-ERR wrong number of arguments for HMSET\r\n"));
-        return;
+/* Delete an element from a hash.
+ * Return 1 on deleted and 0 on not found. */
+static int hashDelete(robj *o, robj *key) {
+    int deleted = 0;
+    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
+        key = getDecodedObject(key);
+        o->ptr = zipmapDel(o->ptr,key->ptr,sdslen(key->ptr), &deleted);
+        decrRefCount(key);
+    } else {
+        deleted = dictDelete((dict*)o->ptr,key) == DICT_OK;
+        /* Always check if the dictionary needs a resize after a delete. */
+        if (deleted && htNeedsResize(o->ptr)) dictResize(o->ptr);
     }
+    return deleted;
+}
 
-    if ((o = lookupKeyWrite(c->db,c->argv[1])) == NULL) {
-        o = createHashObject();
-        dictAdd(c->db->dict,c->argv[1],o);
-        incrRefCount(c->argv[1]);
+/* Return the number of elements in a hash. */
+static unsigned long hashLength(robj *o) {
+    return (o->encoding == REDIS_ENCODING_ZIPMAP) ?
+        zipmapLen((unsigned char*)o->ptr) : dictSize((dict*)o->ptr);
+}
+
+/* Structure to hold hash iteration abstration. Note that iteration over
+ * hashes involves both fields and values. Because it is possible that
+ * not both are required, store pointers in the iterator to avoid
+ * unnecessary memory allocation for fields/values. */
+typedef struct {
+    int encoding;
+    unsigned char *zi;
+    unsigned char *zk, *zv;
+    unsigned int zklen, zvlen;
+
+    dictIterator *di;
+    dictEntry *de;
+} hashIterator;
+
+static hashIterator *hashInitIterator(robj *subject) {
+    hashIterator *hi = zmalloc(sizeof(hashIterator));
+    hi->encoding = subject->encoding;
+    if (hi->encoding == REDIS_ENCODING_ZIPMAP) {
+        hi->zi = zipmapRewind(subject->ptr);
+    } else if (hi->encoding == REDIS_ENCODING_HT) {
+        hi->di = dictGetIterator(subject->ptr);
     } else {
-        if (o->type != REDIS_HASH) {
-            addReply(c,shared.wrongtypeerr);
-            return;
-        }
+        redisAssert(NULL);
     }
+    return hi;
+}
 
-    /* We want to convert the zipmap into an hash table right now if the
-     * entry to be added is too big. */
-    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
-        for (i = 2; i < c->argc; i+=2) {
-            if ((c->argv[i]->encoding == REDIS_ENCODING_RAW &&
-                  sdslen(c->argv[i]->ptr) > server.hash_max_zipmap_value) ||
-                (c->argv[i+1]->encoding == REDIS_ENCODING_RAW &&
-                  sdslen(c->argv[i+1]->ptr) > server.hash_max_zipmap_value)) {
-                convertToRealHash(o);
-                break;
-            }
-        }
+static void hashReleaseIterator(hashIterator *hi) {
+    if (hi->encoding == REDIS_ENCODING_HT) {
+        dictReleaseIterator(hi->di);
     }
+    zfree(hi);
+}
 
-    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
-        unsigned char *zm = o->ptr;
+/* Move to the next entry in the hash. Return REDIS_OK when the next entry
+ * could be found and REDIS_ERR when the iterator reaches the end. */
+static int hashNext(hashIterator *hi) {
+    if (hi->encoding == REDIS_ENCODING_ZIPMAP) {
+        if ((hi->zi = zipmapNext(hi->zi, &hi->zk, &hi->zklen,
+            &hi->zv, &hi->zvlen)) == NULL) return REDIS_ERR;
+    } else {
+        if ((hi->de = dictNext(hi->di)) == NULL) return REDIS_ERR;
+    }
+    return REDIS_OK;
+}
 
-        for (i = 2; i < c->argc; i+=2) {
-            key = getDecodedObject(c->argv[i]);
-            val = getDecodedObject(c->argv[i+1]);
-            zm = zipmapSet(zm,key->ptr,sdslen(key->ptr),
-                              val->ptr,sdslen(val->ptr),NULL);
-            decrRefCount(key);
-            decrRefCount(val);
-            o->ptr = zm;
+/* Get key or value object at current iteration position.
+ * This increases the refcount of the field object by 1. */
+static robj *hashCurrent(hashIterator *hi, int what) {
+    robj *o;
+    if (hi->encoding == REDIS_ENCODING_ZIPMAP) {
+        if (what & REDIS_HASH_KEY) {
+            o = createStringObject((char*)hi->zk,hi->zklen);
+        } else {
+            o = createStringObject((char*)hi->zv,hi->zvlen);
         }
-
-        /* And here there is the second check for hash conversion. */
-        if (zipmapLen(zm) > server.hash_max_zipmap_entries)
-            convertToRealHash(o);
     } else {
-        for (i = 2; i < c->argc; i+=2) {
-            key = tryObjectEncoding(c->argv[i]);
-            val = tryObjectEncoding(c->argv[i+1]);
-            if (dictReplace(o->ptr,key,val)) {
-                incrRefCount(key);
-            }
-            incrRefCount(val);
+        if (what & REDIS_HASH_KEY) {
+            o = dictGetEntryKey(hi->de);
+        } else {
+            o = dictGetEntryVal(hi->de);
         }
+        incrRefCount(o);
     }
-
-    addReply(c, shared.ok);
+    return o;
 }
 
-static void hincrbyCommand(redisClient *c) {
-    long long value = 0, incr = 0;
-    robj *o = lookupKeyWrite(c->db,c->argv[1]);
-
+static robj *hashLookupWriteOrCreate(redisClient *c, robj *key) {
+    robj *o = lookupKeyWrite(c->db,key);
     if (o == NULL) {
         o = createHashObject();
-        dictAdd(c->db->dict,c->argv[1],o);
-        incrRefCount(c->argv[1]);
+        dictAdd(c->db->dict,key,o);
+        incrRefCount(key);
     } else {
         if (o->type != REDIS_HASH) {
             addReply(c,shared.wrongtypeerr);
-            return;
+            return NULL;
         }
     }
+    return o;
+}
 
-    if (getLongLongFromObject(c, c->argv[3], &incr) != REDIS_OK) return;
+/* ============================= Hash commands ============================== */
+static void hsetCommand(redisClient *c) {
+    int update;
+    robj *o;
 
-    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
-        unsigned char *zm = o->ptr;
-        unsigned char *zval;
-        unsigned int zvlen;
-
-        /* Find value if already present in hash */
-        if (zipmapGet(zm,c->argv[2]->ptr,sdslen(c->argv[2]->ptr),
-            &zval,&zvlen)) {
-            /* strtoll needs the char* to have a trailing \0, but
-             * the zipmap doesn't include them. */
-            sds szval = sdsnewlen(zval, zvlen);
-            value = strtoll(szval,NULL,10);
-            sdsfree(szval);
-        }
-
-        value += incr;
-        sds svalue = sdscatprintf(sdsempty(),"%lld",value);
-        zm = zipmapSet(zm,c->argv[2]->ptr,sdslen(c->argv[2]->ptr),
-            (unsigned char*)svalue,sdslen(svalue),NULL);
-        sdsfree(svalue);
-        o->ptr = zm;
-
-        /* Check if the zipmap needs to be converted. */
-        if (zipmapLen(zm) > server.hash_max_zipmap_entries)
-            convertToRealHash(o);
+    if ((o = hashLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
+    hashTryConversion(o,c->argv,2,3);
+    update = hashSet(o,c->argv[2],c->argv[3]);
+    addReply(c, update ? shared.czero : shared.cone);
+    server.dirty++;
+}
+
+static void hsetnxCommand(redisClient *c) {
+    robj *o;
+    if ((o = hashLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
+    hashTryConversion(o,c->argv,2,3);
+
+    if (hashExists(o, c->argv[2])) {
+        addReply(c, shared.czero);
     } else {
-        robj *hval;
-        dictEntry *de;
+        hashSet(o,c->argv[2],c->argv[3]);
+        addReply(c, shared.cone);
+        server.dirty++;
+    }
+}
 
-        /* Find value if already present in hash */
-        de = dictFind(o->ptr,c->argv[2]);
-        if (de != NULL) {
-            hval = dictGetEntryVal(de);
-            if (hval->encoding == REDIS_ENCODING_RAW)
-                value = strtoll(hval->ptr,NULL,10);
-            else if (hval->encoding == REDIS_ENCODING_INT)
-                value = (long)hval->ptr;
-            else
-                redisAssert(1 != 1);
-        }
+static void hmsetCommand(redisClient *c) {
+    int i;
+    robj *o;
 
-        value += incr;
-        hval = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
-        hval = tryObjectEncoding(hval);
-        if (dictReplace(o->ptr,c->argv[2],hval)) {
-            incrRefCount(c->argv[2]);
-        }
+    if ((c->argc % 2) == 1) {
+        addReplySds(c,sdsnew("-ERR wrong number of arguments for HMSET\r\n"));
+        return;
     }
 
+    if ((o = hashLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
+    hashTryConversion(o,c->argv,2,c->argc-1);
+    for (i = 2; i < c->argc; i += 2) {
+        hashSet(o,c->argv[i],c->argv[i+1]);
+    }
+    addReply(c, shared.ok);
+}
+
+static void hincrbyCommand(redisClient *c) {
+    long long value, incr;
+    robj *o, *current, *new;
+
+    if (getLongLongFromObject(c,c->argv[3],&incr) != REDIS_OK) return;
+    if ((o = hashLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
+    if ((current = hashGet(o,c->argv[2])) != NULL) {
+        if (current->encoding == REDIS_ENCODING_RAW)
+            value = strtoll(current->ptr,NULL,10);
+        else if (current->encoding == REDIS_ENCODING_INT)
+            value = (long)current->ptr;
+        else
+            redisAssert(1 != 1);
+        decrRefCount(current);
+    } else {
+        value = 0;
+    }
+
+    value += incr;
+    new = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
+    hashSet(o,c->argv[2],new);
+    decrRefCount(new);
+    addReplyLongLong(c,value);
     server.dirty++;
-    addReplyLongLong(c, value);
 }
 
 static void hgetCommand(redisClient *c) {
-    robj *o;
-
+    robj *o, *value;
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
         checkType(c,o,REDIS_HASH)) return;
 
-    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
-        unsigned char *zm = o->ptr;
-        unsigned char *val;
-        unsigned int vlen;
-        robj *field;
-
-        field = getDecodedObject(c->argv[2]);
-        if (zipmapGet(zm,field->ptr,sdslen(field->ptr), &val,&vlen)) {
-            addReplySds(c,sdscatprintf(sdsempty(),"$%u\r\n", vlen));
-            addReplySds(c,sdsnewlen(val,vlen));
-            addReply(c,shared.crlf);
-            decrRefCount(field);
-            return;
-        } else {
-            addReply(c,shared.nullbulk);
-            decrRefCount(field);
-            return;
-        }
+    if ((value = hashGet(o,c->argv[2])) != NULL) {
+        addReplyBulk(c,value);
+        decrRefCount(value);
     } else {
-        struct dictEntry *de;
-
-        de = dictFind(o->ptr,c->argv[2]);
-        if (de == NULL) {
-            addReply(c,shared.nullbulk);
-        } else {
-            robj *e = dictGetEntryVal(de);
-
-            addReplyBulk(c,e);
-        }
+        addReply(c,shared.nullbulk);
     }
 }
 
 static void hmgetCommand(redisClient *c) {
     int i;
-
-    robj *o = lookupKeyRead(c->db, c->argv[1]);
-    if (o == NULL) {
-        addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->argc-2));
-        for (i = 2; i < c->argc; i++) {
-            addReply(c,shared.nullbulk);
-        }
-        return;
-    } else {
-        if (o->type != REDIS_HASH) {
-            addReply(c,shared.wrongtypeerr);
-            return;
-        }
+    robj *o, *value;
+    o = lookupKeyRead(c->db,c->argv[1]);
+    if (o != NULL && o->type != REDIS_HASH) {
+        addReply(c,shared.wrongtypeerr);
     }
 
+    /* Note the check for o != NULL happens inside the loop. This is
+     * done because objects that cannot be found are considered to be
+     * an empty hash. The reply should then be a series of NULLs. */
     addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->argc-2));
-    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
-        unsigned char *zm = o->ptr;
-        unsigned char *v;
-        unsigned int vlen;
-        robj *field;
-
-        for (i = 2; i < c->argc; i++) {
-            field = getDecodedObject(c->argv[i]);
-            if (zipmapGet(zm,field->ptr,sdslen(field->ptr),&v,&vlen)) {
-                addReplySds(c,sdscatprintf(sdsempty(),"$%u\r\n", vlen));
-                addReplySds(c,sdsnewlen(v,vlen));
-                addReply(c,shared.crlf);
-            } else {
-                addReply(c,shared.nullbulk);
-            }
-            decrRefCount(field);
-        }
-    } else {
-        dictEntry *de;
-
-        for (i = 2; i < c->argc; i++) {
-            de = dictFind(o->ptr,c->argv[i]);
-            if (de != NULL) {
-                addReplyBulk(c,(robj*)dictGetEntryVal(de));
-            } else {
-                addReply(c,shared.nullbulk);
-            }
+    for (i = 2; i < c->argc; i++) {
+        if (o != NULL && (value = hashGet(o,c->argv[i])) != NULL) {
+            addReplyBulk(c,value);
+            decrRefCount(value);
+        } else {
+            addReply(c,shared.nullbulk);
         }
     }
 }
 
 static void hdelCommand(redisClient *c) {
     robj *o;
-    int deleted = 0;
-
     if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,o,REDIS_HASH)) return;
 
-    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
-        robj *field = getDecodedObject(c->argv[2]);
-
-        o->ptr = zipmapDel((unsigned char*) o->ptr,
-            (unsigned char*) field->ptr,
-            sdslen(field->ptr), &deleted);
-        decrRefCount(field);
-        if (zipmapLen((unsigned char*) o->ptr) == 0)
-            deleteKey(c->db,c->argv[1]);
+    if (hashDelete(o,c->argv[2])) {
+        if (hashLength(o) == 0) deleteKey(c->db,c->argv[1]);
+        addReply(c,shared.cone);
+        server.dirty++;
     } else {
-        deleted = dictDelete((dict*)o->ptr,c->argv[2]) == DICT_OK;
-        if (htNeedsResize(o->ptr)) dictResize(o->ptr);
-        if (dictSize((dict*)o->ptr) == 0) deleteKey(c->db,c->argv[1]);
+        addReply(c,shared.czero);
     }
-    if (deleted) server.dirty++;
-    addReply(c,deleted ? shared.cone : shared.czero);
 }
 
 static void hlenCommand(redisClient *c) {
     robj *o;
-    unsigned long len;
-
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,o,REDIS_HASH)) return;
 
-    len = (o->encoding == REDIS_ENCODING_ZIPMAP) ?
-            zipmapLen((unsigned char*)o->ptr) : dictSize((dict*)o->ptr);
-    addReplyUlong(c,len);
+    addReplyUlong(c,hashLength(o));
 }
 
-#define REDIS_GETALL_KEYS 1
-#define REDIS_GETALL_VALS 2
 static void genericHgetallCommand(redisClient *c, int flags) {
-    robj *o, *lenobj;
+    robj *o, *lenobj, *obj;
     unsigned long count = 0;
+    hashIterator *hi;
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk)) == NULL
         || checkType(c,o,REDIS_HASH)) return;
@@ -6369,79 +6378,44 @@ static void genericHgetallCommand(redisClient *c, int flags) {
     addReply(c,lenobj);
     decrRefCount(lenobj);
 
-    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
-        unsigned char *p = zipmapRewind(o->ptr);
-        unsigned char *field, *val;
-        unsigned int flen, vlen;
-
-        while((p = zipmapNext(p,&field,&flen,&val,&vlen)) != NULL) {
-            robj *aux;
-
-            if (flags & REDIS_GETALL_KEYS) {
-                aux = createStringObject((char*)field,flen);
-                addReplyBulk(c,aux);
-                decrRefCount(aux);
-                count++;
-            }
-            if (flags & REDIS_GETALL_VALS) {
-                aux = createStringObject((char*)val,vlen);
-                addReplyBulk(c,aux);
-                decrRefCount(aux);
-                count++;
-            }
+    hi = hashInitIterator(o);
+    while (hashNext(hi) != REDIS_ERR) {
+        if (flags & REDIS_HASH_KEY) {
+            obj = hashCurrent(hi,REDIS_HASH_KEY);
+            addReplyBulk(c,obj);
+            decrRefCount(obj);
+            count++;
         }
-    } else {
-        dictIterator *di = dictGetIterator(o->ptr);
-        dictEntry *de;
-
-        while((de = dictNext(di)) != NULL) {
-            robj *fieldobj = dictGetEntryKey(de);
-            robj *valobj = dictGetEntryVal(de);
-
-            if (flags & REDIS_GETALL_KEYS) {
-                addReplyBulk(c,fieldobj);
-                count++;
-            }
-            if (flags & REDIS_GETALL_VALS) {
-                addReplyBulk(c,valobj);
-                count++;
-            }
+        if (flags & REDIS_HASH_VALUE) {
+            obj = hashCurrent(hi,REDIS_HASH_VALUE);
+            addReplyBulk(c,obj);
+            decrRefCount(obj);
+            count++;
         }
-        dictReleaseIterator(di);
     }
+    hashReleaseIterator(hi);
+
     lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",count);
 }
 
 static void hkeysCommand(redisClient *c) {
-    genericHgetallCommand(c,REDIS_GETALL_KEYS);
+    genericHgetallCommand(c,REDIS_HASH_KEY);
 }
 
 static void hvalsCommand(redisClient *c) {
-    genericHgetallCommand(c,REDIS_GETALL_VALS);
+    genericHgetallCommand(c,REDIS_HASH_VALUE);
 }
 
 static void hgetallCommand(redisClient *c) {
-    genericHgetallCommand(c,REDIS_GETALL_KEYS|REDIS_GETALL_VALS);
+    genericHgetallCommand(c,REDIS_HASH_KEY|REDIS_HASH_VALUE);
 }
 
 static void hexistsCommand(redisClient *c) {
     robj *o;
-    int exists = 0;
-
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,o,REDIS_HASH)) return;
 
-    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
-        robj *field;
-        unsigned char *zm = o->ptr;
-
-        field = getDecodedObject(c->argv[2]);
-        exists = zipmapExists(zm,field->ptr,sdslen(field->ptr));
-        decrRefCount(field);
-    } else {
-        exists = dictFind(o->ptr,c->argv[2]) != NULL;
-    }
-    addReply(c,exists ? shared.cone : shared.czero);
+    addReply(c, hashExists(o,c->argv[2]) ? shared.cone : shared.czero);
 }
 
 static void convertToRealHash(robj *o) {
@@ -6495,16 +6469,16 @@ static redisSortOperation *createSortOperation(int type, robj *pattern) {
 /* Return the value associated to the key with a name obtained
  * substituting the first occurence of '*' in 'pattern' with 'subst' */
 static robj *lookupKeyByPattern(redisDb *db, robj *pattern, robj *subst) {
-    char *p;
+    char *p, *f;
     sds spat, ssub;
-    robj keyobj;
-    int prefixlen, sublen, postfixlen;
+    robj keyobj, fieldobj, *o;
+    int prefixlen, sublen, postfixlen, fieldlen;
     /* Expoit the internal sds representation to create a sds string allocated on the stack in order to make this function faster */
     struct {
         long len;
         long free;
         char buf[REDIS_SORTKEY_MAX+1];
-    } keyname;
+    } keyname, fieldname;
 
     /* If the pattern is "#" return the substitution object itself in order
      * to implement the "SORT ... GET #" feature. */
@@ -6526,20 +6500,49 @@ static robj *lookupKeyByPattern(redisDb *db, robj *pattern, robj *subst) {
         return NULL;
     }
 
+    /* Find out if we're dealing with a hash dereference. */
+    if ((f = strstr(p+1, "->")) != NULL) {
+        fieldlen = sdslen(spat)-(f-spat);
+        /* this also copies \0 character */
+        memcpy(fieldname.buf,f+2,fieldlen-1);
+        fieldname.len = fieldlen-2;
+    } else {
+        fieldlen = 0;
+    }
+
     prefixlen = p-spat;
     sublen = sdslen(ssub);
-    postfixlen = sdslen(spat)-(prefixlen+1);
+    postfixlen = sdslen(spat)-(prefixlen+1)-fieldlen;
     memcpy(keyname.buf,spat,prefixlen);
     memcpy(keyname.buf+prefixlen,ssub,sublen);
     memcpy(keyname.buf+prefixlen+sublen,p+1,postfixlen);
     keyname.buf[prefixlen+sublen+postfixlen] = '\0';
     keyname.len = prefixlen+sublen+postfixlen;
-
-    initStaticStringObject(keyobj,((char*)&keyname)+(sizeof(long)*2))
     decrRefCount(subst);
 
-    /* printf("lookup '%s' => %p\n", keyname.buf,de); */
-    return lookupKeyRead(db,&keyobj);
+    /* Lookup substituted key */
+    initStaticStringObject(keyobj,((char*)&keyname)+(sizeof(long)*2));
+    o = lookupKeyRead(db,&keyobj);
+
+    if (o != NULL && fieldlen > 0) {
+        /* Retrieve value from hash by the field name. This operation
+         * already increases the refcount of the returned object. */
+        if (o->type != REDIS_HASH || fieldname.len < 1) {
+            return NULL;
+        }
+        initStaticStringObject(fieldobj,((char*)&fieldname)+(sizeof(long)*2));
+        o = hashGet(o, &fieldobj);
+    } else {
+        if (o->type != REDIS_STRING) {
+            return NULL;
+        }
+
+        /* Every object that this function returns needs to have its refcount
+         * increased. sortCommand decreases it again. */
+        incrRefCount(o);
+    }
+
+    return o;
 }
 
 /* sortCompare() is used by qsort in sortCommand(). Given that qsort_r with
@@ -6574,14 +6577,9 @@ static int sortCompare(const void *s1, const void *s2) {
                 cmp = strcoll(so1->u.cmpobj->ptr,so2->u.cmpobj->ptr);
             }
         } else {
-            /* Compare elements directly */
-            robj *dec1, *dec2;
-
-            dec1 = getDecodedObject(so1->obj);
-            dec2 = getDecodedObject(so2->obj);
-            cmp = strcoll(dec1->ptr,dec2->ptr);
-            decrRefCount(dec1);
-            decrRefCount(dec2);
+            /* Compare elements directly. Note that these objects already
+             * need to be non-encoded (see sortCommand). */
+            cmp = strcoll(so1->obj->ptr,so2->obj->ptr);
         }
     }
     return server.sort_desc ? -cmp : cmp;
@@ -6708,38 +6706,36 @@ static void sortCommand(redisClient *c) {
     /* Now it's time to load the right scores in the sorting vector */
     if (dontsort == 0) {
         for (j = 0; j < vectorlen; j++) {
+            robj *byval;
             if (sortby) {
-                robj *byval;
-
+                /* lookup value to sort by */
                 byval = lookupKeyByPattern(c->db,sortby,vector[j].obj);
-                if (!byval || byval->type != REDIS_STRING) continue;
-                if (alpha) {
-                    vector[j].u.cmpobj = getDecodedObject(byval);
-                } else {
-                    if (byval->encoding == REDIS_ENCODING_RAW) {
-                        vector[j].u.score = strtod(byval->ptr,NULL);
-                    } else {
-                        /* Don't need to decode the object if it's
-                         * integer-encoded (the only encoding supported) so
-                         * far. We can just cast it */
-                        if (byval->encoding == REDIS_ENCODING_INT) {
-                            vector[j].u.score = (long)byval->ptr;
-                        } else
-                            redisAssert(1 != 1);
-                    }
-                }
+                if (!byval) continue;
             } else {
-                if (!alpha) {
-                    if (vector[j].obj->encoding == REDIS_ENCODING_RAW)
-                        vector[j].u.score = strtod(vector[j].obj->ptr,NULL);
-                    else {
-                        if (vector[j].obj->encoding == REDIS_ENCODING_INT)
-                            vector[j].u.score = (long) vector[j].obj->ptr;
-                        else
-                            redisAssert(1 != 1);
-                    }
+                /* use object itself to sort by */
+                byval = vector[j].obj;
+            }
+
+            if (alpha) {
+                vector[j].u.cmpobj = getDecodedObject(byval);
+            } else {
+                if (byval->encoding == REDIS_ENCODING_RAW) {
+                    vector[j].u.score = strtod(byval->ptr,NULL);
+                } else if (byval->encoding == REDIS_ENCODING_INT) {
+                    /* Don't need to decode the object if it's
+                     * integer-encoded (the only encoding supported) so
+                     * far. We can just cast it */
+                    vector[j].u.score = (long)byval->ptr;
+                } else {
+                    redisAssert(1 != 1);
                 }
             }
+
+            /* when the object was retrieved using lookupKeyByPattern,
+             * its refcount needs to be decreased. */
+            if (sortby) {
+                decrRefCount(byval);
+            }
         }
     }
 
@@ -6836,7 +6832,7 @@ static void sortCommand(redisClient *c) {
     decrRefCount(sortval);
     listRelease(operations);
     for (j = 0; j < vectorlen; j++) {
-        if (sortby && alpha && vector[j].u.cmpobj)
+        if (alpha && vector[j].u.cmpobj)
             decrRefCount(vector[j].u.cmpobj);
     }
     zfree(vector);