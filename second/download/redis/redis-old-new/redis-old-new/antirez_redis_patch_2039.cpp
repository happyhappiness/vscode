@@ -4,21 +4,190 @@
  * Set Commands
  *----------------------------------------------------------------------------*/
 
+/* Factory method to return a set that *can* hold "value". When the object has
+ * an integer-encodable value, an intset will be returned. Otherwise a regular
+ * hash table. */
+robj *setTypeCreate(robj *value) {
+    if (getLongLongFromObject(value,NULL) == REDIS_OK)
+        return createIntsetObject();
+    return createSetObject();
+}
+
+int setTypeAdd(robj *subject, robj *value) {
+    long long llval;
+    if (subject->encoding == REDIS_ENCODING_HT) {
+        if (dictAdd(subject->ptr,value,NULL) == DICT_OK) {
+            incrRefCount(value);
+            return 1;
+        }
+    } else if (subject->encoding == REDIS_ENCODING_INTSET) {
+        if (getLongLongFromObject(value,&llval) == REDIS_OK) {
+            uint8_t success = 0;
+            subject->ptr = intsetAdd(subject->ptr,llval,&success);
+            if (success) {
+                /* Convert to regular set when the intset contains
+                 * too many entries. */
+                if (intsetLen(subject->ptr) > server.set_max_intset_entries)
+                    setTypeConvert(subject,REDIS_ENCODING_HT);
+                return 1;
+            }
+        } else {
+            /* Failed to get integer from object, convert to regular set. */
+            setTypeConvert(subject,REDIS_ENCODING_HT);
+
+            /* The set *was* an intset and this value is not integer
+             * encodable, so dictAdd should always work. */
+            redisAssert(dictAdd(subject->ptr,value,NULL) == DICT_OK);
+            incrRefCount(value);
+            return 1;
+        }
+    } else {
+        redisPanic("Unknown set encoding");
+    }
+    return 0;
+}
+
+int setTypeRemove(robj *subject, robj *value) {
+    long long llval;
+    if (subject->encoding == REDIS_ENCODING_HT) {
+        if (dictDelete(subject->ptr,value) == DICT_OK) {
+            if (htNeedsResize(subject->ptr)) dictResize(subject->ptr);
+            return 1;
+        }
+    } else if (subject->encoding == REDIS_ENCODING_INTSET) {
+        if (getLongLongFromObject(value,&llval) == REDIS_OK) {
+            uint8_t success;
+            subject->ptr = intsetRemove(subject->ptr,llval,&success);
+            if (success) return 1;
+        }
+    } else {
+        redisPanic("Unknown set encoding");
+    }
+    return 0;
+}
+
+int setTypeIsMember(robj *subject, robj *value) {
+    long long llval;
+    if (subject->encoding == REDIS_ENCODING_HT) {
+        return dictFind((dict*)subject->ptr,value) != NULL;
+    } else if (subject->encoding == REDIS_ENCODING_INTSET) {
+        if (getLongLongFromObject(value,&llval) == REDIS_OK) {
+            return intsetFind((intset*)subject->ptr,llval);
+        }
+    } else {
+        redisPanic("Unknown set encoding");
+    }
+    return 0;
+}
+
+setIterator *setTypeInitIterator(robj *subject) {
+    setIterator *si = zmalloc(sizeof(setIterator));
+    si->subject = subject;
+    si->encoding = subject->encoding;
+    if (si->encoding == REDIS_ENCODING_HT) {
+        si->di = dictGetIterator(subject->ptr);
+    } else if (si->encoding == REDIS_ENCODING_INTSET) {
+        si->ii = 0;
+    } else {
+        redisPanic("Unknown set encoding");
+    }
+    return si;
+}
+
+void setTypeReleaseIterator(setIterator *si) {
+    if (si->encoding == REDIS_ENCODING_HT)
+        dictReleaseIterator(si->di);
+    zfree(si);
+}
+
+/* Move to the next entry in the set. Returns the object at the current
+ * position, or NULL when the end is reached. This object will have its
+ * refcount incremented, so the caller needs to take care of this. */
+robj *setTypeNext(setIterator *si) {
+    robj *ret = NULL;
+    if (si->encoding == REDIS_ENCODING_HT) {
+        dictEntry *de = dictNext(si->di);
+        if (de != NULL) {
+            ret = dictGetEntryKey(de);
+            incrRefCount(ret);
+        }
+    } else if (si->encoding == REDIS_ENCODING_INTSET) {
+        long long llval;
+        if (intsetGet(si->subject->ptr,si->ii++,&llval))
+            ret = createStringObjectFromLongLong(llval);
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
+    } else if (subject->encoding == REDIS_ENCODING_INTSET) {
+        long long llval = intsetRandom(subject->ptr);
+        ret = createStringObjectFromLongLong(llval);
+    } else {
+        redisPanic("Unknown set encoding");
+    }
+    return ret;
+}
+
+unsigned long setTypeSize(robj *subject) {
+    if (subject->encoding == REDIS_ENCODING_HT) {
+        return dictSize((dict*)subject->ptr);
+    } else if (subject->encoding == REDIS_ENCODING_INTSET) {
+        return intsetLen((intset*)subject->ptr);
+    } else {
+        redisPanic("Unknown set encoding");
+    }
+}
+
+/* Convert the set to specified encoding. The resulting dict (when converting
+ * to a hashtable) is presized to hold the number of elements in the original
+ * set. */
+void setTypeConvert(robj *subject, int enc) {
+    setIterator *si;
+    robj *element;
+    redisAssert(subject->type == REDIS_SET);
+
+    if (enc == REDIS_ENCODING_HT) {
+        dict *d = dictCreate(&setDictType,NULL);
+        /* Presize the dict to avoid rehashing */
+        dictExpand(d,intsetLen(subject->ptr));
+
+        /* setTypeGet returns a robj with incremented refcount */
+        si = setTypeInitIterator(subject);
+        while ((element = setTypeNext(si)) != NULL)
+            redisAssert(dictAdd(d,element,NULL) == DICT_OK);
+        setTypeReleaseIterator(si);
+
+        subject->encoding = REDIS_ENCODING_HT;
+        zfree(subject->ptr);
+        subject->ptr = d;
+    } else {
+        redisPanic("Unsupported set conversion");
+    }
+}
+
 void saddCommand(redisClient *c) {
     robj *set;
 
     set = lookupKeyWrite(c->db,c->argv[1]);
     if (set == NULL) {
-        set = createSetObject();
+        set = setTypeCreate(c->argv[2]);
         dbAdd(c->db,c->argv[1],set);
     } else {
         if (set->type != REDIS_SET) {
             addReply(c,shared.wrongtypeerr);
             return;
         }
     }
-    if (dictAdd(set->ptr,c->argv[2],NULL) == DICT_OK) {
-        incrRefCount(c->argv[2]);
+    if (setTypeAdd(set,c->argv[2])) {
         server.dirty++;
         addReply(c,shared.cone);
     } else {
@@ -32,49 +201,56 @@ void sremCommand(redisClient *c) {
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
     }
 }
 
 void smoveCommand(redisClient *c) {
-    robj *srcset, *dstset;
-
+    robj *srcset, *dstset, *ele;
     srcset = lookupKeyWrite(c->db,c->argv[1]);
     dstset = lookupKeyWrite(c->db,c->argv[2]);
+    ele = c->argv[3];
 
-    /* If the source key does not exist return 0, if it's of the wrong type
-     * raise an error */
-    if (srcset == NULL || srcset->type != REDIS_SET) {
-        addReply(c, srcset ? shared.wrongtypeerr : shared.czero);
+    /* If the source key does not exist return 0 */
+    if (srcset == NULL) {
+        addReply(c,shared.czero);
         return;
     }
-    /* Error if the destination key is not a set as well */
-    if (dstset && dstset->type != REDIS_SET) {
-        addReply(c,shared.wrongtypeerr);
+
+    /* If the source key has the wrong type, or the destination key
+     * is set and has the wrong type, return with an error. */
+    if (checkType(c,srcset,REDIS_SET) ||
+        (dstset && checkType(c,dstset,REDIS_SET))) return;
+
+    /* If srcset and dstset are equal, SMOVE is a no-op */
+    if (srcset == dstset) {
+        addReply(c,shared.cone);
         return;
     }
-    /* Remove the element from the source set */
-    if (dictDelete(srcset->ptr,c->argv[3]) == DICT_ERR) {
-        /* Key not found in the src set! return zero */
+
+    /* If the element cannot be removed from the src set, return 0. */
+    if (!setTypeRemove(srcset,ele)) {
         addReply(c,shared.czero);
         return;
     }
-    if (dictSize((dict*)srcset->ptr) == 0 && srcset != dstset)
-        dbDelete(c->db,c->argv[1]);
+
+    /* Remove the src set from the database when empty */
+    if (setTypeSize(srcset) == 0) dbDelete(c->db,c->argv[1]);
     server.dirty++;
-    /* Add the element to the destination set */
+
+    /* Create the destination set when it doesn't exist */
     if (!dstset) {
-        dstset = createSetObject();
+        dstset = setTypeCreate(ele);
         dbAdd(c->db,c->argv[2],dstset);
     }
-    if (dictAdd(dstset->ptr,c->argv[3],NULL) == DICT_OK)
-        incrRefCount(c->argv[3]);
+
+    /* An extra key has changed when ele was successfully added to dstset */
+    if (setTypeAdd(dstset,ele)) server.dirty++;
     addReply(c,shared.cone);
 }
 
@@ -84,82 +260,70 @@ void sismemberCommand(redisClient *c) {
     if ((set = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,set,REDIS_SET)) return;
 
-    if (dictFind(set->ptr,c->argv[2]))
+    if (setTypeIsMember(set,c->argv[2]))
         addReply(c,shared.cone);
     else
         addReply(c,shared.czero);
 }
 
 void scardCommand(redisClient *c) {
     robj *o;
-    dict *s;
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,o,REDIS_SET)) return;
 
-    s = o->ptr;
-    addReplyUlong(c,dictSize(s));
+    addReplyUlong(c,setTypeSize(o));
 }
 
 void spopCommand(redisClient *c) {
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
 
 void srandmemberCommand(redisClient *c) {
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
 
 int qsortCompareSetsByCardinality(const void *s1, const void *s2) {
-    dict **d1 = (void*) s1, **d2 = (void*) s2;
-
-    return dictSize(*d1)-dictSize(*d2);
+    return setTypeSize(*(robj**)s1)-setTypeSize(*(robj**)s2);
 }
 
-void sinterGenericCommand(redisClient *c, robj **setskeys, unsigned long setsnum, robj *dstkey) {
-    dict **dv = zmalloc(sizeof(dict*)*setsnum);
-    dictIterator *di;
-    dictEntry *de;
-    robj *lenobj = NULL, *dstset = NULL;
+void sinterGenericCommand(redisClient *c, robj **setkeys, unsigned long setnum, robj *dstkey) {
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
@@ -169,16 +333,15 @@ void sinterGenericCommand(redisClient *c, robj **setskeys, unsigned long setsnum
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
@@ -192,39 +355,37 @@ void sinterGenericCommand(redisClient *c, robj **setskeys, unsigned long setsnum
     } else {
         /* If we have a target key where to store the resulting set
          * create this key with an empty set inside */
-        dstset = createSetObject();
+        dstset = createIntsetObject();
     }
 
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
@@ -233,7 +394,7 @@ void sinterGenericCommand(redisClient *c, robj **setskeys, unsigned long setsnum
     } else {
         lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",cardinality);
     }
-    zfree(dv);
+    zfree(sets);
 }
 
 void sinterCommand(redisClient *c) {
@@ -244,92 +405,85 @@ void sinterstoreCommand(redisClient *c) {
     sinterGenericCommand(c,c->argv+2,c->argc-2,c->argv[1]);
 }
 
-void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnum, robj *dstkey, int op) {
-    dict **dv = zmalloc(sizeof(dict*)*setsnum);
-    dictIterator *di;
-    dictEntry *de;
-    robj *dstset = NULL;
-    int j, cardinality = 0;
+#define REDIS_OP_UNION 0
+#define REDIS_OP_DIFF 1
+#define REDIS_OP_INTER 2
 
-    for (j = 0; j < setsnum; j++) {
-        robj *setobj;
+void sunionDiffGenericCommand(redisClient *c, robj **setkeys, int setnum, robj *dstkey, int op) {
+    robj **sets = zmalloc(sizeof(robj*)*setnum);
+    setIterator *si;
+    robj *ele, *dstset = NULL;
+    int j, cardinality = 0;
 
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
      * is not NULL (that is, we are inside an SUNIONSTORE operation) then
      * this set object will be the resulting object to set into the target key*/
-    dstset = createSetObject();
+    dstset = createIntsetObject();
 
     /* Iterate all the elements of all the sets, add every element a single
      * time to the result set */
-    for (j = 0; j < setsnum; j++) {
-        if (op == REDIS_OP_DIFF && j == 0 && !dv[j]) break; /* result set is empty */
-        if (!dv[j]) continue; /* non existing keys are like empty sets */
-
-        di = dictGetIterator(dv[j]);
+    for (j = 0; j < setnum; j++) {
+        if (op == REDIS_OP_DIFF && j == 0 && !sets[j]) break; /* result set is empty */
+        if (!sets[j]) continue; /* non existing keys are like empty sets */
 
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
 
 void sunionCommand(redisClient *c) {