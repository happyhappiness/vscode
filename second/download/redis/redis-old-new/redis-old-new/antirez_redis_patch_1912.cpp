@@ -249,7 +249,7 @@ void hmsetCommand(redisClient *c) {
     robj *o;
 
     if ((c->argc % 2) == 1) {
-        addReplySds(c,sdsnew("-ERR wrong number of arguments for HMSET\r\n"));
+        addReplyError(c,"wrong number of arguments for HMSET");
         return;
     }
 
@@ -315,7 +315,7 @@ void hmgetCommand(redisClient *c) {
     /* Note the check for o != NULL happens inside the loop. This is
      * done because objects that cannot be found are considered to be
      * an empty hash. The reply should then be a series of NULLs. */
-    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->argc-2));
+    addReplyMultiBulkLen(c,c->argc-2);
     for (i = 2; i < c->argc; i++) {
         if (o != NULL && (value = hashTypeGet(o,c->argv[i])) != NULL) {
             addReplyBulk(c,value);
@@ -346,21 +346,19 @@ void hlenCommand(redisClient *c) {
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,o,REDIS_HASH)) return;
 
-    addReplyUlong(c,hashTypeLength(o));
+    addReplyLongLong(c,hashTypeLength(o));
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