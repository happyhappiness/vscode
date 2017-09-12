@@ -276,7 +276,7 @@ void scardCommand(redisClient *c) {
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,o,REDIS_SET)) return;
 
-    addReplyUlong(c,setTypeSize(o));
+    addReplyLongLong(c,setTypeSize(o));
 }
 
 void spopCommand(redisClient *c) {
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
@@ -470,7 +469,7 @@ void sunionDiffGenericCommand(redisClient *c, robj **setkeys, int setnum, robj *
 
     /* Output the content of the resulting set, if not in STORE mode */
     if (!dstkey) {
-        addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",cardinality));
+        addReplyMultiBulkLen(c,cardinality);
         si = setTypeInitIterator(dstset);
         while((ele = setTypeNext(si)) != NULL) {
             addReplyBulk(c,ele);