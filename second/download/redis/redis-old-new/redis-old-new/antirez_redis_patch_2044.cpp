@@ -3064,7 +3064,9 @@ static robj *createZiplistObject(void) {
 
 static robj *createSetObject(void) {
     dict *d = dictCreate(&setDictType,NULL);
-    return createObject(REDIS_SET,d);
+    robj *o = createObject(REDIS_SET,d);
+    o->encoding = REDIS_ENCODING_HT;
+    return o;
 }
 
 static robj *createHashObject(void) {
@@ -5457,6 +5459,99 @@ static void rpoplpushcommand(redisClient *c) {
 
 /* ==================================== Sets ================================ */
 
+static int setTypeAdd(robj *subject, robj *value) {
+    if (subject->encoding == REDIS_ENCODING_HT) {
+        if (dictAdd(subject->ptr,value,NULL) == DICT_OK) {
+            incrRefCount(value);
+            return 1;
+        }
+    } else {
+        redisPanic("Unknown set encoding");
+    }
+    return 0;
+}
+
+static int setTypeRemove(robj *subject, robj *value) {
+    if (subject->encoding == REDIS_ENCODING_HT) {
+        if (dictDelete(subject->ptr,value) == DICT_OK) {
+            if (htNeedsResize(subject->ptr)) dictResize(subject->ptr);
+            return 1;
+        }
+    } else {
+        redisPanic("Unknown set encoding");
+    }
+    return 0;
+}
+
+static int setTypeIsMember(robj *subject, robj *value) {
+    if (subject->encoding == REDIS_ENCODING_HT) {
+        return dictFind((dict*)subject->ptr,value) != NULL;
+    } else {
+        redisPanic("Unknown set encoding");
+    }
+}
+
+/* Structure to hold set iteration abstraction. */
+typedef struct {
+    int encoding;
+    dictIterator *di;
+} setIterator;
+
+static setIterator *setTypeInitIterator(robj *subject) {
+    setIterator *si = zmalloc(sizeof(setIterator));
+    si->encoding = subject->encoding;
+    if (si->encoding == REDIS_ENCODING_HT) {
+        si->di = dictGetIterator(subject->ptr);
+    } else {
+        redisPanic("Unknown set encoding");
+    }
+    return si;
+}
+
+static void setTypeReleaseIterator(setIterator *si) {
+    if (si->encoding == REDIS_ENCODING_HT)
+        dictReleaseIterator(si->di);
+    zfree(si);
+}
+
+/* Move to the next entry in the set. Returns the object at the current
+ * position, or NULL when the end is reached. This object will have its
+ * refcount incremented, so the caller needs to take care of this. */
+static robj *setTypeNext(setIterator *si) {
+    robj *ret = NULL;
+    if (si->encoding == REDIS_ENCODING_HT) {
+        dictEntry *de = dictNext(si->di);
+        if (de != NULL) {
+            ret = dictGetEntryKey(de);
+            incrRefCount(ret);
+        }
+    }
+    return ret;
+}
+
+
+/* Return random element from set. The returned object will always have
+ * an incremented refcount. */
+robj *setTypeRandomElement(robj *subject) {
+    robj *ret = NULL;
+    if (subject->encoding == REDIS_ENCODING_HT) {
+        dictEntry *de = dictGetRandomKey(subject->ptr);
+        ret = dictGetEntryKey(de);
+        incrRefCount(ret);
+    } else {
+        redisPanic("Unknown set encoding");
+    }
+    return ret;
+}
+
+static unsigned long setTypeSize(robj *subject) {
+    if (subject->encoding == REDIS_ENCODING_HT) {
+        return dictSize((dict*)subject->ptr);
+    } else {
+        redisPanic("Unknown set encoding");
+    }
+}
+
 static void saddCommand(redisClient *c) {
     robj *set;
 
@@ -5470,8 +5565,7 @@ static void saddCommand(redisClient *c) {
             return;
         }
     }
-    if (dictAdd(set->ptr,c->argv[2],NULL) == DICT_OK) {
-        incrRefCount(c->argv[2]);
+    if (setTypeAdd(set,c->argv[2])) {
         server.dirty++;
         addReply(c,shared.cone);
     } else {
@@ -5485,10 +5579,9 @@ static void sremCommand(redisClient *c) {
     if ((set = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,set,REDIS_SET)) return;
 
-    if (dictDelete(set->ptr,c->argv[2]) == DICT_OK) {
+    if (setTypeRemove(set,c->argv[2])) {
+        if (setTypeSize(set) == 0) dbDelete(c->db,c->argv[1]);
         server.dirty++;
-        if (htNeedsResize(set->ptr)) dictResize(set->ptr);
-        if (dictSize((dict*)set->ptr) == 0) dbDelete(c->db,c->argv[1]);
         addReply(c,shared.cone);
     } else {
         addReply(c,shared.czero);
@@ -5513,21 +5606,20 @@ static void smoveCommand(redisClient *c) {
         return;
     }
     /* Remove the element from the source set */
-    if (dictDelete(srcset->ptr,c->argv[3]) == DICT_ERR) {
+    if (!setTypeRemove(srcset,c->argv[3])) {
         /* Key not found in the src set! return zero */
         addReply(c,shared.czero);
         return;
     }
-    if (dictSize((dict*)srcset->ptr) == 0 && srcset != dstset)
+    if (setTypeSize(srcset) == 0 && srcset != dstset)
         dbDelete(c->db,c->argv[1]);
     server.dirty++;
     /* Add the element to the destination set */
     if (!dstset) {
         dstset = createSetObject();
         dbAdd(c->db,c->argv[2],dstset);
     }
-    if (dictAdd(dstset->ptr,c->argv[3],NULL) == DICT_OK)
-        incrRefCount(c->argv[3]);
+    setTypeAdd(dstset,c->argv[3]);
     addReply(c,shared.cone);
 }
 
@@ -5537,82 +5629,70 @@ static void sismemberCommand(redisClient *c) {
     if ((set = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,set,REDIS_SET)) return;
 
-    if (dictFind(set->ptr,c->argv[2]))
+    if (setTypeIsMember(set,c->argv[2]))
         addReply(c,shared.cone);
     else
         addReply(c,shared.czero);
 }
 
 static void scardCommand(redisClient *c) {
     robj *o;
-    dict *s;
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,o,REDIS_SET)) return;
 
-    s = o->ptr;
-    addReplyUlong(c,dictSize(s));
+    addReplyUlong(c,setTypeSize(o));
 }
 
 static void spopCommand(redisClient *c) {
-    robj *set;
-    dictEntry *de;
+    robj *set, *ele;
 
     if ((set = lookupKeyWriteOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
         checkType(c,set,REDIS_SET)) return;
 
-    de = dictGetRandomKey(set->ptr);
-    if (de == NULL) {
+    ele = setTypeRandomElement(set);
+    if (ele == NULL) {
         addReply(c,shared.nullbulk);
     } else {
-        robj *ele = dictGetEntryKey(de);
-
+        setTypeRemove(set,ele);
         addReplyBulk(c,ele);
-        dictDelete(set->ptr,ele);
-        if (htNeedsResize(set->ptr)) dictResize(set->ptr);
-        if (dictSize((dict*)set->ptr) == 0) dbDelete(c->db,c->argv[1]);
+        decrRefCount(ele);
+        if (setTypeSize(set) == 0) dbDelete(c->db,c->argv[1]);
         server.dirty++;
     }
 }
 
 static void srandmemberCommand(redisClient *c) {
-    robj *set;
-    dictEntry *de;
+    robj *set, *ele;
 
     if ((set = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
         checkType(c,set,REDIS_SET)) return;
 
-    de = dictGetRandomKey(set->ptr);
-    if (de == NULL) {
+    ele = setTypeRandomElement(set);
+    if (ele == NULL) {
         addReply(c,shared.nullbulk);
     } else {
-        robj *ele = dictGetEntryKey(de);
-
         addReplyBulk(c,ele);
+        decrRefCount(ele);
     }
 }
 
 static int qsortCompareSetsByCardinality(const void *s1, const void *s2) {
-    dict **d1 = (void*) s1, **d2 = (void*) s2;
-
-    return dictSize(*d1)-dictSize(*d2);
+    return setTypeSize(*(robj**)s1)-setTypeSize(*(robj**)s2);
 }
 
-static void sinterGenericCommand(redisClient *c, robj **setskeys, unsigned long setsnum, robj *dstkey) {
-    dict **dv = zmalloc(sizeof(dict*)*setsnum);
-    dictIterator *di;
-    dictEntry *de;
-    robj *lenobj = NULL, *dstset = NULL;
+static void sinterGenericCommand(redisClient *c, robj **setkeys, unsigned long setnum, robj *dstkey) {
+    robj **sets = zmalloc(sizeof(robj*)*setnum);
+    setIterator *si;
+    robj *ele, *lenobj = NULL, *dstset = NULL;
     unsigned long j, cardinality = 0;
 
-    for (j = 0; j < setsnum; j++) {
-        robj *setobj;
-
-        setobj = dstkey ?
-                    lookupKeyWrite(c->db,setskeys[j]) :
-                    lookupKeyRead(c->db,setskeys[j]);
+    for (j = 0; j < setnum; j++) {
+        robj *setobj = dstkey ?
+            lookupKeyWrite(c->db,setkeys[j]) :
+            lookupKeyRead(c->db,setkeys[j]);
         if (!setobj) {
-            zfree(dv);
+            zfree(sets);
             if (dstkey) {
                 if (dbDelete(c->db,dstkey))
                     server.dirty++;
@@ -5622,16 +5702,15 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, unsigned long
             }
             return;
         }
-        if (setobj->type != REDIS_SET) {
-            zfree(dv);
-            addReply(c,shared.wrongtypeerr);
+        if (checkType(c,setobj,REDIS_SET)) {
+            zfree(sets);
             return;
         }
-        dv[j] = setobj->ptr;
+        sets[j] = setobj;
     }
     /* Sort sets from the smallest to largest, this will improve our
      * algorithm's performace */
-    qsort(dv,setsnum,sizeof(dict*),qsortCompareSetsByCardinality);
+    qsort(sets,setnum,sizeof(robj*),qsortCompareSetsByCardinality);
 
     /* The first thing we should output is the total number of elements...
      * since this is a multi-bulk write, but at this stage we don't know
@@ -5651,33 +5730,31 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, unsigned long
     /* Iterate all the elements of the first (smallest) set, and test
      * the element against all the other sets, if at least one set does
      * not include the element it is discarded */
-    di = dictGetIterator(dv[0]);
-
-    while((de = dictNext(di)) != NULL) {
-        robj *ele;
-
-        for (j = 1; j < setsnum; j++)
-            if (dictFind(dv[j],dictGetEntryKey(de)) == NULL) break;
-        if (j != setsnum)
-            continue; /* at least one set does not contain the member */
-        ele = dictGetEntryKey(de);
-        if (!dstkey) {
-            addReplyBulk(c,ele);
-            cardinality++;
-        } else {
-            dictAdd(dstset->ptr,ele,NULL);
-            incrRefCount(ele);
+    si = setTypeInitIterator(sets[0]);
+    while((ele = setTypeNext(si)) != NULL) {
+        for (j = 1; j < setnum; j++)
+            if (!setTypeIsMember(sets[j],ele)) break;
+
+        /* Only take action when all sets contain the member */
+        if (j == setnum) {
+            if (!dstkey) {
+                addReplyBulk(c,ele);
+                cardinality++;
+            } else {
+                setTypeAdd(dstset,ele);
+            }
         }
+        decrRefCount(ele);
     }
-    dictReleaseIterator(di);
+    setTypeReleaseIterator(si);
 
     if (dstkey) {
         /* Store the resulting set into the target, if the intersection
          * is not an empty set. */
         dbDelete(c->db,dstkey);
-        if (dictSize((dict*)dstset->ptr) > 0) {
+        if (setTypeSize(dstset) > 0) {
             dbAdd(c->db,dstkey,dstset);
-            addReplyLongLong(c,dictSize((dict*)dstset->ptr));
+            addReplyLongLong(c,setTypeSize(dstset));
         } else {
             decrRefCount(dstset);
             addReply(c,shared.czero);
@@ -5686,7 +5763,7 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, unsigned long
     } else {
         lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",cardinality);
     }
-    zfree(dv);
+    zfree(sets);
 }
 
 static void sinterCommand(redisClient *c) {
@@ -5701,29 +5778,25 @@ static void sinterstoreCommand(redisClient *c) {
 #define REDIS_OP_DIFF 1
 #define REDIS_OP_INTER 2
 
-static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnum, robj *dstkey, int op) {
-    dict **dv = zmalloc(sizeof(dict*)*setsnum);
-    dictIterator *di;
-    dictEntry *de;
-    robj *dstset = NULL;
+static void sunionDiffGenericCommand(redisClient *c, robj **setkeys, int setnum, robj *dstkey, int op) {
+    robj **sets = zmalloc(sizeof(robj*)*setnum);
+    setIterator *si;
+    robj *ele, *dstset = NULL;
     int j, cardinality = 0;
 
-    for (j = 0; j < setsnum; j++) {
-        robj *setobj;
-
-        setobj = dstkey ?
-                    lookupKeyWrite(c->db,setskeys[j]) :
-                    lookupKeyRead(c->db,setskeys[j]);
+    for (j = 0; j < setnum; j++) {
+        robj *setobj = dstkey ?
+            lookupKeyWrite(c->db,setkeys[j]) :
+            lookupKeyRead(c->db,setkeys[j]);
         if (!setobj) {
-            dv[j] = NULL;
+            sets[j] = NULL;
             continue;
         }
-        if (setobj->type != REDIS_SET) {
-            zfree(dv);
-            addReply(c,shared.wrongtypeerr);
+        if (checkType(c,setobj,REDIS_SET)) {
+            zfree(sets);
             return;
         }
-        dv[j] = setobj->ptr;
+        sets[j] = setobj;
     }
 
     /* We need a temp set object to store our union. If the dstkey
@@ -5733,60 +5806,53 @@ static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnu
 
     /* Iterate all the elements of all the sets, add every element a single
      * time to the result set */
-    for (j = 0; j < setsnum; j++) {
-        if (op == REDIS_OP_DIFF && j == 0 && !dv[j]) break; /* result set is empty */
-        if (!dv[j]) continue; /* non existing keys are like empty sets */
+    for (j = 0; j < setnum; j++) {
+        if (op == REDIS_OP_DIFF && j == 0 && !sets[j]) break; /* result set is empty */
+        if (!sets[j]) continue; /* non existing keys are like empty sets */
 
-        di = dictGetIterator(dv[j]);
-
-        while((de = dictNext(di)) != NULL) {
-            robj *ele;
-
-            /* dictAdd will not add the same element multiple times */
-            ele = dictGetEntryKey(de);
+        si = setTypeInitIterator(sets[j]);
+        while((ele = setTypeNext(si)) != NULL) {
             if (op == REDIS_OP_UNION || j == 0) {
-                if (dictAdd(dstset->ptr,ele,NULL) == DICT_OK) {
-                    incrRefCount(ele);
+                if (setTypeAdd(dstset,ele)) {
                     cardinality++;
                 }
             } else if (op == REDIS_OP_DIFF) {
-                if (dictDelete(dstset->ptr,ele) == DICT_OK) {
+                if (setTypeRemove(dstset,ele)) {
                     cardinality--;
                 }
             }
+            decrRefCount(ele);
         }
-        dictReleaseIterator(di);
+        setTypeReleaseIterator(si);
 
-        /* result set is empty? Exit asap. */
+        /* Exit when result set is empty. */
         if (op == REDIS_OP_DIFF && cardinality == 0) break;
     }
 
     /* Output the content of the resulting set, if not in STORE mode */
     if (!dstkey) {
         addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",cardinality));
-        di = dictGetIterator(dstset->ptr);
-        while((de = dictNext(di)) != NULL) {
-            robj *ele;
-
-            ele = dictGetEntryKey(de);
+        si = setTypeInitIterator(dstset);
+        while((ele = setTypeNext(si)) != NULL) {
             addReplyBulk(c,ele);
+            decrRefCount(ele);
         }
-        dictReleaseIterator(di);
+        setTypeReleaseIterator(si);
         decrRefCount(dstset);
     } else {
         /* If we have a target key where to store the resulting set
          * create this key with the result set inside */
         dbDelete(c->db,dstkey);
-        if (dictSize((dict*)dstset->ptr) > 0) {
+        if (setTypeSize(dstset) > 0) {
             dbAdd(c->db,dstkey,dstset);
-            addReplyLongLong(c,dictSize((dict*)dstset->ptr));
+            addReplyLongLong(c,setTypeSize(dstset));
         } else {
             decrRefCount(dstset);
             addReply(c,shared.czero);
         }
         server.dirty++;
     }
-    zfree(dv);
+    zfree(sets);
 }
 
 static void sunionCommand(redisClient *c) {