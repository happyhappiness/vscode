@@ -298,6 +298,12 @@ void loadServerConfig(char *filename) {
             server.cluster.configfile = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"lua-time-limit") && argc == 2) {
             server.lua_time_limit = strtoll(argv[1],NULL,10);
+        } else if (!strcasecmp(argv[0],"slowlog-log-slower-than") &&
+                   argc == 2)
+        {
+            server.slowlog_log_slower_than = strtoll(argv[1],NULL,10);
+        } else if (!strcasecmp(argv[0],"slowlog-max-len") && argc == 2) {
+            server.slowlog_max_len = strtoll(argv[1],NULL,10);
         } else {
             err = "Bad directive or wrong number of arguments"; goto loaderr;
         }
@@ -471,6 +477,12 @@ void configSetCommand(redisClient *c) {
     } else if (!strcasecmp(c->argv[2]->ptr,"lua-time-limit")) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
         server.lua_time_limit = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"slowlog-log-slower-than")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR) goto badfmt;
+        server.slowlog_log_slower_than = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"slowlog-max-len")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
+        server.slowlog_max_len = (unsigned)ll;
     } else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);
@@ -645,6 +657,14 @@ void configGetCommand(redisClient *c) {
     if (stringmatch(pattern,"lua-time-limit",0)) {
         addReplyBulkCString(c,"lua-time-limit");
         addReplyBulkLongLong(c,server.lua_time_limit);
+    if (stringmatch(pattern,"slowlog-log-slower-than",0)) {
+        addReplyBulkCString(c,"slowlog-log-slower-than");
+        addReplyBulkLongLong(c,server.slowlog_log_slower_than);
+        matches++;
+    }
+    if (stringmatch(pattern,"slowlog-max-len",0)) {
+        addReplyBulkCString(c,"slowlog-max-len");
+        addReplyBulkLongLong(c,server.slowlog_max_len);
         matches++;
     }
     setDeferredMultiBulkLength(c,replylen,matches*2);