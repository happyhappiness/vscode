@@ -423,6 +423,11 @@ void configSetCommand(redisClient *c) {
 
         if (yn == -1) goto badfmt;
         server.repl_serve_stale_data = yn;
+    } else if (!strcasecmp(c->argv[2]->ptr,"dir")) {
+        if (chdir((char*)o->ptr) == -1) {
+            addReplyErrorFormat(c,"Changing directory: %s", strerror(errno));
+            return;
+        }
     } else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);
@@ -445,6 +450,15 @@ void configGetCommand(redisClient *c) {
     int matches = 0;
     redisAssert(o->encoding == REDIS_ENCODING_RAW);
 
+    if (stringmatch(pattern,"dir",0)) {
+        char buf[1024];
+
+        buf[0] = '\0';
+        getcwd(buf,sizeof(buf));
+        addReplyBulkCString(c,"dir");
+        addReplyBulkCString(c,buf);
+        matches++;
+    }
     if (stringmatch(pattern,"dbfilename",0)) {
         addReplyBulkCString(c,"dbfilename");
         addReplyBulkCString(c,server.dbfilename);