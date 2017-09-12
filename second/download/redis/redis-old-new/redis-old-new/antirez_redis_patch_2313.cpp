@@ -104,6 +104,10 @@
 #define REDIS_SET 2
 #define REDIS_HASH 3
 
+/* Objects encoding */
+#define REDIS_ENCODING_RAW 0    /* Raw representation */
+#define REDIS_ENCODING_INT 1    /* Encoded as integer */
+
 /* Object types only used for dumping to disk */
 #define REDIS_EXPIRETIME 253
 #define REDIS_SELECTDB 254
@@ -183,7 +187,9 @@
 /* A redis object, that is a type able to hold a string / list / set */
 typedef struct redisObject {
     void *ptr;
-    int type;
+    unsigned char type;
+    unsigned char encoding;
+    unsigned char notused[2];
     int refcount;
 } robj;
 
@@ -323,6 +329,8 @@ static robj *createStringObject(char *ptr, size_t len);
 static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int dictid, robj **argv, int argc);
 static int syncWithMaster(void);
 static robj *tryObjectSharing(robj *o);
+static int tryObjectEncoding(robj *o);
+static robj *getDecodedObject(const robj *o);
 static int removeExpire(redisDb *db, robj *key);
 static int expireIfNeeded(redisDb *db, robj *key);
 static int deleteIfVolatile(redisDb *db, robj *key);
@@ -634,32 +642,68 @@ static void dictRedisObjectDestructor(void *privdata, void *val)
     decrRefCount(val);
 }
 
-static int dictSdsKeyCompare(void *privdata, const void *key1,
+static int dictObjKeyCompare(void *privdata, const void *key1,
         const void *key2)
 {
     const robj *o1 = key1, *o2 = key2;
     return sdsDictKeyCompare(privdata,o1->ptr,o2->ptr);
 }
 
-static unsigned int dictSdsHash(const void *key) {
+static unsigned int dictObjHash(const void *key) {
     const robj *o = key;
     return dictGenHashFunction(o->ptr, sdslen((sds)o->ptr));
 }
 
+static int dictEncObjKeyCompare(void *privdata, const void *key1,
+        const void *key2)
+{
+    const robj *o1 = key1, *o2 = key2;
+
+    if (o1->encoding == REDIS_ENCODING_RAW &&
+        o2->encoding == REDIS_ENCODING_RAW)
+        return sdsDictKeyCompare(privdata,o1->ptr,o2->ptr);
+    else {
+        robj *dec1, *dec2;
+        int cmp;
+
+        dec1 = o1->encoding != REDIS_ENCODING_RAW ?
+            getDecodedObject(o1) : (robj*)o1;
+        dec2 = o2->encoding != REDIS_ENCODING_RAW ?
+            getDecodedObject(o2) : (robj*)o2;
+        cmp = sdsDictKeyCompare(privdata,dec1->ptr,dec2->ptr);
+        if (dec1 != o1) decrRefCount(dec1);
+        if (dec2 != o2) decrRefCount(dec2);
+        return cmp;
+    }
+}
+
+static unsigned int dictEncObjHash(const void *key) {
+    const robj *o = key;
+
+    if (o->encoding == REDIS_ENCODING_RAW)
+        return dictGenHashFunction(o->ptr, sdslen((sds)o->ptr));
+    else {
+        robj *dec = getDecodedObject(o);
+        unsigned int hash = dictGenHashFunction(dec->ptr, sdslen((sds)dec->ptr));
+        decrRefCount(dec);
+        return hash;
+    }
+}
+
 static dictType setDictType = {
-    dictSdsHash,               /* hash function */
+    dictEncObjHash,            /* hash function */
     NULL,                      /* key dup */
     NULL,                      /* val dup */
-    dictSdsKeyCompare,         /* key compare */
+    dictEncObjKeyCompare,      /* key compare */
     dictRedisObjectDestructor, /* key destructor */
     NULL                       /* val destructor */
 };
 
 static dictType hashDictType = {
-    dictSdsHash,                /* hash function */
+    dictObjHash,                /* hash function */
     NULL,                       /* key dup */
     NULL,                       /* val dup */
-    dictSdsKeyCompare,          /* key compare */
+    dictObjKeyCompare,          /* key compare */
     dictRedisObjectDestructor,  /* key destructor */
     dictRedisObjectDestructor   /* val destructor */
 };
@@ -1319,6 +1363,10 @@ static int processCommand(redisClient *c) {
         for(j = 1; j < c->argc; j++)
             c->argv[j] = tryObjectSharing(c->argv[j]);
     }
+    /* Let's try to encode the bulk object to save space. */
+    if (cmd->flags & REDIS_CMD_BULK)
+        tryObjectEncoding(c->argv[c->argc-1]);
+
     /* Check if the user is authenticated */
     if (server.requirepass && !c->authenticated && cmd->proc != authCommand) {
         addReplySds(c,sdsnew("-ERR operation not permitted\r\n"));
@@ -1560,8 +1608,12 @@ static void addReply(redisClient *c, robj *obj) {
          c->replstate == REDIS_REPL_ONLINE) &&
         aeCreateFileEvent(server.el, c->fd, AE_WRITABLE,
         sendReplyToClient, c, NULL) == AE_ERR) return;
+    if (obj->encoding != REDIS_ENCODING_RAW) {
+        obj = getDecodedObject(obj);
+    } else {
+        incrRefCount(obj);
+    }
     if (!listAddNodeTail(c->reply,obj)) oom("listAddNodeTail");
-    incrRefCount(obj);
 }
 
 static void addReplySds(redisClient *c, sds s) {
@@ -1570,6 +1622,26 @@ static void addReplySds(redisClient *c, sds s) {
     decrRefCount(o);
 }
 
+static void addReplyBulkLen(redisClient *c, robj *obj) {
+    size_t len;
+
+    if (obj->encoding == REDIS_ENCODING_RAW) {
+        len = sdslen(obj->ptr);
+    } else {
+        long n = (long)obj->ptr;
+
+        len = 1;
+        if (n < 0) {
+            len++;
+            n = -n;
+        }
+        while((n = n/10) != 0) {
+            len++;
+        }
+    }
+    addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",len));
+}
+
 static void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     int cport, cfd;
     char cip[128];
@@ -1618,6 +1690,7 @@ static robj *createObject(int type, void *ptr) {
     }
     if (!o) oom("createObject");
     o->type = type;
+    o->encoding = REDIS_ENCODING_RAW;
     o->ptr = ptr;
     o->refcount = 1;
     return o;
@@ -1642,7 +1715,9 @@ static robj *createSetObject(void) {
 }
 
 static void freeStringObject(robj *o) {
-    sdsfree(o->ptr);
+    if (o->encoding == REDIS_ENCODING_RAW) {
+        sdsfree(o->ptr);
+    }
 }
 
 static void freeListObject(robj *o) {
@@ -1686,6 +1761,36 @@ static void decrRefCount(void *obj) {
     }
 }
 
+static robj *lookupKey(redisDb *db, robj *key) {
+    dictEntry *de = dictFind(db->dict,key);
+    return de ? dictGetEntryVal(de) : NULL;
+}
+
+static robj *lookupKeyRead(redisDb *db, robj *key) {
+    expireIfNeeded(db,key);
+    return lookupKey(db,key);
+}
+
+static robj *lookupKeyWrite(redisDb *db, robj *key) {
+    deleteIfVolatile(db,key);
+    return lookupKey(db,key);
+}
+
+static int deleteKey(redisDb *db, robj *key) {
+    int retval;
+
+    /* We need to protect key from destruction: after the first dictDelete()
+     * it may happen that 'key' is no longer valid if we don't increment
+     * it's count. This may happen when we get the object reference directly
+     * from the hash table with dictRandomKey() or dict iterators */
+    incrRefCount(key);
+    if (dictSize(db->expires)) dictDelete(db->expires,key);
+    retval = dictDelete(db->dict,key);
+    decrRefCount(key);
+
+    return retval == DICT_OK;
+}
+
 /* Try to share an object against the shared objects pool */
 static robj *tryObjectSharing(robj *o) {
     struct dictEntry *de;
@@ -1731,34 +1836,54 @@ static robj *tryObjectSharing(robj *o) {
     }
 }
 
-static robj *lookupKey(redisDb *db, robj *key) {
-    dictEntry *de = dictFind(db->dict,key);
-    return de ? dictGetEntryVal(de) : NULL;
-}
+/* Try to encode a string object in order to save space */
+static int tryObjectEncoding(robj *o) {
+    long value;
+    char *endptr, buf[32];
+    sds s = o->ptr;
 
-static robj *lookupKeyRead(redisDb *db, robj *key) {
-    expireIfNeeded(db,key);
-    return lookupKey(db,key);
-}
+    if (o->encoding != REDIS_ENCODING_RAW)
+        return REDIS_ERR; /* Already encoded */
 
-static robj *lookupKeyWrite(redisDb *db, robj *key) {
-    deleteIfVolatile(db,key);
-    return lookupKey(db,key);
-}
+    /* It's not save to encode shared objects: shared objects can be shared
+     * everywhere in the "object space" of Redis. Encoded objects can only
+     * appear as "values" (and not, for instance, as keys) */
+     if (o->refcount > 1) return REDIS_ERR;
 
-static int deleteKey(redisDb *db, robj *key) {
-    int retval;
+    /* Currently we try to encode only strings */
+    assert(o->type == REDIS_STRING);
 
-    /* We need to protect key from destruction: after the first dictDelete()
-     * it may happen that 'key' is no longer valid if we don't increment
-     * it's count. This may happen when we get the object reference directly
-     * from the hash table with dictRandomKey() or dict iterators */
-    incrRefCount(key);
-    if (dictSize(db->expires)) dictDelete(db->expires,key);
-    retval = dictDelete(db->dict,key);
-    decrRefCount(key);
+    /* Check if it's possible to encode this value as a long. We are assuming
+     * that sizeof(long) = sizeof(void) in all the supported archs. */
+    value = strtol(s, &endptr, 10);
+    if (endptr[0] != '\0') return REDIS_ERR;
+    snprintf(buf,32,"%ld",value);
 
-    return retval == DICT_OK;
+    /* If the number converted back into a string is not identical
+     * then it's not possible to encode the string as integer */
+    if (strlen(buf) != sdslen(s) || memcmp(buf,s,sdslen(s))) return REDIS_ERR;
+
+    /* Ok, this object can be encoded */
+    o->encoding = REDIS_ENCODING_INT;
+    sdsfree(o->ptr);
+    o->ptr = (void*) value;
+    return REDIS_OK;
+}
+
+/* Get a decoded version of an encoded object (returned as a new object) */
+static robj *getDecodedObject(const robj *o) {
+    robj *dec;
+    
+    assert(o->encoding != REDIS_ENCODING_RAW);
+    if (o->type == REDIS_STRING && o->encoding == REDIS_ENCODING_INT) {
+        char buf[32];
+
+        snprintf(buf,32,"%ld",(long)o->ptr);
+        dec = createStringObject(buf,strlen(buf));
+        return dec;
+    } else {
+        assert(1 != 1);
+    }
 }
 
 /*============================ DB saving/loading ============================ */
@@ -1865,10 +1990,12 @@ static int rdbSaveLzfStringObject(FILE *fp, robj *obj) {
 
 /* Save a string objet as [len][data] on disk. If the object is a string
  * representation of an integer value we try to safe it in a special form */
-static int rdbSaveStringObject(FILE *fp, robj *obj) {
-    size_t len = sdslen(obj->ptr);
+static int rdbSaveStringObjectRaw(FILE *fp, robj *obj) {
+    size_t len;
     int enclen;
 
+    len = sdslen(obj->ptr);
+
     /* Try integer encoding */
     if (len <= 11) {
         unsigned char buf[5];
@@ -1880,7 +2007,7 @@ static int rdbSaveStringObject(FILE *fp, robj *obj) {
 
     /* Try LZF compression - under 20 bytes it's unable to compress even
      * aaaaaaaaaaaaaaaaaa so skip it */
-    if (1 && len > 20) {
+    if (len > 20) {
         int retval;
 
         retval = rdbSaveLzfStringObject(fp,obj);
@@ -1895,6 +2022,21 @@ static int rdbSaveStringObject(FILE *fp, robj *obj) {
     return 0;
 }
 
+/* Like rdbSaveStringObjectRaw() but handle encoded objects */
+static int rdbSaveStringObject(FILE *fp, robj *obj) {
+    int retval;
+    robj *dec;
+
+    if (obj->encoding != REDIS_ENCODING_RAW) {
+        dec = getDecodedObject(obj);
+        retval = rdbSaveStringObjectRaw(fp,dec);
+        decrRefCount(dec);
+        return retval;
+    } else {
+        return rdbSaveStringObjectRaw(fp,obj);
+    }
+}
+
 /* Save the DB on disk. Return REDIS_ERR on error, REDIS_OK on success */
 static int rdbSave(char *filename) {
     dictIterator *di = NULL;
@@ -2212,6 +2354,7 @@ static int rdbLoad(char *filename) {
         if (type == REDIS_STRING) {
             /* Read string value */
             if ((o = rdbLoadStringObject(fp,rdbver)) == NULL) goto eoferr;
+            tryObjectEncoding(o);
         } else if (type == REDIS_LIST || type == REDIS_SET) {
             /* Read list/set value */
             uint32_t listlen;
@@ -2224,6 +2367,7 @@ static int rdbLoad(char *filename) {
                 robj *ele;
 
                 if ((ele = rdbLoadStringObject(fp,rdbver)) == NULL) goto eoferr;
+                tryObjectEncoding(ele);
                 if (type == REDIS_LIST) {
                     if (!listAddNodeTail((list*)o->ptr,ele))
                         oom("listAddNodeTail");
@@ -2277,8 +2421,7 @@ static void pingCommand(redisClient *c) {
 }
 
 static void echoCommand(redisClient *c) {
-    addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",
-        (int)sdslen(c->argv[1]->ptr)));
+    addReplyBulkLen(c,c->argv[1]);
     addReply(c,c->argv[1]);
     addReply(c,shared.crlf);
 }
@@ -2323,7 +2466,7 @@ static void getCommand(redisClient *c) {
         if (o->type != REDIS_STRING) {
             addReply(c,shared.wrongtypeerr);
         } else {
-            addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",(int)sdslen(o->ptr)));
+            addReplyBulkLen(c,o);
             addReply(c,o);
             addReply(c,shared.crlf);
         }
@@ -2354,7 +2497,7 @@ static void mgetCommand(redisClient *c) {
             if (o->type != REDIS_STRING) {
                 addReply(c,shared.nullbulk);
             } else {
-                addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",(int)sdslen(o->ptr)));
+                addReplyBulkLen(c,o);
                 addReply(c,o);
                 addReply(c,shared.crlf);
             }
@@ -2376,12 +2519,18 @@ static void incrDecrCommand(redisClient *c, long long incr) {
         } else {
             char *eptr;
 
-            value = strtoll(o->ptr, &eptr, 10);
+            if (o->encoding == REDIS_ENCODING_RAW)
+                value = strtoll(o->ptr, &eptr, 10);
+            else if (o->encoding == REDIS_ENCODING_INT)
+                value = (long)o->ptr;
+            else
+                assert(1 != 1);
         }
     }
 
     value += incr;
     o = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
+    tryObjectEncoding(o);
     retval = dictAdd(c->db->dict,c->argv[1],o);
     if (retval == DICT_ERR) {
         dictReplace(c->db->dict,c->argv[1],o);
@@ -2742,7 +2891,7 @@ static void lindexCommand(redisClient *c) {
                 addReply(c,shared.nullbulk);
             } else {
                 robj *ele = listNodeValue(ln);
-                addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",(int)sdslen(ele->ptr)));
+                addReplyBulkLen(c,ele);
                 addReply(c,ele);
                 addReply(c,shared.crlf);
             }
@@ -2802,7 +2951,7 @@ static void popGenericCommand(redisClient *c, int where) {
                 addReply(c,shared.nullbulk);
             } else {
                 robj *ele = listNodeValue(ln);
-                addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",(int)sdslen(ele->ptr)));
+                addReplyBulkLen(c,ele);
                 addReply(c,ele);
                 addReply(c,shared.crlf);
                 listDelNode(list,ln);
@@ -2858,7 +3007,7 @@ static void lrangeCommand(redisClient *c) {
             addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
             for (j = 0; j < rangelen; j++) {
                 ele = listNodeValue(ln);
-                addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",(int)sdslen(ele->ptr)));
+                addReplyBulkLen(c,ele);
                 addReply(c,ele);
                 addReply(c,shared.crlf);
                 ln = ln->next;
@@ -3090,7 +3239,7 @@ static void spopCommand(redisClient *c) {
         } else {
             robj *ele = dictGetEntryKey(de);
 
-            addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",sdslen(ele->ptr)));
+            addReplyBulkLen(c,ele);
             addReply(c,ele);
             addReply(c,shared.crlf);
             dictDelete(set->ptr,ele);
@@ -3171,7 +3320,7 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
             continue; /* at least one set does not contain the member */
         ele = dictGetEntryKey(de);
         if (!dstkey) {
-            addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",sdslen(ele->ptr)));
+            addReplyBulkLen(c,ele);
             addReply(c,ele);
             addReply(c,shared.crlf);
             cardinality++;
@@ -3280,8 +3429,7 @@ static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnu
             robj *ele;
 
             ele = dictGetEntryKey(de);
-            addReplySds(c,sdscatprintf(sdsempty(),
-                    "$%d\r\n",sdslen(ele->ptr)));
+            addReplyBulkLen(c,ele);
             addReply(c,ele);
             addReply(c,shared.crlf);
         }
@@ -3357,6 +3505,12 @@ static robj *lookupKeyByPattern(redisDb *db, robj *pattern, robj *subst) {
         char buf[REDIS_SORTKEY_MAX+1];
     } keyname;
 
+    if (subst->encoding == REDIS_ENCODING_RAW)
+        incrRefCount(subst);
+    else {
+        subst = getDecodedObject(subst);
+    }
+
     spat = pattern->ptr;
     ssub = subst->ptr;
     if (sdslen(spat)+sdslen(ssub)-1 > REDIS_SORTKEY_MAX) return NULL;
@@ -3376,6 +3530,8 @@ static robj *lookupKeyByPattern(redisDb *db, robj *pattern, robj *subst) {
     keyobj.type = REDIS_STRING;
     keyobj.ptr = ((char*)&keyname)+(sizeof(long)*2);
 
+    decrRefCount(subst);
+
     /* printf("lookup '%s' => %p\n", keyname.buf,de); */
     return lookupKeyRead(db,&keyobj);
 }
@@ -3413,7 +3569,20 @@ static int sortCompare(const void *s1, const void *s2) {
             }
         } else {
             /* Compare elements directly */
-            cmp = strcoll(so1->obj->ptr,so2->obj->ptr);
+            if (so1->obj->encoding == REDIS_ENCODING_RAW &&
+                so2->obj->encoding == REDIS_ENCODING_RAW) {
+                cmp = strcoll(so1->obj->ptr,so2->obj->ptr);
+            } else {
+                robj *dec1, *dec2;
+
+                dec1 = so1->obj->encoding == REDIS_ENCODING_RAW ?
+                    so1->obj : getDecodedObject(so1->obj);
+                dec2 = so2->obj->encoding == REDIS_ENCODING_RAW ?
+                    so2->obj : getDecodedObject(so2->obj);
+                cmp = strcoll(dec1->ptr,dec2->ptr);
+                if (dec1 != so1->obj) decrRefCount(dec1);
+                if (dec2 != so2->obj) decrRefCount(dec2);
+            }
         }
     }
     return server.sort_desc ? -cmp : cmp;
@@ -3543,13 +3712,33 @@ static void sortCommand(redisClient *c) {
                 byval = lookupKeyByPattern(c->db,sortby,vector[j].obj);
                 if (!byval || byval->type != REDIS_STRING) continue;
                 if (alpha) {
-                    vector[j].u.cmpobj = byval;
-                    incrRefCount(byval);
+                    if (byval->encoding == REDIS_ENCODING_RAW) {
+                        vector[j].u.cmpobj = byval;
+                        incrRefCount(byval);
+                    } else {
+                        vector[j].u.cmpobj = getDecodedObject(byval);
+                    }
                 } else {
-                    vector[j].u.score = strtod(byval->ptr,NULL);
+                    if (byval->encoding == REDIS_ENCODING_RAW) {
+                        vector[j].u.score = strtod(byval->ptr,NULL);
+                    } else {
+                        if (byval->encoding == REDIS_ENCODING_INT)
+                            vector[j].u.score = (long)byval->ptr;
+                        else
+                            assert(1 != 1);
+                    }
                 }
             } else {
-                if (!alpha) vector[j].u.score = strtod(vector[j].obj->ptr,NULL);
+                if (!alpha) {
+                    if (vector[j].obj->encoding == REDIS_ENCODING_RAW)
+                        vector[j].u.score = strtod(vector[j].obj->ptr,NULL);
+                    else {
+                        if (vector[j].obj->encoding == REDIS_ENCODING_INT)
+                            vector[j].u.score = (long) vector[j].obj->ptr;
+                        else
+                            assert(1 != 1);
+                    }
+                }
             }
         }
     }
@@ -3581,8 +3770,7 @@ static void sortCommand(redisClient *c) {
     for (j = start; j <= end; j++) {
         listNode *ln;
         if (!getop) {
-            addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",
-                sdslen(vector[j].obj->ptr)));
+            addReplyBulkLen(c,vector[j].obj);
             addReply(c,vector[j].obj);
             addReply(c,shared.crlf);
         }
@@ -3596,8 +3784,7 @@ static void sortCommand(redisClient *c) {
                 if (!val || val->type != REDIS_STRING) {
                     addReply(c,shared.nullbulk);
                 } else {
-                    addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",
-                        sdslen(val->ptr)));
+                    addReplyBulkLen(c,val);
                     addReply(c,val);
                     addReply(c,shared.crlf);
                 }
@@ -4178,8 +4365,8 @@ static void debugCommand(redisClient *c) {
         key = dictGetEntryKey(de);
         val = dictGetEntryVal(de);
         addReplySds(c,sdscatprintf(sdsempty(),
-            "+Key at:%p refcount:%d, value at:%p refcount:%d\r\n",
-                key, key->refcount, val, val->refcount));
+            "+Key at:%p refcount:%d, value at:%p refcount:%d encoding:%d\r\n",
+                key, key->refcount, val, val->refcount, val->encoding));
     } else {
         addReplySds(c,sdsnew(
             "-ERR Syntax error, try DEBUG [SEGFAULT|OBJECT <key>]\r\n"));
@@ -4188,13 +4375,18 @@ static void debugCommand(redisClient *c) {
 
 #ifdef HAVE_BACKTRACE
 static struct redisFunctionSym symsTable[] = {
+{"dictEncObjKeyCompare", (unsigned long)dictEncObjKeyCompare},
+{"dictEncObjHash", (unsigned long)dictEncObjHash},
+{"incrDecrCommand", (unsigned long)incrDecrCommand},
 {"freeStringObject", (unsigned long)freeStringObject},
 {"freeListObject", (unsigned long)freeListObject},
 {"freeSetObject", (unsigned long)freeSetObject},
 {"decrRefCount", (unsigned long)decrRefCount},
 {"createObject", (unsigned long)createObject},
 {"freeClient", (unsigned long)freeClient},
 {"rdbLoad", (unsigned long)rdbLoad},
+{"rdbSaveStringObject", (unsigned long)rdbSaveStringObject},
+{"rdbSaveStringObjectRaw", (unsigned long)rdbSaveStringObjectRaw},
 {"addReply", (unsigned long)addReply},
 {"addReplySds", (unsigned long)addReplySds},
 {"incrRefCount", (unsigned long)incrRefCount},
@@ -4203,6 +4395,8 @@ static struct redisFunctionSym symsTable[] = {
 {"replicationFeedSlaves", (unsigned long)replicationFeedSlaves},
 {"syncWithMaster", (unsigned long)syncWithMaster},
 {"tryObjectSharing", (unsigned long)tryObjectSharing},
+{"tryObjectEncoding", (unsigned long)tryObjectEncoding},
+{"getDecodedObject", (unsigned long)getDecodedObject},
 {"removeExpire", (unsigned long)removeExpire},
 {"expireIfNeeded", (unsigned long)expireIfNeeded},
 {"deleteIfVolatile", (unsigned long)deleteIfVolatile},