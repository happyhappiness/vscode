@@ -32,6 +32,7 @@
 #include "slowlog.h"
 #include "bio.h"
 #include "latency.h"
+#include "atomicvar.h"
 
 #include <time.h>
 #include <signal.h>
@@ -68,7 +69,8 @@ double R_Zero, R_PosInf, R_NegInf, R_Nan;
 /*================================= Globals ================================= */
 
 /* Global vars */
-struct redisServer server; /* server global state */
+struct redisServer server; /* Server global state */
+volatile unsigned long lru_clock; /* Server global current LRU time. */
 
 /* Our command table.
  *
@@ -976,7 +978,8 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
      *
      * Note that you can change the resolution altering the
      * LRU_CLOCK_RESOLUTION define. */
-    server.lruclock = getLRUClock();
+    unsigned long lruclock = getLRUClock();
+    atomicSet(server.lruclock,lruclock);
 
     /* Record the max memory used since the server was started. */
     if (zmalloc_used_memory() > server.stat_peak_memory)
@@ -1420,14 +1423,16 @@ void initServerConfig(void) {
     server.cluster_announce_bus_port = CONFIG_DEFAULT_CLUSTER_ANNOUNCE_BUS_PORT;
     server.migrate_cached_sockets = dictCreate(&migrateCacheDictType,NULL);
     server.next_client_id = 1; /* Client IDs, start from 1 .*/
+    pthread_mutex_init(&server.next_client_id_mutex,NULL);
     server.loading_process_events_interval_bytes = (1024*1024*2);
     server.lazyfree_lazy_eviction = CONFIG_DEFAULT_LAZYFREE_LAZY_EVICTION;
     server.lazyfree_lazy_expire = CONFIG_DEFAULT_LAZYFREE_LAZY_EXPIRE;
     server.lazyfree_lazy_server_del = CONFIG_DEFAULT_LAZYFREE_LAZY_SERVER_DEL;
     server.always_show_logo = CONFIG_DEFAULT_ALWAYS_SHOW_LOGO;
     server.lua_time_limit = LUA_SCRIPT_TIME_LIMIT;
 
-    server.lruclock = getLRUClock();
+    unsigned int lruclock = getLRUClock();
+    atomicSet(server.lruclock,lruclock);
     resetServerSaveParams();
 
     appendServerSaveParams(60*60,1);  /* save after 1 hour and 1 change */
@@ -2809,6 +2814,8 @@ sds genRedisInfoString(char *section) {
             call_uname = 0;
         }
 
+        unsigned int lruclock;
+        atomicGet(server.lruclock,lruclock);
         info = sdscatprintf(info,
             "# Server\r\n"
             "redis_version:%s\r\n"
@@ -2848,7 +2855,7 @@ sds genRedisInfoString(char *section) {
             (intmax_t)uptime,
             (intmax_t)(uptime/(3600*24)),
             server.hz,
-            (unsigned long) server.lruclock,
+            (unsigned long) lruclock,
             server.executable ? server.executable : "",
             server.configfile ? server.configfile : "");
     }