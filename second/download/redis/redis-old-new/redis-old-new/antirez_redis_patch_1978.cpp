@@ -494,7 +494,7 @@ void lrangeCommand(redisClient *c) {
     rangelen = (end-start)+1;
 
     /* Return the result in form of a multi-bulk reply */
-    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
+    addReplyMultiBulkLen(c,rangelen);
     listTypeIterator *li = listTypeInitIterator(o,start,REDIS_TAIL);
     for (j = 0; j < rangelen; j++) {
         redisAssert(listTypeNext(li,&entry));
@@ -772,7 +772,7 @@ int handleClientsWaitingListPush(redisClient *c, robj *key, robj *ele) {
     redisAssert(ln != NULL);
     receiver = ln->value;
 
-    addReplySds(receiver,sdsnew("*2\r\n"));
+    addReplyMultiBulkLen(receiver,2);
     addReplyBulk(receiver,key);
     addReplyBulk(receiver,ele);
     unblockClientWaitingData(receiver);
@@ -811,7 +811,7 @@ void blockingPopGenericCommand(redisClient *c, int where) {
                      * "real" command will add the last element (the value)
                      * for us. If this souds like an hack to you it's just
                      * because it is... */
-                    addReplySds(c,sdsnew("*2\r\n"));
+                    addReplyMultiBulkLen(c,2);
                     addReplyBulk(c,argv[1]);
                     popGenericCommand(c,where);
 