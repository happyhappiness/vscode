@@ -350,17 +350,15 @@ void hlenCommand(redisClient *c) {
 }
 
 void genericHgetallCommand(redisClient *c, int flags) {
-    robj *o, *lenobj, *obj;
+    robj *o, *obj;
     unsigned long count = 0;
     hashTypeIterator *hi;
+    void *replylen = NULL;
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk)) == NULL
         || checkType(c,o,REDIS_HASH)) return;
 
-    lenobj = createObject(REDIS_STRING,NULL);
-    addReply(c,lenobj);
-    decrRefCount(lenobj);
-
+    replylen = addDeferredMultiBulkLength(c);
     hi = hashTypeInitIterator(o);
     while (hashTypeNext(hi) != REDIS_ERR) {
         if (flags & REDIS_HASH_KEY) {
@@ -377,8 +375,7 @@ void genericHgetallCommand(redisClient *c, int flags) {
         }
     }
     hashTypeReleaseIterator(hi);
-
-    lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",count);
+    setDeferredMultiBulkLength(c,replylen,count);
 }
 
 void hkeysCommand(redisClient *c) {