@@ -270,8 +270,8 @@ void configSetCommand(redisClient *c) {
                 stopAppendOnly();
             } else {
                 if (startAppendOnly() == REDIS_ERR) {
-                    addReplySds(c,sdscatprintf(sdsempty(),
-                        "-ERR Unable to turn on AOF. Check server logs.\r\n"));
+                    addReplyError(c,
+                        "Unable to turn on AOF. Check server logs.");
                     decrRefCount(o);
                     return;
                 }
@@ -312,9 +312,8 @@ void configSetCommand(redisClient *c) {
         }
         sdsfreesplitres(v,vlen);
     } else {
-        addReplySds(c,sdscatprintf(sdsempty(),
-            "-ERR not supported CONFIG parameter %s\r\n",
-            (char*)c->argv[2]->ptr));
+        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
+            (char*)c->argv[2]->ptr);
         decrRefCount(o);
         return;
     }
@@ -323,22 +322,18 @@ void configSetCommand(redisClient *c) {
     return;
 
 badfmt: /* Bad format errors */
-    addReplySds(c,sdscatprintf(sdsempty(),
-        "-ERR invalid argument '%s' for CONFIG SET '%s'\r\n",
+    addReplyErrorFormat(c,"Invalid argument '%s' for CONFIG SET '%s'",
             (char*)o->ptr,
-            (char*)c->argv[2]->ptr));
+            (char*)c->argv[2]->ptr);
     decrRefCount(o);
 }
 
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
@@ -410,7 +405,7 @@ void configGetCommand(redisClient *c) {
         matches++;
     }
     decrRefCount(o);
-    lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",matches*2);
+    setDeferredMultiBulkLength(c,replylen,matches*2);
 }
 
 void configCommand(redisClient *c) {
@@ -428,13 +423,12 @@ void configCommand(redisClient *c) {
         server.stat_starttime = time(NULL);
         addReply(c,shared.ok);
     } else {
-        addReplySds(c,sdscatprintf(sdsempty(),
-            "-ERR CONFIG subcommand must be one of GET, SET, RESETSTAT\r\n"));
+        addReplyError(c,
+            "CONFIG subcommand must be one of GET, SET, RESETSTAT");
     }
     return;
 
 badarity:
-    addReplySds(c,sdscatprintf(sdsempty(),
-        "-ERR Wrong number of arguments for CONFIG %s\r\n",
-        (char*) c->argv[1]->ptr));
+    addReplyErrorFormat(c,"Wrong number of arguments for CONFIG %s",
+        (char*) c->argv[1]->ptr);
 }