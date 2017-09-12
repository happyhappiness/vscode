@@ -332,13 +332,10 @@ void configSetCommand(redisClient *c) {
 
 void configGetCommand(redisClient *c) {
     robj *o = getDecodedObject(c->argv[2]);
-    robj *lenobj = createObject(REDIS_STRING,NULL);
+    void *replylen = addDeferredMultiBulkLength(c);
     char *pattern = o->ptr;
     int matches = 0;
 
-    addReply(c,lenobj);
-    decrRefCount(lenobj);
-
     if (stringmatch(pattern,"dbfilename",0)) {
         addReplyBulkCString(c,"dbfilename");
         addReplyBulkCString(c,server.dbfilename);
@@ -410,7 +407,7 @@ void configGetCommand(redisClient *c) {
         matches++;
     }
     decrRefCount(o);
-    lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",matches*2);
+    setDeferredMultiBulkLength(c,replylen,matches*2);
 }
 
 void configCommand(redisClient *c) {