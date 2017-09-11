@@ -39,26 +39,28 @@ void sunionDiffGenericCommand(client *c, robj **setkeys, int setnum,
 /* Factory method to return a set that *can* hold "value". When the object has
  * an integer-encodable value, an intset will be returned. Otherwise a regular
  * hash table. */
-robj *setTypeCreate(robj *value) {
-    if (isObjectRepresentableAsLongLong(value,NULL) == C_OK)
+robj *setTypeCreate(sds value) {
+    if (isSdsRepresentableAsLongLong(value,NULL) == C_OK)
         return createIntsetObject();
     return createSetObject();
 }
 
-/* Add the specified value into a set. The function takes care of incrementing
- * the reference count of the object if needed in order to retain a copy.
+/* Add the specified value into a set.
  *
  * If the value was already member of the set, nothing is done and 0 is
  * returned, otherwise the new element is added and 1 is returned. */
-int setTypeAdd(robj *subject, robj *value) {
+int setTypeAdd(robj *subject, sds value) {
     long long llval;
     if (subject->encoding == OBJ_ENCODING_HT) {
-        if (dictAdd(subject->ptr,value,NULL) == DICT_OK) {
-            incrRefCount(value);
+        dict *ht = subject->ptr;
+        dictEntry *de = dictAddRaw(ht,value);
+        if (de) {
+            dictSetKey(ht,de,sdsdup(value));
+            dictSetVal(ht,de,NULL);
             return 1;
         }
     } else if (subject->encoding == OBJ_ENCODING_INTSET) {
-        if (isObjectRepresentableAsLongLong(value,&llval) == C_OK) {
+        if (isSdsRepresentableAsLongLong(value,&llval) == C_OK) {
             uint8_t success = 0;
             subject->ptr = intsetAdd(subject->ptr,llval,&success);
             if (success) {
@@ -74,9 +76,7 @@ int setTypeAdd(robj *subject, robj *value) {
 
             /* The set *was* an intset and this value is not integer
              * encodable, so dictAdd should always work. */
-            serverAssertWithInfo(NULL,value,
-                                dictAdd(subject->ptr,value,NULL) == DICT_OK);
-            incrRefCount(value);
+            serverAssert(dictAdd(subject->ptr,sdsdup(value),NULL) == DICT_OK);
             return 1;
         }
     } else {
@@ -85,15 +85,15 @@ int setTypeAdd(robj *subject, robj *value) {
     return 0;
 }
 
-int setTypeRemove(robj *setobj, robj *value) {
+int setTypeRemove(robj *setobj, sds value) {
     long long llval;
     if (setobj->encoding == OBJ_ENCODING_HT) {
         if (dictDelete(setobj->ptr,value) == DICT_OK) {
             if (htNeedsResize(setobj->ptr)) dictResize(setobj->ptr);
             return 1;
         }
     } else if (setobj->encoding == OBJ_ENCODING_INTSET) {
-        if (isObjectRepresentableAsLongLong(value,&llval) == C_OK) {
+        if (isSdsRepresentableAsLongLong(value,&llval) == C_OK) {
             int success;
             setobj->ptr = intsetRemove(setobj->ptr,llval,&success);
             if (success) return 1;
@@ -104,12 +104,12 @@ int setTypeRemove(robj *setobj, robj *value) {
     return 0;
 }
 
-int setTypeIsMember(robj *subject, robj *value) {
+int setTypeIsMember(robj *subject, sds value) {
     long long llval;
     if (subject->encoding == OBJ_ENCODING_HT) {
         return dictFind((dict*)subject->ptr,value) != NULL;
     } else if (subject->encoding == OBJ_ENCODING_INTSET) {
-        if (isObjectRepresentableAsLongLong(value,&llval) == C_OK) {
+        if (isSdsRepresentableAsLongLong(value,&llval) == C_OK) {
             return intsetFind((intset*)subject->ptr,llval);
         }
     } else {
@@ -141,54 +141,51 @@ void setTypeReleaseIterator(setTypeIterator *si) {
 /* Move to the next entry in the set. Returns the object at the current
  * position.
  *
- * Since set elements can be internally be stored as redis objects or
+ * Since set elements can be internally be stored as SDS strings or
  * simple arrays of integers, setTypeNext returns the encoding of the
  * set object you are iterating, and will populate the appropriate pointer
- * (objele) or (llele) accordingly.
+ * (sdsele) or (llele) accordingly.
  *
- * Note that both the objele and llele pointers should be passed and cannot
+ * Note that both the sdsele and llele pointers should be passed and cannot
  * be NULL since the function will try to defensively populate the non
  * used field with values which are easy to trap if misused.
  *
- * When there are no longer elements -1 is returned.
- * Returned objects ref count is not incremented, so this function is
- * copy on write friendly. */
-int setTypeNext(setTypeIterator *si, robj **objele, int64_t *llele) {
+ * When there are no longer elements -1 is returned. */
+int setTypeNext(setTypeIterator *si, sds *sdsele, int64_t *llele) {
     if (si->encoding == OBJ_ENCODING_HT) {
         dictEntry *de = dictNext(si->di);
         if (de == NULL) return -1;
-        *objele = dictGetKey(de);
+        *sdsele = dictGetKey(de);
         *llele = -123456789; /* Not needed. Defensive. */
     } else if (si->encoding == OBJ_ENCODING_INTSET) {
         if (!intsetGet(si->subject->ptr,si->ii++,llele))
             return -1;
-        *objele = NULL; /* Not needed. Defensive. */
+        *sdsele = NULL; /* Not needed. Defensive. */
     } else {
         serverPanic("Wrong set encoding in setTypeNext");
     }
     return si->encoding;
 }
 
 /* The not copy on write friendly version but easy to use version
- * of setTypeNext() is setTypeNextObject(), returning new objects
- * or incrementing the ref count of returned objects. So if you don't
- * retain a pointer to this object you should call decrRefCount() against it.
+ * of setTypeNext() is setTypeNextObject(), returning new SDS
+ * strings. So if you don't retain a pointer to this object you should call
+ * sdsfree() against it.
  *
  * This function is the way to go for write operations where COW is not
- * an issue as the result will be anyway of incrementing the ref count. */
-robj *setTypeNextObject(setTypeIterator *si) {
+ * an issue. */
+sds setTypeNextObject(setTypeIterator *si) {
     int64_t intele;
-    robj *objele;
+    sds sdsele;
     int encoding;
 
-    encoding = setTypeNext(si,&objele,&intele);
+    encoding = setTypeNext(si,&sdsele,&intele);
     switch(encoding) {
         case -1:    return NULL;
         case OBJ_ENCODING_INTSET:
-            return createStringObjectFromLongLong(intele);
+            return sdsfromlonglong(intele);
         case OBJ_ENCODING_HT:
-            incrRefCount(objele);
-            return objele;
+            return sdsdup(sdsele);
         default:
             serverPanic("Unsupported encoding");
     }
@@ -197,29 +194,25 @@ robj *setTypeNextObject(setTypeIterator *si) {
 
 /* Return random element from a non empty set.
  * The returned element can be a int64_t value if the set is encoded
- * as an "intset" blob of integers, or a redis object if the set
+ * as an "intset" blob of integers, or an SDS string if the set
  * is a regular set.
  *
  * The caller provides both pointers to be populated with the right
  * object. The return value of the function is the object->encoding
  * field of the object and is used by the caller to check if the
  * int64_t pointer or the redis object pointer was populated.
  *
- * Note that both the objele and llele pointers should be passed and cannot
+ * Note that both the sdsele and llele pointers should be passed and cannot
  * be NULL since the function will try to defensively populate the non
- * used field with values which are easy to trap if misused.
- *
- * When an object is returned (the set was a real set) the ref count
- * of the object is not incremented so this function can be considered
- * copy on write friendly. */
-int setTypeRandomElement(robj *setobj, robj **objele, int64_t *llele) {
+ * used field with values which are easy to trap if misused. */
+int setTypeRandomElement(robj *setobj, sds *sdsele, int64_t *llele) {
     if (setobj->encoding == OBJ_ENCODING_HT) {
         dictEntry *de = dictGetRandomKey(setobj->ptr);
-        *objele = dictGetKey(de);
+        *sdsele = dictGetKey(de);
         *llele = -123456789; /* Not needed. Defensive. */
     } else if (setobj->encoding == OBJ_ENCODING_INTSET) {
         *llele = intsetRandom(setobj->ptr);
-        *objele = NULL; /* Not needed. Defensive. */
+        *sdsele = NULL; /* Not needed. Defensive. */
     } else {
         serverPanic("Unknown set encoding");
     }
@@ -247,17 +240,16 @@ void setTypeConvert(robj *setobj, int enc) {
     if (enc == OBJ_ENCODING_HT) {
         int64_t intele;
         dict *d = dictCreate(&setDictType,NULL);
-        robj *element;
+        sds element;
 
         /* Presize the dict to avoid rehashing */
         dictExpand(d,intsetLen(setobj->ptr));
 
         /* To add the elements we extract integers and create redis objects */
         si = setTypeInitIterator(setobj);
         while (setTypeNext(si,&element,&intele) != -1) {
-            element = createStringObjectFromLongLong(intele);
-            serverAssertWithInfo(NULL,element,
-                                dictAdd(d,element,NULL) == DICT_OK);
+            element = sdsfromlonglong(intele);
+            serverAssert(dictAdd(d,element,NULL) == DICT_OK);
         }
         setTypeReleaseIterator(si);
 
@@ -275,7 +267,7 @@ void saddCommand(client *c) {
 
     set = lookupKeyWrite(c->db,c->argv[1]);
     if (set == NULL) {
-        set = setTypeCreate(c->argv[2]);
+        set = setTypeCreate(c->argv[2]->ptr);
         dbAdd(c->db,c->argv[1],set);
     } else {
         if (set->type != OBJ_SET) {
@@ -285,8 +277,7 @@ void saddCommand(client *c) {
     }
 
     for (j = 2; j < c->argc; j++) {
-        c->argv[j] = tryObjectEncoding(c->argv[j]);
-        if (setTypeAdd(set,c->argv[j])) added++;
+        if (setTypeAdd(set,c->argv[j]->ptr)) added++;
     }
     if (added) {
         signalModifiedKey(c->db,c->argv[1]);
@@ -304,7 +295,7 @@ void sremCommand(client *c) {
         checkType(c,set,OBJ_SET)) return;
 
     for (j = 2; j < c->argc; j++) {
-        if (setTypeRemove(set,c->argv[j])) {
+        if (setTypeRemove(set,c->argv[j]->ptr)) {
             deleted++;
             if (setTypeSize(set) == 0) {
                 dbDelete(c->db,c->argv[1]);
@@ -328,7 +319,7 @@ void smoveCommand(client *c) {
     robj *srcset, *dstset, *ele;
     srcset = lookupKeyWrite(c->db,c->argv[1]);
     dstset = lookupKeyWrite(c->db,c->argv[2]);
-    ele = c->argv[3] = tryObjectEncoding(c->argv[3]);
+    ele = c->argv[3];
 
     /* If the source key does not exist return 0 */
     if (srcset == NULL) {
@@ -343,12 +334,13 @@ void smoveCommand(client *c) {
 
     /* If srcset and dstset are equal, SMOVE is a no-op */
     if (srcset == dstset) {
-        addReply(c,setTypeIsMember(srcset,ele) ? shared.cone : shared.czero);
+        addReply(c,setTypeIsMember(srcset,ele->ptr) ?
+            shared.cone : shared.czero);
         return;
     }
 
     /* If the element cannot be removed from the src set, return 0. */
-    if (!setTypeRemove(srcset,ele)) {
+    if (!setTypeRemove(srcset,ele->ptr)) {
         addReply(c,shared.czero);
         return;
     }
@@ -365,12 +357,12 @@ void smoveCommand(client *c) {
 
     /* Create the destination set when it doesn't exist */
     if (!dstset) {
-        dstset = setTypeCreate(ele);
+        dstset = setTypeCreate(ele->ptr);
         dbAdd(c->db,c->argv[2],dstset);
     }
 
     /* An extra key has changed when ele was successfully added to dstset */
-    if (setTypeAdd(dstset,ele)) {
+    if (setTypeAdd(dstset,ele->ptr)) {
         server.dirty++;
         notifyKeyspaceEvent(NOTIFY_SET,"sadd",c->argv[2],c->db->id);
     }
@@ -383,8 +375,7 @@ void sismemberCommand(client *c) {
     if ((set = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,set,OBJ_SET)) return;
 
-    c->argv[2] = tryObjectEncoding(c->argv[2]);
-    if (setTypeIsMember(set,c->argv[2]))
+    if (setTypeIsMember(set,c->argv[2]->ptr))
         addReply(c,shared.cone);
     else
         addReply(c,shared.czero);
@@ -457,7 +448,7 @@ void spopWithCountCommand(client *c) {
         return;
     }
 
-    /* Case 2 and 3 require to replicate SPOP as a set of SERM commands.
+    /* Case 2 and 3 require to replicate SPOP as a set of SREM commands.
      * Prepare our replication argument vector. Also send the array length
      * which is common to both the code paths. */
     robj *propargv[3];
@@ -466,6 +457,7 @@ void spopWithCountCommand(client *c) {
     addReplyMultiBulkLen(c,count);
 
     /* Common iteration vars. */
+    sds sdsele;
     robj *objele;
     int encoding;
     int64_t llele;
@@ -480,17 +472,18 @@ void spopWithCountCommand(client *c) {
      * the set. */
     if (remaining*SPOP_MOVE_STRATEGY_MUL > count) {
         while(count--) {
-            encoding = setTypeRandomElement(set,&objele,&llele);
+            /* Emit and remove. */
+            encoding = setTypeRandomElement(set,&sdsele,&llele);
             if (encoding == OBJ_ENCODING_INTSET) {
+                addReplyBulkLongLong(c,llele);
                 objele = createStringObjectFromLongLong(llele);
+                set->ptr = intsetRemove(set->ptr,llele,NULL);
             } else {
-                incrRefCount(objele);
+                addReplyBulkCBuffer(c,sdsele,sdslen(sdsele));
+                objele = createStringObject(sdsele,sdslen(sdsele));
+                setTypeRemove(set,sdsele);
             }
 
-            /* Return the element to the client and remove from the set. */
-            addReplyBulk(c,objele);
-            setTypeRemove(set,objele);
-
             /* Replicate/AOF this command as an SREM operation */
             propargv[2] = objele;
             alsoPropagate(server.sremCommand,c->db->id,propargv,3,
@@ -510,16 +503,16 @@ void spopWithCountCommand(client *c) {
 
         /* Create a new set with just the remaining elements. */
         while(remaining--) {
-            encoding = setTypeRandomElement(set,&objele,&llele);
+            encoding = setTypeRandomElement(set,&sdsele,&llele);
             if (encoding == OBJ_ENCODING_INTSET) {
-                objele = createStringObjectFromLongLong(llele);
+                sdsele = sdsfromlonglong(llele);
             } else {
-                incrRefCount(objele);
+                sdsele = sdsdup(sdsele);
             }
-            if (!newset) newset = setTypeCreate(objele);
-            setTypeAdd(newset,objele);
-            setTypeRemove(set,objele);
-            decrRefCount(objele);
+            if (!newset) newset = setTypeCreate(sdsele);
+            setTypeAdd(newset,sdsele);
+            setTypeRemove(set,sdsele);
+            sdsfree(sdsele);
         }
 
         /* Assign the new set as the key value. */
@@ -529,19 +522,19 @@ void spopWithCountCommand(client *c) {
         /* Tranfer the old set to the client and release it. */
         setTypeIterator *si;
         si = setTypeInitIterator(set);
-        while((encoding = setTypeNext(si,&objele,&llele)) != -1) {
+        while((encoding = setTypeNext(si,&sdsele,&llele)) != -1) {
             if (encoding == OBJ_ENCODING_INTSET) {
+                addReplyBulkLongLong(c,llele);
                 objele = createStringObjectFromLongLong(llele);
             } else {
-                incrRefCount(objele);
+                addReplyBulkCBuffer(c,sdsele,sdslen(sdsele));
+                objele = createStringObject(sdsele,sdslen(sdsele));
             }
-            addReplyBulk(c,objele);
 
             /* Replicate/AOF this command as an SREM operation */
             propargv[2] = objele;
             alsoPropagate(server.sremCommand,c->db->id,propargv,3,
                 PROPAGATE_AOF|PROPAGATE_REPL);
-
             decrRefCount(objele);
         }
         setTypeReleaseIterator(si);
@@ -558,6 +551,7 @@ void spopWithCountCommand(client *c) {
 
 void spopCommand(client *c) {
     robj *set, *ele, *aux;
+    sds sdsele;
     int64_t llele;
     int encoding;
 
@@ -575,27 +569,27 @@ void spopCommand(client *c) {
         checkType(c,set,OBJ_SET)) return;
 
     /* Get a random element from the set */
-    encoding = setTypeRandomElement(set,&ele,&llele);
+    encoding = setTypeRandomElement(set,&sdsele,&llele);
 
     /* Remove the element from the set */
     if (encoding == OBJ_ENCODING_INTSET) {
         ele = createStringObjectFromLongLong(llele);
         set->ptr = intsetRemove(set->ptr,llele,NULL);
     } else {
-        incrRefCount(ele);
-        setTypeRemove(set,ele);
+        ele = createStringObject(sdsele,sdslen(sdsele));
+        setTypeRemove(set,ele->ptr);
     }
 
     notifyKeyspaceEvent(NOTIFY_SET,"spop",c->argv[1],c->db->id);
 
     /* Replicate/AOF this command as an SREM operation */
     aux = createStringObject("SREM",4);
     rewriteClientCommandVector(c,3,aux,c->argv[1],ele);
-    decrRefCount(ele);
     decrRefCount(aux);
 
     /* Add the element to the reply */
     addReplyBulk(c,ele);
+    decrRefCount(ele);
 
     /* Delete the set if it's empty */
     if (setTypeSize(set) == 0) {
@@ -620,7 +614,8 @@ void srandmemberWithCountCommand(client *c) {
     long l;
     unsigned long count, size;
     int uniq = 1;
-    robj *set, *ele;
+    robj *set;
+    sds ele;
     int64_t llele;
     int encoding;
 
@@ -657,7 +652,7 @@ void srandmemberWithCountCommand(client *c) {
             if (encoding == OBJ_ENCODING_INTSET) {
                 addReplyBulkLongLong(c,llele);
             } else {
-                addReplyBulk(c,ele);
+                addReplyBulkCBuffer(c,ele,sdslen(ele));
             }
         }
         return;
@@ -672,7 +667,7 @@ void srandmemberWithCountCommand(client *c) {
     }
 
     /* For CASE 3 and CASE 4 we need an auxiliary dictionary. */
-    d = dictCreate(&setDictType,NULL);
+    d = dictCreate(&objectKeyPointerValueDictType,NULL);
 
     /* CASE 3:
      * The number of elements inside the set is not greater than
@@ -694,7 +689,7 @@ void srandmemberWithCountCommand(client *c) {
             if (encoding == OBJ_ENCODING_INTSET) {
                 retval = dictAdd(d,createStringObjectFromLongLong(llele),NULL);
             } else {
-                retval = dictAdd(d,dupStringObject(ele),NULL);
+                retval = dictAdd(d,createStringObject(ele,sdslen(ele)),NULL);
             }
             serverAssert(retval == DICT_OK);
         }
@@ -717,21 +712,22 @@ void srandmemberWithCountCommand(client *c) {
      * to reach the specified count. */
     else {
         unsigned long added = 0;
+        robj *objele;
 
         while(added < count) {
             encoding = setTypeRandomElement(set,&ele,&llele);
             if (encoding == OBJ_ENCODING_INTSET) {
-                ele = createStringObjectFromLongLong(llele);
+                objele = createStringObjectFromLongLong(llele);
             } else {
-                ele = dupStringObject(ele);
+                objele = createStringObject(ele,sdslen(ele));
             }
             /* Try to add the object to the dictionary. If it already exists
              * free it, otherwise increment the number of objects we have
              * in the result dictionary. */
-            if (dictAdd(d,ele,NULL) == DICT_OK)
+            if (dictAdd(d,objele,NULL) == DICT_OK)
                 added++;
             else
-                decrRefCount(ele);
+                decrRefCount(objele);
         }
     }
 
@@ -750,7 +746,8 @@ void srandmemberWithCountCommand(client *c) {
 }
 
 void srandmemberCommand(client *c) {
-    robj *set, *ele;
+    robj *set;
+    sds ele;
     int64_t llele;
     int encoding;
 
@@ -769,7 +766,7 @@ void srandmemberCommand(client *c) {
     if (encoding == OBJ_ENCODING_INTSET) {
         addReplyBulkLongLong(c,llele);
     } else {
-        addReplyBulk(c,ele);
+        addReplyBulkCBuffer(c,ele,sdslen(ele));
     }
 }
 
@@ -789,7 +786,8 @@ void sinterGenericCommand(client *c, robj **setkeys,
                           unsigned long setnum, robj *dstkey) {
     robj **sets = zmalloc(sizeof(robj*)*setnum);
     setTypeIterator *si;
-    robj *eleobj, *dstset = NULL;
+    robj *dstset = NULL;
+    sds elesds;
     int64_t intobj;
     void *replylen = NULL;
     unsigned long j, cardinality = 0;
@@ -839,7 +837,7 @@ void sinterGenericCommand(client *c, robj **setkeys,
      * the element against all the other sets, if at least one set does
      * not include the element it is discarded */
     si = setTypeInitIterator(sets[0]);
-    while((encoding = setTypeNext(si,&eleobj,&intobj)) != -1) {
+    while((encoding = setTypeNext(si,&elesds,&intobj)) != -1) {
         for (j = 1; j < setnum; j++) {
             if (sets[j] == sets[0]) continue;
             if (encoding == OBJ_ENCODING_INTSET) {
@@ -852,25 +850,15 @@ void sinterGenericCommand(client *c, robj **setkeys,
                  * have to use the generic function, creating an object
                  * for this */
                 } else if (sets[j]->encoding == OBJ_ENCODING_HT) {
-                    eleobj = createStringObjectFromLongLong(intobj);
-                    if (!setTypeIsMember(sets[j],eleobj)) {
-                        decrRefCount(eleobj);
+                    elesds = sdsfromlonglong(intobj);
+                    if (!setTypeIsMember(sets[j],elesds)) {
+                        sdsfree(elesds);
                         break;
                     }
-                    decrRefCount(eleobj);
+                    sdsfree(elesds);
                 }
             } else if (encoding == OBJ_ENCODING_HT) {
-                /* Optimization... if the source object is integer
-                 * encoded AND the target set is an intset, we can get
-                 * a much faster path. */
-                if (eleobj->encoding == OBJ_ENCODING_INT &&
-                    sets[j]->encoding == OBJ_ENCODING_INTSET &&
-                    !intsetFind((intset*)sets[j]->ptr,(long)eleobj->ptr))
-                {
-                    break;
-                /* else... object to object check is easy as we use the
-                 * type agnostic API here. */
-                } else if (!setTypeIsMember(sets[j],eleobj)) {
+                if (!setTypeIsMember(sets[j],elesds)) {
                     break;
                 }
             }
@@ -880,17 +868,17 @@ void sinterGenericCommand(client *c, robj **setkeys,
         if (j == setnum) {
             if (!dstkey) {
                 if (encoding == OBJ_ENCODING_HT)
-                    addReplyBulk(c,eleobj);
+                    addReplyBulkCBuffer(c,elesds,sdslen(elesds));
                 else
                     addReplyBulkLongLong(c,intobj);
                 cardinality++;
             } else {
                 if (encoding == OBJ_ENCODING_INTSET) {
-                    eleobj = createStringObjectFromLongLong(intobj);
-                    setTypeAdd(dstset,eleobj);
-                    decrRefCount(eleobj);
+                    elesds = sdsfromlonglong(intobj);
+                    setTypeAdd(dstset,elesds);
+                    sdsfree(elesds);
                 } else {
-                    setTypeAdd(dstset,eleobj);
+                    setTypeAdd(dstset,elesds);
                 }
             }
         }
@@ -937,7 +925,8 @@ void sunionDiffGenericCommand(client *c, robj **setkeys, int setnum,
                               robj *dstkey, int op) {
     robj **sets = zmalloc(sizeof(robj*)*setnum);
     setTypeIterator *si;
-    robj *ele, *dstset = NULL;
+    robj *dstset = NULL;
+    sds ele;
     int j, cardinality = 0;
     int diff_algo = 1;
 
@@ -1003,7 +992,7 @@ void sunionDiffGenericCommand(client *c, robj **setkeys, int setnum,
             si = setTypeInitIterator(sets[j]);
             while((ele = setTypeNextObject(si)) != NULL) {
                 if (setTypeAdd(dstset,ele)) cardinality++;
-                decrRefCount(ele);
+                sdsfree(ele);
             }
             setTypeReleaseIterator(si);
         }
@@ -1028,7 +1017,7 @@ void sunionDiffGenericCommand(client *c, robj **setkeys, int setnum,
                 setTypeAdd(dstset,ele);
                 cardinality++;
             }
-            decrRefCount(ele);
+            sdsfree(ele);
         }
         setTypeReleaseIterator(si);
     } else if (op == SET_OP_DIFF && sets[0] && diff_algo == 2) {
@@ -1049,7 +1038,7 @@ void sunionDiffGenericCommand(client *c, robj **setkeys, int setnum,
                 } else {
                     if (setTypeRemove(dstset,ele)) cardinality--;
                 }
-                decrRefCount(ele);
+                sdsfree(ele);
             }
             setTypeReleaseIterator(si);
 
@@ -1064,8 +1053,8 @@ void sunionDiffGenericCommand(client *c, robj **setkeys, int setnum,
         addReplyMultiBulkLen(c,cardinality);
         si = setTypeInitIterator(dstset);
         while((ele = setTypeNextObject(si)) != NULL) {
-            addReplyBulk(c,ele);
-            decrRefCount(ele);
+            addReplyBulkCBuffer(c,ele,sdslen(ele));
+            sdsfree(ele);
         }
         setTypeReleaseIterator(si);
         decrRefCount(dstset);