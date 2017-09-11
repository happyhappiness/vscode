@@ -45,6 +45,11 @@ robj *setTypeCreate(robj *value) {
     return createSetObject();
 }
 
+/* Add the specified value into a set. The function takes care of incrementing
+ * the reference count of the object if needed in order to retain a copy.
+ *
+ * If the value was already member of the set, nothing is done and 0 is
+ * returned, otherwise the new element is added and 1 is returned. */
 int setTypeAdd(robj *subject, robj *value) {
     long long llval;
     if (subject->encoding == REDIS_ENCODING_HT) {
@@ -487,7 +492,7 @@ void spopWithCountCommand(redisClient *c) {
     long l;
     unsigned long count, size;
     unsigned long elements_returned;
-    robj *set, *aux, *aux_set;
+    robj *set, *aux_set;
     int64_t llele;
 
     /* Get the count argument */
@@ -522,7 +527,6 @@ void spopWithCountCommand(redisClient *c) {
      * The number of requested elements is greater than or equal to
      * the number of elements inside the set: simply return the whole set. */
     if (count >= size) {
-
         /* We just return the entire set */
         sunionDiffGenericCommand(c,c->argv+1,1,NULL,REDIS_OP_UNION);
 
@@ -531,10 +535,9 @@ void spopWithCountCommand(redisClient *c) {
         notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
 
         /* Replicate/AOF this command as an SREM operation */
-        aux = createStringObject("DEL",3);
-        rewriteClientCommandVector(c,2,aux,c->argv[1]);
-        decrRefCount(aux);
-
+        rewriteClientCommandVector(c,2,shared.del,c->argv[1]);
+        signalModifiedKey(c->db,c->argv[1]);
+        server.dirty++;
         return;
     }
 
@@ -544,9 +547,7 @@ void spopWithCountCommand(redisClient *c) {
 
     /* We need an auxiliary set. Optimistically, we create a set using an
      * Intset internally. */
-    aux = createStringObjectFromLongLong(0);
-    aux_set = setTypeCreate(aux);
-    decrRefCount(aux);
+    aux_set = createIntsetObject();
 
     /* Get the count requested of random elements from the set into our
      * auxiliary set. */
@@ -555,47 +556,43 @@ void spopWithCountCommand(redisClient *c) {
 
     {
         setTypeIterator *si;
-        robj *objele;
+        robj *objele, **propargv;
         int element_encoding;
 
         addReplyMultiBulkLen(c, elements_returned);
 
-        /* Replicate/AOF this command as an SREM operation */
-        aux = createStringObject("SREM",4);
-
         si = setTypeInitIterator(aux_set);
         while ((element_encoding = setTypeNext(si, &objele, &llele)) != -1) {
             if (element_encoding == REDIS_ENCODING_HT) {
-
-                addReplyBulk(c, objele);
-
-                /* Replicate/AOF this command as an SREM commands */
-                rewriteClientCommandVector(c, 3, aux, c->argv[1], objele);
-                setTypeRemove(set, objele);
-            }
-            else if (element_encoding == REDIS_ENCODING_INTSET) {
-                /* TODO: setTypeRemove() forces us to convert all of the ints
-                 *       to string... isn't there a nicer way to do this? */
+                incrRefCount(objele);
+            } else if (element_encoding == REDIS_ENCODING_INTSET) {
                 objele = createStringObjectFromLongLong(llele);
-                addReplyBulk(c, objele);
-
-                /* Replicate/AOF this command as an SREM commands */
-                rewriteClientCommandVector(c, 3, aux, c->argv[1], objele);
-                setTypeRemove(set, objele);
-
-                /* We created it, we kill it. */
-                decrRefCount(objele);
-            }
-            else {
+            } else {
                 redisPanic("Unknown set encoding");
             }
+            setTypeRemove(set, objele);
+            addReplyBulk(c, objele);
+
+            /* Replicate/AOF this command as an SREM operation */
+            propargv = zmalloc(sizeof(robj*)*3);
+            propargv[0] = createStringObject("SREM",4);
+            propargv[1] = c->argv[1];
+            incrRefCount(c->argv[1]);
+            propargv[2] = objele;
+            incrRefCount(objele);
+
+            alsoPropagate(server.sremCommand,c->db->id,propargv,3,REDIS_PROPAGATE_AOF|REDIS_PROPAGATE_REPL);
+            decrRefCount(objele);
+            server.dirty++;
         }
         setTypeReleaseIterator(si);
-
-        decrRefCount(aux);
     }
 
-    /* Free the auxiliary set - we need it no more. */
+    /* Don't propagate the command itself even if we incremented the
+     * dirty counter. We don't want to propagate an SPOP command since
+     * we propagated the command as a set of SREMs operations using
+     * the alsoPropagate() API. */
+    preventCommandPropagation(c);
     decrRefCount(aux_set);
 }
 