@@ -246,8 +246,11 @@ void loadServerConfig(char *filename) {
  *----------------------------------------------------------------------------*/
 
 void configSetCommand(redisClient *c) {
-    robj *o = getDecodedObject(c->argv[3]);
+    robj *o;
     long long ll;
+    redisAssert(c->argv[2]->encoding == REDIS_ENCODING_RAW);
+    redisAssert(c->argv[3]->encoding == REDIS_ENCODING_RAW);
+    o = c->argv[3];
 
     if (!strcasecmp(c->argv[2]->ptr,"dbfilename")) {
         zfree(server.dbfilename);
@@ -312,7 +315,6 @@ void configSetCommand(redisClient *c) {
                 if (startAppendOnly() == REDIS_ERR) {
                     addReplyError(c,
                         "Unable to turn on AOF. Check server logs.");
-                    decrRefCount(o);
                     return;
                 }
             }
@@ -354,26 +356,24 @@ void configSetCommand(redisClient *c) {
     } else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);
-        decrRefCount(o);
         return;
     }
-    decrRefCount(o);
     addReply(c,shared.ok);
     return;
 
 badfmt: /* Bad format errors */
     addReplyErrorFormat(c,"Invalid argument '%s' for CONFIG SET '%s'",
             (char*)o->ptr,
             (char*)c->argv[2]->ptr);
-    decrRefCount(o);
 }
 
 void configGetCommand(redisClient *c) {
-    robj *o = getDecodedObject(c->argv[2]);
+    robj *o = c->argv[2];
     void *replylen = addDeferredMultiBulkLength(c);
     char *pattern = o->ptr;
     char buf[128];
     int matches = 0;
+    redisAssert(o->encoding == REDIS_ENCODING_RAW);
 
     if (stringmatch(pattern,"dbfilename",0)) {
         addReplyBulkCString(c,"dbfilename");
@@ -462,7 +462,6 @@ void configGetCommand(redisClient *c) {
         sdsfree(buf);
         matches++;
     }
-    decrRefCount(o);
     setDeferredMultiBulkLength(c,replylen,matches*2);
 }
 