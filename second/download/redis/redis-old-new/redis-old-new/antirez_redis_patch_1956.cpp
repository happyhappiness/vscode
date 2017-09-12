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
@@ -323,10 +322,9 @@ void configSetCommand(redisClient *c) {
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
 
@@ -425,13 +423,12 @@ void configCommand(redisClient *c) {
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