@@ -585,6 +585,10 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
      */
     updateLRUClock();
 
+    /* Record the max memory used since the server was started. */
+    if (zmalloc_used_memory() > server.stat_peak_memory)
+        server.stat_peak_memory = zmalloc_used_memory();
+
     /* We received a SIGTERM, shutting down here in a safe way, as it is
      * not ok doing so inside the signal handler. */
     if (server.shutdown_asap) {
@@ -957,6 +961,7 @@ void initServer() {
     server.stat_starttime = time(NULL);
     server.stat_keyspace_misses = 0;
     server.stat_keyspace_hits = 0;
+    server.stat_peak_memory = 0;
     server.unixtime = time(NULL);
     aeCreateTimeEvent(server.el, 1, serverCron, NULL, NULL);
     if (server.ipfd > 0 && aeCreateFileEvent(server.el,server.ipfd,AE_READABLE,
@@ -1240,7 +1245,6 @@ sds genRedisInfoString(char *section) {
     sds info = sdsempty();
     time_t uptime = time(NULL)-server.stat_starttime;
     int j, numcommands;
-    char hmem[64];
     struct rusage self_ru, c_ru;
     unsigned long lol, bib;
     int allsections = 0, defsections = 0;
@@ -1254,7 +1258,6 @@ sds genRedisInfoString(char *section) {
     getrusage(RUSAGE_SELF, &self_ru);
     getrusage(RUSAGE_CHILDREN, &c_ru);
     getClientsMaxBuffers(&lol,&bib);
-    bytesToHuman(hmem,zmalloc_used_memory());
 
     /* Server */
     if (allsections || defsections || !strcasecmp(section,"server")) {
@@ -1299,18 +1302,29 @@ sds genRedisInfoString(char *section) {
 
     /* Memory */
     if (allsections || defsections || !strcasecmp(section,"memory")) {
+        char hmem[64];
+        char peak_hmem[64];
+
+        bytesToHuman(hmem,zmalloc_used_memory());
+        bytesToHuman(peak_hmem,server.stat_peak_memory);
         if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info,
             "# Memory\r\n"
             "used_memory:%zu\r\n"
             "used_memory_human:%s\r\n"
             "used_memory_rss:%zu\r\n"
+            "used_memory_peak:%zu\r\n"
+            "used_memory_peak_human:%s\r\n"
             "mem_fragmentation_ratio:%.2f\r\n"
+            "peak_mem_fragmentation_ratio:%.2f\r\n"
             "use_tcmalloc:%d\r\n",
             zmalloc_used_memory(),
             hmem,
             zmalloc_get_rss(),
+            server.stat_peak_memory,
+            peak_hmem,
             zmalloc_get_fragmentation_ratio(),
+            (float)zmalloc_get_rss()/server.stat_peak_memory,
     #ifdef USE_TCMALLOC
             1
     #else