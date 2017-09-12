@@ -545,7 +545,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
         redisLog(REDIS_VERBOSE,"%d clients connected (%d slaves), %zu bytes in use",
             listLength(server.clients)-listLength(server.slaves),
             listLength(server.slaves),
-            zmalloc_used_memory());
+            redisEstimateRSS());
     }
 
     /* Close connections of timedout clients */
@@ -590,17 +590,15 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
     /* Swap a few keys on disk if we are over the memory limit and VM
      * is enbled. Try to free objects from the free list first. */
     if (vmCanSwapOut()) {
-        while (server.vm_enabled && zmalloc_used_memory() >
-                server.vm_max_memory)
-        {
+        while (server.vm_enabled && redisEstimateRSS() > server.vm_max_memory) {
             int retval;
 
             if (tryFreeOneObjectFromFreelist() == REDIS_OK) continue;
             retval = (server.vm_max_threads == 0) ?
                         vmSwapOneObjectBlocking() :
                         vmSwapOneObjectThreaded();
             if (retval == REDIS_ERR && !(loops % 300) &&
-                zmalloc_used_memory() >
+                redisEstimateRSS() >
                 (server.vm_max_memory+server.vm_max_memory/10))
             {
                 redisLog(REDIS_WARNING,"WARNING: vm-max-memory limit exceeded by more than 10%% but unable to swap more objects out!");
@@ -940,7 +938,7 @@ int processCommand(redisClient *c) {
      * is returning an error. */
     if (server.maxmemory) freeMemoryIfNeeded();
     if (server.maxmemory && (cmd->flags & REDIS_CMD_DENYOOM) &&
-        zmalloc_used_memory() > server.maxmemory)
+        redisEstimateRSS() > server.maxmemory)
     {
         addReplyError(c,"command not allowed when used memory > 'maxmemory'");
         return REDIS_OK;
@@ -1059,7 +1057,7 @@ sds genRedisInfoString(void) {
     getrusage(RUSAGE_SELF, &self_ru);
     getrusage(RUSAGE_CHILDREN, &c_ru);
 
-    bytesToHuman(hmem,zmalloc_used_memory());
+    bytesToHuman(hmem,redisEstimateRSS());
     info = sdscatprintf(sdsempty(),
         "redis_version:%s\r\n"
         "redis_git_sha1:%s\r\n"
@@ -1079,8 +1077,8 @@ sds genRedisInfoString(void) {
         "blocked_clients:%d\r\n"
         "used_memory:%zu\r\n"
         "used_memory_human:%s\r\n"
-        "used_memory_rss:%zu\r\n"
-        "used_memory_estimated_rss:%zu\r\n"
+        "used_memory_zmalloc:%zu\r\n"
+        "used_memory_raw_rss:%zu\r\n"
         "mem_fragmentation_ratio:%.2f\r\n"
         "use_tcmalloc:%d\r\n"
         "changes_since_last_save:%lld\r\n"
@@ -1114,10 +1112,10 @@ sds genRedisInfoString(void) {
         listLength(server.clients)-listLength(server.slaves),
         listLength(server.slaves),
         server.blpop_blocked_clients,
-        zmalloc_used_memory(),
+        redisEstimateRSS(),
         hmem,
+        zmalloc_used_memory(),
         zmalloc_get_rss(),
-        redisEstimateRSS(),
         zmalloc_get_fragmentation_ratio(),
 #ifdef USE_TCMALLOC
         1,
@@ -1285,7 +1283,7 @@ size_t redisEstimateRSS(void) {
 void freeMemoryIfNeeded(void) {
     /* Remove keys accordingly to the active policy as long as we are
      * over the memory limit. */
-    while (server.maxmemory && zmalloc_used_memory() > server.maxmemory) {
+    while (server.maxmemory && redisEstimateRSS() > server.maxmemory) {
         int j, k, freed = 0;
 
         /* Basic strategy -- remove objects from the free list. */