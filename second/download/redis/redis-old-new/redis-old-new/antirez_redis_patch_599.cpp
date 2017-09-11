@@ -212,106 +212,6 @@ int setTypeRandomElement(robj *setobj, robj **objele, int64_t *llele) {
     return setobj->encoding;
 }
 
-/* Return a number of random elements from a non empty set.
- *
- * This is a version of setTypeRandomElement() that is modified in order to
- * return multiple entries, using dictGetRandomKeys() and intsetRandomMembers().
- *
- * The elements are stored into 'aux_set' which should be of a set type.
- *
- * The function returns the number of items stored into 'aux_set', that may
- * be less than 'count' if the hash table has less than 'count' elements
- * inside.
- *
- * Note that this function is not suitable when you need a good distribution
- * of the returned items, but only when you need to "sample" a given number
- * of continuous elements to run some kind of algorithm or to produce
- * statistics. However the function is much faster than setTypeRandomElement()
- * at producing N elements, and the elements are guaranteed to be non
- * repeating.
- */
-unsigned long setTypeRandomElements(robj *set, unsigned long count,
-                                    robj *aux_set) {
-    unsigned long set_size;
-    unsigned long elements_to_return = count;
-    unsigned long elements_copied = 0;
-    unsigned long current_element = 0;
-
-    /* Like all setType* functions, we assume good behavior on part of the
-     * caller, so no extra parameter checks are made. */
-
-    /* If the number of elements in the the set is less than the count
-     * requested, just return all of them. */
-    set_size = setTypeSize(set);
-    if (set_size < count) {
-        elements_to_return = set_size;
-    }
-
-    /* TODO: It is definitely faster adding items to the set by directly
-     * handling the Dict or intset inside it, avoiding the constant encoding
-     * checks inside setTypeAdd(). However, We don't want to touch the set
-     * internals in non setType* functions. So, we just call setTypeAdd()
-     * multiple times, but this isn't an optimal solution.
-     * Another option would be to create a bulk-add function:
-     * setTypeAddBulk(). */
-    if (set->encoding == REDIS_ENCODING_HT) {
-        /* Allocate result array */
-        dictEntry **random_elements =
-            zmalloc(sizeof(dictEntry*) * elements_to_return);
-
-        /* Get the random elements */
-        elements_copied =
-            dictGetRandomKeys(set->ptr, random_elements, elements_to_return);
-        redisAssert(elements_copied == elements_to_return);
-
-        /* Put them into the set */
-        for (current_element = 0; current_element < elements_copied;
-             current_element++) {
-
-            /* We get the key and duplicate it, as we know it is a string */
-            setTypeAdd(aux_set,
-                dictGetKey(random_elements[current_element]));
-        }
-
-        zfree(random_elements);
-
-    } else if (set->encoding == REDIS_ENCODING_INTSET) {
-        /* Allocate result array */
-        int64_t *random_elements =
-            zmalloc(sizeof(int64_t) * elements_to_return);
-        robj* element_as_str = NULL;
-
-        elements_copied =
-            intsetRandomMembers((intset*) set->ptr,
-                                random_elements,
-                                elements_to_return);
-
-        redisAssert(elements_copied == elements_to_return);
-
-        /* Put them into the set */
-        for (current_element = 0; current_element < elements_copied;
-             current_element++) {
-
-            element_as_str = createStringObjectFromLongLong(
-                    random_elements[current_element]);
-
-            /* Put the values in the set */
-            setTypeAdd(aux_set,
-                       element_as_str);
-
-            decrRefCount(element_as_str);
-        }
-
-        zfree(random_elements);
-    } else {
-        redisPanic("Unknown set encoding");
-    }
-
-    /* We have a set with random elements. Return the actual elements in
-       the aux_set. */
-    return elements_copied;
-}
-
 unsigned long setTypeSize(robj *subject) {
     if (subject->encoding == REDIS_ENCODING_HT) {
         return dictSize((dict*)subject->ptr);
@@ -485,15 +385,18 @@ void scardCommand(redisClient *c) {
     addReplyLongLong(c,setTypeSize(o));
 }
 
-/* handle the "SPOP key <count>" variant. The normal version of the
+/* Handle the "SPOP key <count>" variant. The normal version of the
  * command is handled by the spopCommand() function itself. */
 
+/* How many times bigger should be the set compared to the remaining size
+ * for us to use the "create new set" strategy? Read later in the
+ * implementation for more info. */
+#define SPOP_MOVE_STRATEGY_MUL 5
+
 void spopWithCountCommand(redisClient *c) {
     long l;
     unsigned long count, size;
-    unsigned long elements_returned;
-    robj *set, *aux_set;
-    int64_t llele;
+    robj *set;
 
     /* Get the count argument */
     if (getLongFromObjectOrReply(c,c->argv[2],&l,NULL) != REDIS_OK) return;
@@ -516,12 +419,11 @@ void spopWithCountCommand(redisClient *c) {
         return;
     }
 
-    /* Get the size of the set. It is always > 0, as empty sets get
-     * deleted.  */
     size = setTypeSize(set);
 
     /* Generate an SPOP keyspace notification */
     notifyKeyspaceEvent(REDIS_NOTIFY_SET,"spop",c->argv[1],c->db->id);
+    server.dirty += count;
 
     /* CASE 1:
      * The number of requested elements is greater than or equal to
@@ -534,64 +436,102 @@ void spopWithCountCommand(redisClient *c) {
         dbDelete(c->db,c->argv[1]);
         notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
 
-        /* Replicate/AOF this command as an SREM operation */
+        /* Propagate this command as an DEL operation */
         rewriteClientCommandVector(c,2,shared.del,c->argv[1]);
         signalModifiedKey(c->db,c->argv[1]);
         server.dirty++;
         return;
     }
 
-    /* CASE 2:
-     * The number of requested elements is less than the number
-     * of elements inside the set. */
-
-    /* We need an auxiliary set. Optimistically, we create a set using an
-     * Intset internally. */
-    aux_set = createIntsetObject();
-
-    /* Get the count requested of random elements from the set into our
-     * auxiliary set. */
-    elements_returned = setTypeRandomElements(set, count, aux_set);
-    redisAssert(elements_returned == count);
+    /* Case 2 and 3 require to replicate SPOP as a set of SERM commands.
+     * Prepare our replication argument vector. Also send the array length
+     * which is common to both the code paths. */
+    robj *propargv[3];
+    propargv[0] = createStringObject("SREM",4);
+    propargv[1] = c->argv[1];
+    addReplyMultiBulkLen(c,count);
 
-    {
-        setTypeIterator *si;
-        robj *objele, *propargv[3];
-        int element_encoding;
-
-        addReplyMultiBulkLen(c, elements_returned);
-        propargv[0] = createStringObject("SREM",4);
-        propargv[1] = c->argv[1];
+    /* Common iteration vars. */
+    robj *objele;
+    int encoding;
+    int64_t llele;
+    unsigned long remaining = size-count; /* Elements left after SPOP. */
 
-        si = setTypeInitIterator(aux_set);
-        while ((element_encoding = setTypeNext(si, &objele, &llele)) != -1) {
-            if (element_encoding == REDIS_ENCODING_HT) {
-                incrRefCount(objele);
-            } else if (element_encoding == REDIS_ENCODING_INTSET) {
+    /* If we are here, the number of requested elements is less than the
+     * number of elements inside the set. Also we are sure that count < size.
+     * Use two different strategies.
+     *
+     * CASE 2: The number of elements to return is small compared to the
+     * set size. We can just extract random elements and return them to
+     * the set. */
+    if (remaining*SPOP_MOVE_STRATEGY_MUL > count) {
+        while(count--) {
+            encoding = setTypeRandomElement(set,&objele,&llele);
+            if (encoding == REDIS_ENCODING_INTSET) {
                 objele = createStringObjectFromLongLong(llele);
             } else {
-                redisPanic("Unknown set encoding");
+                incrRefCount(objele);
             }
-            setTypeRemove(set, objele);
-            addReplyBulk(c, objele);
+
+            /* Return the element to the client and remove from the set. */
+            addReplyBulk(c,objele);
+            setTypeRemove(set,objele);
 
             /* Replicate/AOF this command as an SREM operation */
             propargv[2] = objele;
-            alsoPropagate(server.sremCommand,c->db->id,propargv,3,REDIS_PROPAGATE_AOF|REDIS_PROPAGATE_REPL);
-
+            alsoPropagate(server.sremCommand,c->db->id,propargv,3,
+                REDIS_PROPAGATE_AOF|REDIS_PROPAGATE_REPL);
+            decrRefCount(objele);
+        }
+    } else {
+    /* CASE 3: The number of elements to return is very big, approaching
+     * the size of the set itself. After some time extracting random elements
+     * from such a set becomes computationally expensive, so we use
+     * a different strategy, we extract random elements that we don't
+     * want to return (the elements that will remain part of the set),
+     * creating a new set as we do this (that will be stored as the original
+     * set). Then we return the elements left in the original set and
+     * release it. */
+        robj *newset = NULL;
+
+        /* Create a new set with just the remaining elements. */
+        while(remaining--) {
+            encoding = setTypeRandomElement(set,&objele,&llele);
+            if (encoding == REDIS_ENCODING_INTSET) {
+                objele = createStringObjectFromLongLong(llele);
+            } else {
+                incrRefCount(objele);
+            }
+            if (!newset) newset = setTypeCreate(objele);
+            setTypeAdd(newset,objele);
+            setTypeRemove(set,objele);
             decrRefCount(objele);
-            server.dirty++;
         }
-        decrRefCount(propargv[0]);
+
+        /* Assign the new set as the key value. */
+        incrRefCount(set); /* Protect the old set value. */
+        dbOverwrite(c->db,c->argv[1],newset);
+
+        /* Tranfer the old set to the client and release it. */
+        setTypeIterator *si;
+        si = setTypeInitIterator(set);
+        while((encoding = setTypeNext(si,&objele,&llele)) != -1) {
+            if (encoding == REDIS_ENCODING_INTSET) {
+                addReplyBulkLongLong(c,llele);
+            } else {
+                addReplyBulk(c,objele);
+            }
+        }
         setTypeReleaseIterator(si);
+        decrRefCount(set);
     }
 
     /* Don't propagate the command itself even if we incremented the
      * dirty counter. We don't want to propagate an SPOP command since
      * we propagated the command as a set of SREMs operations using
      * the alsoPropagate() API. */
+    decrRefCount(propargv[0]);
     preventCommandPropagation(c);
-    decrRefCount(aux_set);
 }
 
 void spopCommand(redisClient *c) {