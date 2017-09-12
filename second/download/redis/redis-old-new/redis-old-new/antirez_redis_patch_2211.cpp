@@ -336,7 +336,6 @@ struct redisServer {
     int cronloops;              /* number of times the cron function run */
     list *objfreelist;          /* A list of freed objects to avoid malloc() */
     time_t lastsave;            /* Unix time of last save succeeede */
-    size_t usedmemory;             /* Used memory in megabytes */
     /* Fields used only for stats */
     time_t stat_starttime;         /* server start time */
     long long stat_numcommands;    /* number of processed commands */
@@ -1165,9 +1164,6 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
      * To access a global var is faster than calling time(NULL) */
     server.unixtime = time(NULL);
 
-    /* Update the global state with the amount of used memory */
-    server.usedmemory = zmalloc_used_memory();
-
     /* Show some info about non-empty databases */
     for (j = 0; j < server.dbnum; j++) {
         long long size, used, vkeys;
@@ -1194,7 +1190,7 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
         redisLog(REDIS_VERBOSE,"%d clients connected (%d slaves), %zu bytes in use, %d shared objects",
             listLength(server.clients)-listLength(server.slaves),
             listLength(server.slaves),
-            server.usedmemory,
+            zmalloc_used_memory(),
             dictSize(server.sharingpool));
     }
 
@@ -1437,7 +1433,6 @@ static void initServer() {
     server.bgrewritebuf = sdsempty();
     server.lastsave = time(NULL);
     server.dirty = 0;
-    server.usedmemory = 0;
     server.stat_numcommands = 0;
     server.stat_numconnections = 0;
     server.stat_starttime = time(NULL);
@@ -5581,7 +5576,7 @@ static void bytesToHuman(char *s, unsigned long long n) {
         sprintf(s,"%.2fM",d);
     } else if (n < (1024LL*1024*1024*1024)) {
         d = (double)n/(1024LL*1024*1024);
-        sprintf(s,"%.2fM",d);
+        sprintf(s,"%.2fG",d);
     }
 }
 
@@ -5594,7 +5589,7 @@ static sds genRedisInfoString(void) {
     int j;
     char hmem[64];
   
-    bytesToHuman(hmem,server.usedmemory);
+    bytesToHuman(hmem,zmalloc_used_memory());
     info = sdscatprintf(sdsempty(),
         "redis_version:%s\r\n"
         "arch_bits:%s\r\n"
@@ -5624,7 +5619,7 @@ static sds genRedisInfoString(void) {
         listLength(server.clients)-listLength(server.slaves),
         listLength(server.slaves),
         server.blockedclients,
-        server.usedmemory,
+        zmalloc_used_memory(),
         hmem,
         server.dirty,
         server.bgsavechildpid != -1,
@@ -7396,6 +7391,9 @@ static int vmSwapOneObject(int usethreads) {
 
     for (j = 0; j < server.dbnum; j++) {
         redisDb *db = server.db+j;
+        /* Why maxtries is set to 100?
+         * Because this way (usually) we'll find 1 object even if just 1% - 2%
+         * are swappable objects */
         int maxtries = 100;
 
         if (dictSize(db->dict) == 0) continue;