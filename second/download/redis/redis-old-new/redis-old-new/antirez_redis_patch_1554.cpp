@@ -28,6 +28,7 @@
  */
 
 #include "redis.h"
+#include "slowlog.h"
 
 #ifdef HAVE_BACKTRACE
 #include <execinfo.h>
@@ -194,7 +195,8 @@ struct redisCommand redisCommandTable[] = {
     {"object",objectCommand,-2,0,NULL,0,0,0,0,0},
     {"client",clientCommand,-2,0,NULL,0,0,0,0,0},
     {"eval",evalCommand,-3,REDIS_CMD_DENYOOM,zunionInterGetKeys,0,0,0,0,0},
-    {"evalsha",evalShaCommand,-3,REDIS_CMD_DENYOOM,zunionInterGetKeys,0,0,0,0,0}
+    {"evalsha",evalShaCommand,-3,REDIS_CMD_DENYOOM,zunionInterGetKeys,0,0,0,0,0},
+    {"slowlog",slowlogCommand,-2,0,NULL,0,0,0,0,0}
 };
 
 /*============================ Utility functions ============================ */
@@ -871,6 +873,10 @@ void initServerConfig() {
     populateCommandTable();
     server.delCommand = lookupCommandByCString("del");
     server.multiCommand = lookupCommandByCString("multi");
+    
+    /* Slow log */
+    server.slowlog_log_slower_than = REDIS_SLOWLOG_LOG_SLOWER_THAN;
+    server.slowlog_max_len = REDIS_SLOWLOG_MAX_LEN;
 }
 
 void initServer() {
@@ -958,6 +964,7 @@ void initServer() {
 
     if (server.cluster_enabled) clusterInit();
     scriptingInit();
+    slowlogInit();
     srand(time(NULL)^getpid());
 }
 
@@ -1004,18 +1011,20 @@ struct redisCommand *lookupCommandByCString(char *s) {
 }
 
 /* Call() is the core of Redis execution of a command */
-void call(redisClient *c, struct redisCommand *cmd) {
-    long long dirty, start = ustime();
+void call(redisClient *c) {
+    long long dirty, start = ustime(), duration;
 
     dirty = server.dirty;
-    cmd->proc(c);
+    c->cmd->proc(c);
     dirty = server.dirty-dirty;
-    cmd->microseconds += ustime()-start;
-    cmd->calls++;
+    duration = ustime()-start;
+    c->cmd->microseconds += duration;
+    slowlogPushEntryIfNeeded(c->argv,c->argc,duration);
+    c->cmd->calls++;
 
     if (server.appendonly && dirty)
-        feedAppendOnlyFile(cmd,c->db->id,c->argv,c->argc);
-    if ((dirty || cmd->flags & REDIS_CMD_FORCE_REPLICATION) &&
+        feedAppendOnlyFile(c->cmd,c->db->id,c->argv,c->argc);
+    if ((dirty || c->cmd->flags & REDIS_CMD_FORCE_REPLICATION) &&
         listLength(server.slaves))
         replicationFeedSlaves(server.slaves,c->db->id,c->argv,c->argc);
     if (listLength(server.monitors))
@@ -1032,8 +1041,6 @@ void call(redisClient *c, struct redisCommand *cmd) {
  * and other operations can be performed by the caller. Otherwise
  * if 0 is returned the client was destroied (i.e. after QUIT). */
 int processCommand(redisClient *c) {
-    struct redisCommand *cmd;
-
     /* The QUIT command is handled separately. Normal command procs will
      * go through checking for replication and QUIT will cause trouble
      * when FORCE_REPLICATION is enabled and would be implemented in
@@ -1045,36 +1052,37 @@ int processCommand(redisClient *c) {
     }
 
     /* Now lookup the command and check ASAP about trivial error conditions
-     * such wrong arity, bad command name and so forth. */
-    cmd = lookupCommand(c->argv[0]->ptr);
-    if (!cmd) {
+     * such as wrong arity, bad command name and so forth. */
+    c->cmd = lookupCommand(c->argv[0]->ptr);
+    if (!c->cmd) {
         addReplyErrorFormat(c,"unknown command '%s'",
             (char*)c->argv[0]->ptr);
         return REDIS_OK;
-    } else if ((cmd->arity > 0 && cmd->arity != c->argc) ||
-               (c->argc < -cmd->arity)) {
+    } else if ((c->cmd->arity > 0 && c->cmd->arity != c->argc) ||
+               (c->argc < -c->cmd->arity)) {
         addReplyErrorFormat(c,"wrong number of arguments for '%s' command",
-            cmd->name);
+            c->cmd->name);
         return REDIS_OK;
     }
 
     /* Check if the user is authenticated */
-    if (server.requirepass && !c->authenticated && cmd->proc != authCommand) {
+    if (server.requirepass && !c->authenticated && c->cmd->proc != authCommand)
+    {
         addReplyError(c,"operation not permitted");
         return REDIS_OK;
     }
 
     /* If cluster is enabled, redirect here */
     if (server.cluster_enabled &&
-                !(cmd->getkeys_proc == NULL && cmd->firstkey == 0)) {
+                !(c->cmd->getkeys_proc == NULL && c->cmd->firstkey == 0)) {
         int hashslot;
 
         if (server.cluster.state != REDIS_CLUSTER_OK) {
             addReplyError(c,"The cluster is down. Check with CLUSTER INFO for more information");
             return REDIS_OK;
         } else {
             int ask;
-            clusterNode *n = getNodeByQuery(c,cmd,c->argv,c->argc,&hashslot,&ask);
+            clusterNode *n = getNodeByQuery(c,c->cmd,c->argv,c->argc,&hashslot,&ask);
             if (n == NULL) {
                 addReplyError(c,"Multi keys request invalid in cluster");
                 return REDIS_OK;
@@ -1093,7 +1101,7 @@ int processCommand(redisClient *c) {
      * keys in the dataset). If there are not the only thing we can do
      * is returning an error. */
     if (server.maxmemory) freeMemoryIfNeeded();
-    if (server.maxmemory && (cmd->flags & REDIS_CMD_DENYOOM) &&
+    if (server.maxmemory && (c->cmd->flags & REDIS_CMD_DENYOOM) &&
         zmalloc_used_memory() > server.maxmemory)
     {
         addReplyError(c,"command not allowed when used memory > 'maxmemory'");
@@ -1103,8 +1111,10 @@ int processCommand(redisClient *c) {
     /* Only allow SUBSCRIBE and UNSUBSCRIBE in the context of Pub/Sub */
     if ((dictSize(c->pubsub_channels) > 0 || listLength(c->pubsub_patterns) > 0)
         &&
-        cmd->proc != subscribeCommand && cmd->proc != unsubscribeCommand &&
-        cmd->proc != psubscribeCommand && cmd->proc != punsubscribeCommand) {
+        c->cmd->proc != subscribeCommand &&
+        c->cmd->proc != unsubscribeCommand &&
+        c->cmd->proc != psubscribeCommand &&
+        c->cmd->proc != punsubscribeCommand) {
         addReplyError(c,"only (P)SUBSCRIBE / (P)UNSUBSCRIBE / QUIT allowed in this context");
         return REDIS_OK;
     }
@@ -1113,28 +1123,28 @@ int processCommand(redisClient *c) {
      * we are a slave with a broken link with master. */
     if (server.masterhost && server.replstate != REDIS_REPL_CONNECTED &&
         server.repl_serve_stale_data == 0 &&
-        cmd->proc != infoCommand && cmd->proc != slaveofCommand)
+        c->cmd->proc != infoCommand && c->cmd->proc != slaveofCommand)
     {
         addReplyError(c,
             "link with MASTER is down and slave-serve-stale-data is set to no");
         return REDIS_OK;
     }
 
     /* Loading DB? Return an error if the command is not INFO */
-    if (server.loading && cmd->proc != infoCommand) {
+    if (server.loading && c->cmd->proc != infoCommand) {
         addReply(c, shared.loadingerr);
         return REDIS_OK;
     }
 
     /* Exec the command */
     if (c->flags & REDIS_MULTI &&
-        cmd->proc != execCommand && cmd->proc != discardCommand &&
-        cmd->proc != multiCommand && cmd->proc != watchCommand)
+        c->cmd->proc != execCommand && c->cmd->proc != discardCommand &&
+        c->cmd->proc != multiCommand && c->cmd->proc != watchCommand)
     {
-        queueMultiCommand(c,cmd);
+        queueMultiCommand(c);
         addReply(c,shared.queued);
     } else {
-        call(c,cmd);
+        call(c);
     }
     return REDIS_OK;
 }
@@ -1305,22 +1315,6 @@ sds genRedisInfoString(char *section) {
             );
     }
 
-    /* Allocation statistics */
-    if (allsections || !strcasecmp(section,"allocstats")) {
-        if (sections++) info = sdscat(info,"\r\n");
-        info = sdscat(info, "# Allocstats\r\nallocation_stats:");
-        for (j = 0; j <= ZMALLOC_MAX_ALLOC_STAT; j++) {
-            size_t count = zmalloc_allocations_for_size(j);
-            if (count) {
-                if (info[sdslen(info)-1] != ':') info = sdscatlen(info,",",1);
-                info = sdscatprintf(info,"%s%d=%zu",
-                    (j == ZMALLOC_MAX_ALLOC_STAT) ? ">=" : "",
-                    j,count);
-            }
-        }
-        info = sdscat(info,"\r\n");
-    }
-
     /* Persistence */
     if (allsections || defsections || !strcasecmp(section,"persistence")) {
         if (sections++) info = sdscat(info,"\r\n");
@@ -1456,8 +1450,8 @@ sds genRedisInfoString(char *section) {
         "# CPU\r\n"
         "used_cpu_sys:%.2f\r\n"
         "used_cpu_user:%.2f\r\n"
-        "used_cpu_sys_childrens:%.2f\r\n"
-        "used_cpu_user_childrens:%.2f\r\n",
+        "used_cpu_sys_children:%.2f\r\n"
+        "used_cpu_user_children:%.2f\r\n",
         (float)self_ru.ru_utime.tv_sec+(float)self_ru.ru_utime.tv_usec/1000000,
         (float)self_ru.ru_stime.tv_sec+(float)self_ru.ru_stime.tv_usec/1000000,
         (float)c_ru.ru_utime.tv_sec+(float)c_ru.ru_utime.tv_usec/1000000,