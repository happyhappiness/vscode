@@ -612,7 +612,7 @@ void activeExpireCycle(void) {
 }
 
 void updateLRUClock(void) {
-    server.lruclock = (time(NULL)/REDIS_LRU_CLOCK_RESOLUTION) &
+    server.lruclock = (server.unixtime/REDIS_LRU_CLOCK_RESOLUTION) &
                                                 REDIS_LRU_CLOCK_MAX;
 }
 
@@ -821,15 +821,13 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
             updateDictResizePolicy();
         }
     } else {
-         time_t now = time(NULL);
-
         /* If there is not a background saving/rewrite in progress check if
          * we have to save/rewrite now */
          for (j = 0; j < server.saveparamslen; j++) {
             struct saveparam *sp = server.saveparams+j;
 
             if (server.dirty >= sp->changes &&
-                now-server.lastsave > sp->seconds) {
+                server.unixtime-server.lastsave > sp->seconds) {
                 redisLog(REDIS_NOTICE,"%d changes in %d seconds. Saving...",
                     sp->changes, sp->seconds);
                 rdbSaveBackground(server.rdb_filename);
@@ -1683,7 +1681,7 @@ void bytesToHuman(char *s, unsigned long long n) {
  * on memory corruption problems. */
 sds genRedisInfoString(char *section) {
     sds info = sdsempty();
-    time_t uptime = time(NULL)-server.stat_starttime;
+    time_t uptime = server.unixtime-server.stat_starttime;
     int j, numcommands;
     struct rusage self_ru, c_ru;
     unsigned long lol, bib;
@@ -1822,7 +1820,7 @@ sds genRedisInfoString(char *section) {
             perc = ((double)server.loading_loaded_bytes /
                    server.loading_total_bytes) * 100;
 
-            elapsed = time(NULL)-server.loading_start_time;
+            elapsed = server.unixtime-server.loading_start_time;
             if (elapsed == 0) {
                 eta = 1; /* A fake 1 second figure if we don't have
                             enough info */
@@ -1893,7 +1891,7 @@ sds genRedisInfoString(char *section) {
                 (server.repl_state == REDIS_REPL_CONNECTED) ?
                     "up" : "down",
                 server.master ?
-                ((int)(time(NULL)-server.master->lastinteraction)) : -1,
+                ((int)(server.unixtime-server.master->lastinteraction)) : -1,
                 server.repl_state == REDIS_REPL_TRANSFER
             );
 
@@ -1902,14 +1900,14 @@ sds genRedisInfoString(char *section) {
                     "master_sync_left_bytes:%ld\r\n"
                     "master_sync_last_io_seconds_ago:%d\r\n"
                     ,(long)server.repl_transfer_left,
-                    (int)(time(NULL)-server.repl_transfer_lastio)
+                    (int)(server.unixtime-server.repl_transfer_lastio)
                 );
             }
 
             if (server.repl_state != REDIS_REPL_CONNECTED) {
                 info = sdscatprintf(info,
                     "master_link_down_since_seconds:%ld\r\n",
-                    (long)time(NULL)-server.repl_down_since);
+                    (long)server.unixtime-server.repl_down_since);
             }
         }
         info = sdscatprintf(info,