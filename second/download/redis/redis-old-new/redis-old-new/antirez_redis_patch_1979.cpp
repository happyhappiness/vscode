@@ -469,7 +469,7 @@ void sunionDiffGenericCommand(redisClient *c, robj **setkeys, int setnum, robj *
 
     /* Output the content of the resulting set, if not in STORE mode */
     if (!dstkey) {
-        addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",cardinality));
+        addReplyMultiBulkLen(c,cardinality);
         si = setTypeInitIterator(dstset);
         while((ele = setTypeNext(si)) != NULL) {
             addReplyBulk(c,ele);