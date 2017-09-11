@@ -1187,7 +1187,7 @@ void initServerConfig() {
     server.repl_ping_slave_period = REDIS_REPL_PING_SLAVE_PERIOD;
     server.repl_timeout = REDIS_REPL_TIMEOUT;
     server.cluster_enabled = 0;
-    server.cluster.configfile = zstrdup("nodes.conf");
+    server.cluster_configfile = zstrdup("nodes.conf");
     server.lua_caller = NULL;
     server.lua_time_limit = REDIS_LUA_TIME_LIMIT;
     server.lua_client = NULL;
@@ -1661,7 +1661,7 @@ int processCommand(redisClient *c) {
                 !(c->cmd->getkeys_proc == NULL && c->cmd->firstkey == 0)) {
         int hashslot;
 
-        if (server.cluster.state != REDIS_CLUSTER_OK) {
+        if (server.cluster->state != REDIS_CLUSTER_OK) {
             addReplyError(c,"The cluster is down. Check with CLUSTER INFO for more information");
             return REDIS_OK;
         } else {
@@ -1670,7 +1670,7 @@ int processCommand(redisClient *c) {
             if (n == NULL) {
                 addReplyError(c,"Multi keys request invalid in cluster");
                 return REDIS_OK;
-            } else if (n != server.cluster.myself) {
+            } else if (n != server.cluster->myself) {
                 addReplySds(c,sdscatprintf(sdsempty(),
                     "-%s %d %s:%d\r\n", ask ? "ASK" : "MOVED",
                     hashslot,n->ip,n->port));