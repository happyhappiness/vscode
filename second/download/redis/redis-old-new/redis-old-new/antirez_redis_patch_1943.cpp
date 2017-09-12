@@ -307,7 +307,7 @@ void sortCommand(redisClient *c) {
     outputlen = getop ? getop*(end-start+1) : end-start+1;
     if (storekey == NULL) {
         /* STORE option not specified, sent the sorting result to client */
-        addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",outputlen));
+        addReplyMultiBulkLen(c,outputlen);
         for (j = start; j <= end; j++) {
             listNode *ln;
             listIter li;
@@ -369,7 +369,7 @@ void sortCommand(redisClient *c) {
          * replaced. */
         server.dirty += 1+outputlen;
         touchWatchedKey(c->db,storekey);
-        addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",outputlen));
+        addReplyLongLong(c,outputlen);
     }
 
     /* Cleanup */