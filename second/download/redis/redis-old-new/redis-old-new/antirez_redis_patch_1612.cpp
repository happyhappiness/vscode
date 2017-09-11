@@ -296,6 +296,8 @@ void loadServerConfig(char *filename) {
         } else if (!strcasecmp(argv[0],"cluster-config-file") && argc == 2) {
             zfree(server.cluster.configfile);
             server.cluster.configfile = zstrdup(argv[1]);
+        } else if (!strcasecmp(argv[0],"lua-time-limit") && argc == 2) {
+            server.lua_time_limit = strtoll(argv[1],NULL,10);
         } else {
             err = "Bad directive or wrong number of arguments"; goto loaderr;
         }
@@ -460,6 +462,9 @@ void configSetCommand(redisClient *c) {
     } else if (!strcasecmp(c->argv[2]->ptr,"zset-max-ziplist-value")) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
         server.zset_max_ziplist_value = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"lua-time-limit")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
+        server.lua_time_limit = ll;
     } else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);
@@ -621,6 +626,11 @@ void configGetCommand(redisClient *c) {
         addReplyBulkLongLong(c,server.zset_max_ziplist_value);
         matches++;
     }
+    if (stringmatch(pattern,"lua-time-limit",0)) {
+        addReplyBulkCString(c,"lua-time-limit");
+        addReplyBulkLongLong(c,server.lua_time_limit);
+        matches++;
+    }
     setDeferredMultiBulkLength(c,replylen,matches*2);
 }
 