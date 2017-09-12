@@ -223,11 +223,9 @@ void keysCommand(redisClient *c) {
     sds pattern = c->argv[1]->ptr;
     int plen = sdslen(pattern);
     unsigned long numkeys = 0;
-    robj *lenobj = createObject(REDIS_STRING,NULL);
+    void *replylen = addDeferredMultiBulkLength(c);
 
     di = dictGetIterator(c->db->dict);
-    addReply(c,lenobj);
-    decrRefCount(lenobj);
     while((de = dictNext(di)) != NULL) {
         sds key = dictGetEntryKey(de);
         robj *keyobj;
@@ -243,7 +241,7 @@ void keysCommand(redisClient *c) {
         }
     }
     dictReleaseIterator(di);
-    lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",numkeys);
+    setDeferredMultiBulkLength(c,replylen,numkeys);
 }
 
 void dbsizeCommand(redisClient *c) {