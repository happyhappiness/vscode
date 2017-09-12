@@ -320,7 +320,8 @@ int qsortCompareSetsByCardinality(const void *s1, const void *s2) {
 void sinterGenericCommand(redisClient *c, robj **setkeys, unsigned long setnum, robj *dstkey) {
     robj **sets = zmalloc(sizeof(robj*)*setnum);
     setTypeIterator *si;
-    robj *ele, *lenobj = NULL, *dstset = NULL;
+    robj *ele, *dstset = NULL;
+    void *replylen = NULL;
     unsigned long j, cardinality = 0;
 
     for (j = 0; j < setnum; j++) {
@@ -356,9 +357,7 @@ void sinterGenericCommand(redisClient *c, robj **setkeys, unsigned long setnum,
      * to the output list and save the pointer to later modify it with the
      * right length */
     if (!dstkey) {
-        lenobj = createObject(REDIS_STRING,NULL);
-        addReply(c,lenobj);
-        decrRefCount(lenobj);
+        replylen = addDeferredMultiBulkLength(c);
     } else {
         /* If we have a target key where to store the resulting set
          * create this key with an empty set inside */
@@ -400,7 +399,7 @@ void sinterGenericCommand(redisClient *c, robj **setkeys, unsigned long setnum,
         touchWatchedKey(c->db,dstkey);
         server.dirty++;
     } else {
-        lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",cardinality);
+        setDeferredMultiBulkLength(c,replylen,cardinality);
     }
     zfree(sets);
 }