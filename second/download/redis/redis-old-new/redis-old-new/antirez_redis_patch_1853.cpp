@@ -152,6 +152,10 @@ void loadServerConfig(char *filename) {
             server.replstate = REDIS_REPL_CONNECT;
         } else if (!strcasecmp(argv[0],"masterauth") && argc == 2) {
         	server.masterauth = zstrdup(argv[1]);
+        } else if (!strcasecmp(argv[0],"slave-serve-stale-data") && argc == 2) {
+            if ((server.repl_serve_stale_data = yesnotoi(argv[1])) == -1) {
+                err = "argument must be 'yes' or 'no'"; goto loaderr;
+            }
         } else if (!strcasecmp(argv[0],"glueoutputbuf") && argc == 2) {
             if ((server.glueoutputbuf = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
@@ -379,6 +383,11 @@ void configSetCommand(redisClient *c) {
             appendServerSaveParams(seconds, changes);
         }
         sdsfreesplitres(v,vlen);
+    } else if (!strcasecmp(c->argv[2]->ptr,"slave-serve-stale-data")) {
+        int yn = yesnotoi(o->ptr);
+
+        if (yn == -1) goto badfmt;
+        server.repl_serve_stale_data = yn;
     } else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);
@@ -488,6 +497,11 @@ void configGetCommand(redisClient *c) {
         sdsfree(buf);
         matches++;
     }
+    if (stringmatch(pattern,"slave-serve-stale-data",0)) {
+        addReplyBulkCString(c,"slave-serve-stale-data");
+        addReplyBulkCString(c,server.repl_serve_stale_data ? "yes" : "no");
+        matches++;
+    }
     setDeferredMultiBulkLength(c,replylen,matches*2);
 }
 