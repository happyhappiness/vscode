@@ -33,7 +33,7 @@
  * Set Commands
  *----------------------------------------------------------------------------*/
 
-void sunionDiffGenericCommand(redisClient *c, robj **setkeys, int setnum, 
+void sunionDiffGenericCommand(redisClient *c, robj **setkeys, int setnum,
                               robj *dstkey, int op);
 
 /* Factory method to return a set that *can* hold "value". When the object has
@@ -208,7 +208,7 @@ int setTypeRandomElement(robj *setobj, robj **objele, int64_t *llele) {
 }
 
 /* Return a number of random elements from a non empty set.
- * 
+ *
  * This is a version of setTypeRandomElement() that is modified in order to
  * return multiple entries, using dictGetRandomKeys() and intsetRandomMembers().
  *
@@ -223,80 +223,86 @@ int setTypeRandomElement(robj *setobj, robj **objele, int64_t *llele) {
  * of continuous elements to run some kind of algorithm or to produce
  * statistics. However the function is much faster than setTypeRandomElement()
  * at producing N elements, and the elements are guaranteed to be non
- * repeating. 
+ * repeating.
  */
-unsigned long setTypeRandomElements(robj *set, unsigned long count, robj *aux_set) {
+unsigned long setTypeRandomElements(robj *set, unsigned long count,
+                                    robj *aux_set) {
     unsigned long set_size;
     unsigned long elements_to_return = count;
     unsigned long elements_copied = 0;
     unsigned long current_element = 0;
 
-    /* Like all setType* functions, we assume good behavior on part of the caller,
-     * so no extra parameter checks are made. */
+    /* Like all setType* functions, we assume good behavior on part of the
+     * caller, so no extra parameter checks are made. */
 
-    /* If the number of elements in the the set is less than the count 
-       requested, just return all of them. */
+    /* If the number of elements in the the set is less than the count
+     * requested, just return all of them. */
     set_size = setTypeSize(set);
     if (set_size < count) {
         elements_to_return = set_size;
     }
 
-    /* TODO: It is definitely faster adding items to the set by directly handling the Dict
-       or intset inside it, avoiding the constant encoding checks inside setTypeAdd(). 
-       However, We don't want to touch the set internals in non setType* functions.
-       So, we just call setTypeAdd() multiple times, but this isn't an optimial
-       solution. 
-       Another option would be to create a bulk-add function: setTypeAddBulk(). */
+    /* TODO: It is definitely faster adding items to the set by directly
+     * handling the Dict or intset inside it, avoiding the constant encoding
+     * checks inside setTypeAdd(). However, We don't want to touch the set
+     * internals in non setType* functions. So, we just call setTypeAdd()
+     * multiple times, but this isn't an optimal solution.
+     * Another option would be to create a bulk-add function:
+     * setTypeAddBulk(). */
     if (set->encoding == REDIS_ENCODING_HT) {
         /* Allocate result array */
-        dictEntry **random_elements = 
+        dictEntry **random_elements =
             zmalloc(sizeof(dictEntry*) * elements_to_return);
 
         /* Get the random elements */
-        elements_copied = 
+        elements_copied =
             dictGetRandomKeys(set->ptr, random_elements, elements_to_return);
         redisAssert(elements_copied == elements_to_return);
 
         /* Put them into the set */
-        for (current_element = 0;
-             current_element < elements_copied;
+        for (current_element = 0; current_element < elements_copied;
              current_element++) {
 
             /* We get the key and duplicate it, as we know it is a string */
-            setTypeAdd(aux_set, 
-                dupStringObject(dictGetKey(random_elements[current_element])));
+            setTypeAdd(aux_set,
+                dictGetKey(random_elements[current_element]));
         }
 
         zfree(random_elements);
 
     } else if (set->encoding == REDIS_ENCODING_INTSET) {
         /* Allocate result array */
-        int64_t *random_elements = zmalloc(sizeof(int64_t) * elements_to_return);
+        int64_t *random_elements =
+            zmalloc(sizeof(int64_t) * elements_to_return);
+        robj* element_as_str = NULL;
 
-        elements_copied = 
-            intsetRandomMembers((intset*) set->ptr, 
-                                random_elements, 
+        elements_copied =
+            intsetRandomMembers((intset*) set->ptr,
+                                random_elements,
                                 elements_to_return);
 
         redisAssert(elements_copied == elements_to_return);
 
         /* Put them into the set */
-        for (current_element = 0;
-             current_element < elements_copied;
+        for (current_element = 0; current_element < elements_copied;
              current_element++) {
 
+            element_as_str = createStringObjectFromLongLong(
+                    random_elements[current_element]);
+
             /* Put the values in the set */
-            setTypeAdd(aux_set, 
-                       createStringObjectFromLongLong(
-                            random_elements[current_element]));
+            setTypeAdd(aux_set,
+                       element_as_str);
+
+            decrRefCount(element_as_str);
         }
 
         zfree(random_elements);
     } else {
         redisPanic("Unknown set encoding");
     }
 
-    /* We have a set with random elements. Return the actual elements in 
+    /* We have a set with random elements. Return the actual elements in
        the aux_set. */
     return elements_copied;
 }
@@ -493,31 +499,31 @@ void spopWithCountCommand(redisClient *c) {
         return;
     }
 
-    /* Make sure a key with the name inputted exists, and that it's type is 
-       indeed a set. Otherwise, return nil */
+    /* Make sure a key with the name inputted exists, and that it's type is
+     * indeed a set. Otherwise, return nil */
     if ((set = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk))
         == NULL || checkType(c,set,REDIS_SET)) return;
 
-    /* If count is zero, serve an empty multibulk ASAP to avoid special 
-       cases later. */
+    /* If count is zero, serve an empty multibulk ASAP to avoid special
+     * cases later. */
     if (count == 0) {
         addReply(c,shared.emptymultibulk);
         return;
     }
 
     /* Get the size of the set. It is always > 0, as empty sets get
-       deleted.  */
+     * deleted.  */
     size = setTypeSize(set);
 
     /* Generate an SPOP keyspace notification */
     notifyKeyspaceEvent(REDIS_NOTIFY_SET,"spop",c->argv[1],c->db->id);
 
     /* CASE 1:
-     * The number of requested elements is greater than or equal to 
+     * The number of requested elements is greater than or equal to
      * the number of elements inside the set: simply return the whole set. */
     if (count >= size) {
 
-        /* We just return the entire set */ 
+        /* We just return the entire set */
         sunionDiffGenericCommand(c,c->argv+1,1,NULL,REDIS_OP_UNION);
 
         /* Delete the set as it is now empty */
@@ -536,14 +542,14 @@ void spopWithCountCommand(redisClient *c) {
      * The number of requested elements is less than the number
      * of elements inside the set. */
 
-    /* We need an auxiliary set. Optimistically, we create a set using an 
-       Intset internally. */
+    /* We need an auxiliary set. Optimistically, we create a set using an
+     * Intset internally. */
     aux = createStringObjectFromLongLong(0);
     aux_set = setTypeCreate(aux);
     decrRefCount(aux);
 
-    /* Get the count requested of random elements from the set into our 
-       auxiliary set. */
+    /* Get the count requested of random elements from the set into our
+     * auxiliary set. */
     elements_returned = setTypeRandomElements(set, count, aux_set);
     redisAssert(elements_returned == count);
 
@@ -568,8 +574,8 @@ void spopWithCountCommand(redisClient *c) {
                 setTypeRemove(set, objele);
             }
             else if (element_encoding == REDIS_ENCODING_INTSET) {
-                /* TODO: setTypeRemove() forces us to convert all of the ints 
-                         to string... isn't there a nicer way to do this? */
+                /* TODO: setTypeRemove() forces us to convert all of the ints
+                 *       to string... isn't there a nicer way to do this? */
                 objele = createStringObjectFromLongLong(llele);
                 addReplyBulk(c, objele);
 
@@ -590,7 +596,7 @@ void spopWithCountCommand(redisClient *c) {
     }
 
     /* Free the auxiliary set - we need it no more. */
-    freeSetObject(aux_set);
+    decrRefCount(aux_set);
 }
 
 void spopCommand(redisClient *c) {
@@ -606,8 +612,8 @@ void spopCommand(redisClient *c) {
         return;
     }
 
-    /* Make sure a key with the name inputted exists, and that it's type is 
-       indeed a set */
+    /* Make sure a key with the name inputted exists, and that it's type is
+     * indeed a set */
     if ((set = lookupKeyWriteOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
         checkType(c,set,REDIS_SET)) return;
 
@@ -822,7 +828,7 @@ int qsortCompareSetsByRevCardinality(const void *s1, const void *s2) {
     return  (o2 ? setTypeSize(o2) : 0) - (o1 ? setTypeSize(o1) : 0);
 }
 
-void sinterGenericCommand(redisClient *c, robj **setkeys, 
+void sinterGenericCommand(redisClient *c, robj **setkeys,
                           unsigned long setnum, robj *dstkey) {
     robj **sets = zmalloc(sizeof(robj*)*setnum);
     setTypeIterator *si;
@@ -970,7 +976,7 @@ void sinterstoreCommand(redisClient *c) {
 #define REDIS_OP_DIFF 1
 #define REDIS_OP_INTER 2
 
-void sunionDiffGenericCommand(redisClient *c, robj **setkeys, int setnum, 
+void sunionDiffGenericCommand(redisClient *c, robj **setkeys, int setnum,
                               robj *dstkey, int op) {
     robj **sets = zmalloc(sizeof(robj*)*setnum);
     setTypeIterator *si;