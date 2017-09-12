@@ -204,7 +204,7 @@ void selectCommand(redisClient *c) {
     int id = atoi(c->argv[1]->ptr);
 
     if (selectDb(c,id) == REDIS_ERR) {
-        addReplySds(c,sdsnew("-ERR invalid DB index\r\n"));
+        addReplyError(c,"invalid DB index");
     } else {
         addReply(c,shared.ok);
     }
@@ -228,11 +228,9 @@ void keysCommand(redisClient *c) {
     sds pattern = c->argv[1]->ptr;
     int plen = sdslen(pattern), allkeys;
     unsigned long numkeys = 0;
-    robj *lenobj = createObject(REDIS_STRING,NULL);
+    void *replylen = addDeferredMultiBulkLength(c);
 
     di = dictGetIterator(c->db->dict);
-    addReply(c,lenobj);
-    decrRefCount(lenobj);
     allkeys = (pattern[0] == '*' && pattern[1] == '\0');
     while((de = dictNext(di)) != NULL) {
         sds key = dictGetEntryKey(de);
@@ -248,17 +246,15 @@ void keysCommand(redisClient *c) {
         }
     }
     dictReleaseIterator(di);
-    lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",numkeys);
+    setDeferredMultiBulkLength(c,replylen,numkeys);
 }
 
 void dbsizeCommand(redisClient *c) {
-    addReplySds(c,
-        sdscatprintf(sdsempty(),":%lu\r\n",dictSize(c->db->dict)));
+    addReplyLongLong(c,dictSize(c->db->dict));
 }
 
 void lastsaveCommand(redisClient *c) {
-    addReplySds(c,
-        sdscatprintf(sdsempty(),":%lu\r\n",server.lastsave));
+    addReplyLongLong(c,server.lastsave);
 }
 
 void typeCommand(redisClient *c) {
@@ -267,24 +263,23 @@ void typeCommand(redisClient *c) {
 
     o = lookupKeyRead(c->db,c->argv[1]);
     if (o == NULL) {
-        type = "+none";
+        type = "none";
     } else {
         switch(o->type) {
-        case REDIS_STRING: type = "+string"; break;
-        case REDIS_LIST: type = "+list"; break;
-        case REDIS_SET: type = "+set"; break;
-        case REDIS_ZSET: type = "+zset"; break;
-        case REDIS_HASH: type = "+hash"; break;
-        default: type = "+unknown"; break;
+        case REDIS_STRING: type = "string"; break;
+        case REDIS_LIST: type = "list"; break;
+        case REDIS_SET: type = "set"; break;
+        case REDIS_ZSET: type = "zset"; break;
+        case REDIS_HASH: type = "hash"; break;
+        default: type = "unknown"; break;
         }
     }
-    addReplySds(c,sdsnew(type));
-    addReply(c,shared.crlf);
+    addReplyStatus(c,type);
 }
 
 void saveCommand(redisClient *c) {
     if (server.bgsavechildpid != -1) {
-        addReplySds(c,sdsnew("-ERR background save in progress\r\n"));
+        addReplyError(c,"Background save already in progress");
         return;
     }
     if (rdbSave(server.dbfilename) == REDIS_OK) {
@@ -296,12 +291,11 @@ void saveCommand(redisClient *c) {
 
 void bgsaveCommand(redisClient *c) {
     if (server.bgsavechildpid != -1) {
-        addReplySds(c,sdsnew("-ERR background save already in progress\r\n"));
+        addReplyError(c,"Background save already in progress");
         return;
     }
     if (rdbSaveBackground(server.dbfilename) == REDIS_OK) {
-        char *status = "+Background saving started\r\n";
-        addReplySds(c,sdsnew(status));
+        addReplyStatus(c,"Background saving started");
     } else {
         addReply(c,shared.err);
     }
@@ -310,7 +304,7 @@ void bgsaveCommand(redisClient *c) {
 void shutdownCommand(redisClient *c) {
     if (prepareForShutdown() == REDIS_OK)
         exit(0);
-    addReplySds(c, sdsnew("-ERR Errors trying to SHUTDOWN. Check logs.\r\n"));
+    addReplyError(c,"Errors trying to SHUTDOWN. Check logs.");
 }
 
 void renameGenericCommand(redisClient *c, int nx) {