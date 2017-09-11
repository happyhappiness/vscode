@@ -33,7 +33,8 @@
  * Set Commands
  *----------------------------------------------------------------------------*/
 
-void sunionDiffGenericCommand(redisClient *c, robj **setkeys, int setnum, robj *dstkey, int op);
+void sunionDiffGenericCommand(redisClient *c, robj **setkeys, int setnum, 
+                              robj *dstkey, int op);
 
 /* Factory method to return a set that *can* hold "value". When the object has
  * an integer-encodable value, an intset will be returned. Otherwise a regular
@@ -68,7 +69,8 @@ int setTypeAdd(robj *subject, robj *value) {
 
             /* The set *was* an intset and this value is not integer
              * encodable, so dictAdd should always work. */
-            redisAssertWithInfo(NULL,value,dictAdd(subject->ptr,value,NULL) == DICT_OK);
+            redisAssertWithInfo(NULL,value,
+                                dictAdd(subject->ptr,value,NULL) == DICT_OK);
             incrRefCount(value);
             return 1;
         }
@@ -205,6 +207,100 @@ int setTypeRandomElement(robj *setobj, robj **objele, int64_t *llele) {
     return setobj->encoding;
 }
 
+/* Return a number of random elements from a non empty set.
+ * 
+ * This is a version of setTypeRandomElement() that is modified in order to
+ * return multiple entries, using dictGetRandomKeys() and intsetRandomMembers().
+ *
+ * The elements are stored into 'aux_set' which should be of a set type.
+ *
+ * The function returns the number of items stored into 'aux_set', that may
+ * be less than 'count' if the hash table has less than 'count' elements
+ * inside.
+ *
+ * Note that this function is not suitable when you need a good distribution
+ * of the returned items, but only when you need to "sample" a given number
+ * of continuous elements to run some kind of algorithm or to produce
+ * statistics. However the function is much faster than setTypeRandomElement()
+ * at producing N elements, and the elements are guaranteed to be non
+ * repeating. 
+ */
+int setTypeRandomElements(robj *set, int count, robj *aux_set) {
+    int set_size;
+    int elements_to_return = count;
+    int elements_copied = 0;
+    int current_element = 0;
+
+    /* Like all setType* functions, we assume good behavior on part of the caller,
+     * so no extra parameter checks are made. */
+
+    /* If the number of elements in the the set is less than the count 
+       requested, just return all of them. */
+    set_size = setTypeSize(set);
+    if (set_size < count) {
+        elements_to_return = set_size;
+    }
+
+    /* TODO: It is definitely faster adding items to the set by directly handling the Dict
+       or intset inside it, avoiding the constant encoding checks inside setTypeAdd(). 
+       However, We don't want to touch the set internals in non setType* functions.
+       So, we just call setTypeAdd() multiple times, but this isn't an optimial
+       solution. 
+       Another option would be to create a bulk-add function: setTypeAddBulk(). */
+    if (set->encoding == REDIS_ENCODING_HT) {
+        /* Allocate result array */
+        dictEntry **random_elements = 
+            zmalloc(sizeof(dictEntry*) * elements_to_return);
+
+        /* Get the random elements */
+        elements_copied = 
+            dictGetRandomKeys(set->ptr, random_elements, elements_to_return);
+        redisAssert(elements_copied == elements_to_return);
+
+        /* Put them into the set */
+        for (current_element = 0;
+             current_element < elements_copied;
+             current_element++) {
+
+            /* We get the key and duplicate it, as we know it is a string */
+            setTypeAdd(aux_set, 
+                dupStringObject(dictGetKey(random_elements[current_element])));
+        }
+
+        zfree(random_elements);
+
+    } else if (set->encoding == REDIS_ENCODING_INTSET) {
+        /* Allocate result array */
+        int64_t *random_elements = zmalloc(sizeof(int64_t) * elements_to_return);
+
+        elements_copied = 
+            intsetRandomMembers((intset*) set->ptr, 
+                                random_elements, 
+                                elements_to_return);
+
+        redisAssert(elements_copied == elements_to_return);
+
+        /* Put them into the set */
+        for (current_element = 0;
+             current_element < elements_copied;
+             current_element++) {
+
+            /* Put the values in the set */
+            setTypeAdd(aux_set, 
+                       createStringObjectFromLongLong(
+                            random_elements[current_element]));
+        }
+
+        zfree(random_elements);
+    } else {
+        redisPanic("Unknown set encoding");
+    }
+
+    /* We have a set with random elements. Return the actual elements in 
+       the aux_set. */
+    return elements_copied;
+}
+
 unsigned long setTypeSize(robj *subject) {
     if (subject->encoding == REDIS_ENCODING_HT) {
         return dictSize((dict*)subject->ptr);
@@ -235,7 +331,8 @@ void setTypeConvert(robj *setobj, int enc) {
         si = setTypeInitIterator(setobj);
         while (setTypeNext(si,NULL,&intele) != -1) {
             element = createStringObjectFromLongLong(intele);
-            redisAssertWithInfo(NULL,element,dictAdd(d,element,NULL) == DICT_OK);
+            redisAssertWithInfo(NULL,element,
+                                dictAdd(d,element,NULL) == DICT_OK);
         }
         setTypeReleaseIterator(si);
 
@@ -377,22 +474,155 @@ void scardCommand(redisClient *c) {
     addReplyLongLong(c,setTypeSize(o));
 }
 
+/* handle the "SPOP key <count>" variant. The normal version of the
+ * command is handled by the spopCommand() function itself. */
+
+void spopWithCountCommand(redisClient *c) {
+    long l;
+    unsigned long count, size;
+    int elements_returned;
+    robj *set, *aux, *aux_set;
+    int64_t llele;
+
+    /* Get the count argument */
+    if (getLongFromObjectOrReply(c,c->argv[2],&l,NULL) != REDIS_OK) return;
+    if (l >= 0) {
+        count = (unsigned) l;
+    } else {
+        addReply(c,shared.outofrangeerr);
+        return;
+    }
+
+    /* Make sure a key with the name inputted exists, and that it's type is 
+       indeed a set. Otherwise, return nil */
+    if ((set = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk))
+        == NULL || checkType(c,set,REDIS_SET)) return;
+
+    /* If count is zero, serve an empty multibulk ASAP to avoid special 
+       cases later. */
+    if (count == 0) {
+        addReply(c,shared.emptymultibulk);
+        return;
+    }
+
+    /* Get the size of the set. It is always > 0, as empty sets get
+       deleted.  */
+    size = setTypeSize(set);
+
+    /* Generate an SPOP keyspace notification */
+    notifyKeyspaceEvent(REDIS_NOTIFY_SET,"spop",c->argv[1],c->db->id);
+
+    /* CASE 1:
+     * The number of requested elements is greater than or equal to 
+     * the number of elements inside the set: simply return the whole set. */
+    if (count >= size) {
+
+        /* We just return the entire set */ 
+        sunionDiffGenericCommand(c,c->argv+1,1,NULL,REDIS_OP_UNION);
+
+        /* Delete the set as it is now empty */
+        dbDelete(c->db,c->argv[1]);
+        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
+
+        /* Replicate/AOF this command as an SREM operation */
+        aux = createStringObject("DEL",3);
+        rewriteClientCommandVector(c,2,aux,c->argv[1]);
+        decrRefCount(aux);
+
+        return;
+    }
+
+    /* CASE 2:
+     * The number of requested elements is less than the number
+     * of elements inside the set. */
+
+    /* We need an auxiliary set. Optimistically, we create a set using an 
+       Intset internally. */
+    aux = createStringObjectFromLongLong(0);
+    aux_set = setTypeCreate(aux);
+    decrRefCount(aux);
+
+    /* Get the count requested of random elements from the set into our 
+       auxiliary set. */
+    elements_returned = setTypeRandomElements(set, count, aux_set);
+    redisAssert(elements_returned == count);
+
+    {
+        setTypeIterator *si;
+        robj *objele;
+        int element_encoding;
+
+        addReplyMultiBulkLen(c, elements_returned);
+
+        /* Replicate/AOF this command as an SREM operation */
+        aux = createStringObject("SREM",4);
+
+        si = setTypeInitIterator(aux_set);
+        while ((element_encoding = setTypeNext(si, &objele, &llele)) != -1) {
+            if (element_encoding == REDIS_ENCODING_HT) {
+
+                addReplyBulk(c, objele);
+
+                /* Replicate/AOF this command as an SREM commands */
+                rewriteClientCommandVector(c, 3, aux, c->argv[1], objele);
+                setTypeRemove(set, objele);
+            }
+            else if (element_encoding == REDIS_ENCODING_INTSET) {
+                /* TODO: setTypeRemove() forces us to convert all of the ints 
+                         to string... isn't there a nicer way to do this? */
+                objele = createStringObjectFromLongLong(llele);
+                addReplyBulk(c, objele);
+
+                /* Replicate/AOF this command as an SREM commands */
+                rewriteClientCommandVector(c, 3, aux, c->argv[1], objele);
+                setTypeRemove(set, objele);
+
+                /* We created it, we kill it. */
+                decrRefCount(objele);
+            }
+            else {
+                redisPanic("Unknown set encoding");
+            }
+        }
+        setTypeReleaseIterator(si);
+
+        decrRefCount(aux);
+    }
+
+    /* Free the auxiliary set - we need it no more. */
+    freeSetObject(aux_set);
+}
+
 void spopCommand(redisClient *c) {
     robj *set, *ele, *aux;
     int64_t llele;
     int encoding;
 
+    if (c->argc == 3) {
+        spopWithCountCommand(c);
+        return;
+    } else if (c->argc > 3) {
+        addReply(c,shared.syntaxerr);
+        return;
+    }
+
+    /* Make sure a key with the name inputted exists, and that it's type is 
+       indeed a set */
     if ((set = lookupKeyWriteOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
         checkType(c,set,REDIS_SET)) return;
 
+    /* Get a random element from the set */
     encoding = setTypeRandomElement(set,&ele,&llele);
+
+    /* Remove the element from the set */
     if (encoding == REDIS_ENCODING_INTSET) {
         ele = createStringObjectFromLongLong(llele);
         set->ptr = intsetRemove(set->ptr,llele,NULL);
     } else {
         incrRefCount(ele);
         setTypeRemove(set,ele);
     }
+
     notifyKeyspaceEvent(REDIS_NOTIFY_SET,"spop",c->argv[1],c->db->id);
 
     /* Replicate/AOF this command as an SREM operation */
@@ -401,11 +631,16 @@ void spopCommand(redisClient *c) {
     decrRefCount(ele);
     decrRefCount(aux);
 
+    /* Add the element to the reply */
     addReplyBulk(c,ele);
+
+    /* Delete the set if it's empty */
     if (setTypeSize(set) == 0) {
         dbDelete(c->db,c->argv[1]);
         notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
     }
+
+    /* Set has been modified */
     signalModifiedKey(c->db,c->argv[1]);
     server.dirty++;
 }
@@ -587,7 +822,8 @@ int qsortCompareSetsByRevCardinality(const void *s1, const void *s2) {
     return  (o2 ? setTypeSize(o2) : 0) - (o1 ? setTypeSize(o1) : 0);
 }
 
-void sinterGenericCommand(redisClient *c, robj **setkeys, unsigned long setnum, robj *dstkey) {
+void sinterGenericCommand(redisClient *c, robj **setkeys, 
+                          unsigned long setnum, robj *dstkey) {
     robj **sets = zmalloc(sizeof(robj*)*setnum);
     setTypeIterator *si;
     robj *eleobj, *dstset = NULL;
@@ -734,7 +970,8 @@ void sinterstoreCommand(redisClient *c) {
 #define REDIS_OP_DIFF 1
 #define REDIS_OP_INTER 2
 
-void sunionDiffGenericCommand(redisClient *c, robj **setkeys, int setnum, robj *dstkey, int op) {
+void sunionDiffGenericCommand(redisClient *c, robj **setkeys, int setnum, 
+                              robj *dstkey, int op) {
     robj **sets = zmalloc(sizeof(robj*)*setnum);
     setTypeIterator *si;
     robj *ele, *dstset = NULL;