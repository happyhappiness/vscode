@@ -691,12 +691,14 @@ int activeExpireCycleTryExpire(redisDb *db, struct dictEntry *de, long long now)
  * No more than REDIS_DBCRON_DBS_PER_CALL databases are tested at every
  * iteration.
  *
- * If fast is non-zero the function will try to expire just one key ASAP
- * from the current DB and return. This kind of call is used when Redis detects
- * that timelimit_exit is true, so there is more work to do, and we do it
- * more incrementally from the beforeSleep() function of the event loop. */
+ * If fast is non-zero the function will try to run a "fast" expire cycle that
+ * takes no longer than EXPIRE_FAST_CYCLE_DURATION microseconds, and is not
+ * repeated again before the same amount of time.
+ *
+ * This kind of call is used when Redis detects that timelimit_exit is
+ * true, so there is more work to do, and we do it more incrementally from
+ * the beforeSleep() function of the event loop. */
 
-#define EXPIRED_HISTORY_LEN 10
 #define EXPIRE_FAST_CYCLE_DURATION 1000
 
 void activeExpireCycle(int fast) {
@@ -710,41 +712,15 @@ void activeExpireCycle(int fast) {
     long long start = ustime(), timelimit;
     static long long last_fast_cycle = 0;
 
-#if 0
-    static int expired_history[EXPIRED_HISTORY_LEN];
-    static int expired_history_id = 0;
-    static int expired_perc_avg = 0;
-#endif
-
     if (fast) {
         /* Don't start a fast cycle if the previous cycle did not exited
          * for time limt. Also don't repeat a fast cycle for the same period
          * as the fast cycle total duration itself. */
         if (!timelimit_exit) return;
-        if (start < last_fast_cycle + EXPIRE_FAST_CYCLE_DURATION) {
-            printf("CANT START A FAST CYCLE\n");
-            return;
-        }
+        if (start < last_fast_cycle + EXPIRE_FAST_CYCLE_DURATION) return;
         last_fast_cycle = start;
     }
 
-#if 0
-    if (fast) {
-        if (!timelimit_exit) return;
-
-        /* Let's try to expire a single key from the previous DB, the one that
-         * had enough keys expiring to reach the time limit. */
-        redisDb *db = server.db+((current_db+server.dbnum-1) % server.dbnum);
-        dictEntry *de;
-
-        for (j = 0; j < 100; j++) {
-            if ((de = dictGetRandomKey(db->expires)) == NULL) break;
-            activeExpireCycleTryExpire(db,de,server.mstime);
-        }
-        return;
-    }
-#endif
-
     /* We usually should test REDIS_DBCRON_DBS_PER_CALL per iteration, with
      * two exceptions:
      *
@@ -811,19 +787,6 @@ void activeExpireCycle(int fast) {
             {
                 timelimit_exit = 1;
             }
-#if 0
-            expired_history_id = (expired_history_id+1) % EXPIRED_HISTORY_LEN;
-            expired_history[expired_history_id] = expired;
-            {
-                int i;
-                expired_perc_avg = 0;
-                for (i = 0; i < EXPIRED_HISTORY_LEN; i++) {
-                    expired_perc_avg += expired_history[i];
-                }
-                expired_perc_avg = (expired_perc_avg * 100) / (REDIS_EXPIRELOOKUPS_PER_CRON*EXPIRED_HISTORY_LEN);
-                // printf("Expired AVG: %d\n", expired_perc_avg);
-            }
-#endif
             if (timelimit_exit) return;
         } while (expired > REDIS_EXPIRELOOKUPS_PER_CRON/4);
     }
@@ -944,12 +907,8 @@ void clientsCron(void) {
 void databasesCron(void) {
     /* Expire keys by random sampling. Not required for slaves
      * as master will synthesize DELs for us. */
-    if (server.active_expire_enabled && server.masterhost == NULL) {
-        long long totalex = server.stat_expiredkeys;
+    if (server.active_expire_enabled && server.masterhost == NULL)
         activeExpireCycle(0);
-        if (server.stat_expiredkeys - totalex)
-            printf("EXPIRED SLOW: %lld\n", server.stat_expiredkeys - totalex);
-    }
 
     /* Perform hash tables rehashing if needed, but only if there are no
      * other processes saving the DB on disk. Otherwise rehashing is bad
@@ -1192,12 +1151,7 @@ void beforeSleep(struct aeEventLoop *eventLoop) {
     redisClient *c;
 
     /* Run a fast expire cycle. */
-    {
-        long long totalex = server.stat_expiredkeys;
-        activeExpireCycle(1);
-        if (server.stat_expiredkeys - totalex)
-            printf("EXPIRED FAST: %lld\n", server.stat_expiredkeys - totalex);
-    }
+    activeExpireCycle(1);
 
     /* Try to process pending commands for clients that were just unblocked. */
     while (listLength(server.unblocked_clients)) {