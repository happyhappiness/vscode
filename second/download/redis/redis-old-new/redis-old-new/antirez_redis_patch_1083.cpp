@@ -654,14 +654,51 @@ void updateDictResizePolicy(void) {
 
 /* ======================= Cron: called every 100 ms ======================== */
 
+/* Helper function for the activeExpireCycle() function.
+ * This function will try to expire the key that is stored in the hash table
+ * entry 'de' of the 'expires' hash table of a Redis database.
+ *
+ * If the key is found to be expired, it is removed from the database and
+ * 1 is returned. Otherwise no operation is performed and 0 is returned.
+ *
+ * When a key is expired, server.stat_expiredkeys is incremented.
+ *
+ * The parameter 'now' is the current time in milliseconds as is passed
+ * to the function to avoid too many gettimeofday() syscalls. */
+int activeExpireCycleTryExpire(redisDb *db, struct dictEntry *de, long long now) {
+    long long t = dictGetSignedIntegerVal(de);
+    if (now > t) {
+        sds key = dictGetKey(de);
+        robj *keyobj = createStringObject(key,sdslen(key));
+
+        propagateExpire(db,keyobj);
+        dbDelete(db,keyobj);
+        notifyKeyspaceEvent(REDIS_NOTIFY_EXPIRED,
+            "expired",keyobj,db->id);
+        decrRefCount(keyobj);
+        server.stat_expiredkeys++;
+        return 1;
+    } else {
+        return 0;
+    }
+}
+
 /* Try to expire a few timed out keys. The algorithm used is adaptive and
  * will use few CPU cycles if there are few expiring keys, otherwise
  * it will get more aggressive to avoid that too much memory is used by
  * keys that can be removed from the keyspace.
  *
  * No more than REDIS_DBCRON_DBS_PER_CALL databases are tested at every
- * iteration. */
-void activeExpireCycle(void) {
+ * iteration.
+ *
+ * If fast is non-zero the function will try to expire just one key ASAP
+ * from the current DB and return. This kind of call is used when Redis detects
+ * that timelimit_exit is true, so there is more work to do, and we do it
+ * more incrementally from the beforeSleep() function of the event loop. */
+
+#define EXPIRED_HISTORY_LEN 10
+
+void activeExpireCycle(int fast) {
     /* This function has some global state in order to continue the work
      * incrementally across calls. */
     static unsigned int current_db = 0; /* Last DB tested. */
@@ -671,6 +708,31 @@ void activeExpireCycle(void) {
     unsigned int dbs_per_call = REDIS_DBCRON_DBS_PER_CALL;
     long long start = ustime(), timelimit;
 
+#if 0
+    static int expired_history[EXPIRED_HISTORY_LEN];
+    static int expired_history_id = 0;
+    static int expired_perc_avg = 0;
+#endif
+
+    if (fast && !timelimit_exit) return;
+
+#if 0
+    if (fast) {
+        if (!timelimit_exit) return;
+
+        /* Let's try to expire a single key from the previous DB, the one that
+         * had enough keys expiring to reach the time limit. */
+        redisDb *db = server.db+((current_db+server.dbnum-1) % server.dbnum);
+        dictEntry *de;
+
+        for (j = 0; j < 100; j++) {
+            if ((de = dictGetRandomKey(db->expires)) == NULL) break;
+            activeExpireCycleTryExpire(db,de,server.mstime);
+        }
+        return;
+    }
+#endif
+
     /* We usually should test REDIS_DBCRON_DBS_PER_CALL per iteration, with
      * two exceptions:
      *
@@ -689,6 +751,8 @@ void activeExpireCycle(void) {
     timelimit_exit = 0;
     if (timelimit <= 0) timelimit = 1;
 
+    if (fast) timelimit = 1000; /* 1 millisecond. */
+
     for (j = 0; j < dbs_per_call; j++) {
         int expired;
         redisDb *db = server.db+(current_db % server.dbnum);
@@ -722,22 +786,9 @@ void activeExpireCycle(void) {
                 num = REDIS_EXPIRELOOKUPS_PER_CRON;
             while (num--) {
                 dictEntry *de;
-                long long t;
 
                 if ((de = dictGetRandomKey(db->expires)) == NULL) break;
-                t = dictGetSignedIntegerVal(de);
-                if (now > t) {
-                    sds key = dictGetKey(de);
-                    robj *keyobj = createStringObject(key,sdslen(key));
-
-                    propagateExpire(db,keyobj);
-                    dbDelete(db,keyobj);
-                    notifyKeyspaceEvent(REDIS_NOTIFY_EXPIRED,
-                        "expired",keyobj,db->id);
-                    decrRefCount(keyobj);
-                    expired++;
-                    server.stat_expiredkeys++;
-                }
+                if (activeExpireCycleTryExpire(db,de,now)) expired++;
             }
             /* We can't block forever here even if there are many keys to
              * expire. So after a given amount of milliseconds return to the
@@ -747,8 +798,21 @@ void activeExpireCycle(void) {
                 (ustime()-start) > timelimit)
             {
                 timelimit_exit = 1;
-                return;
             }
+#if 0
+            expired_history_id = (expired_history_id+1) % EXPIRED_HISTORY_LEN;
+            expired_history[expired_history_id] = expired;
+            {
+                int i;
+                expired_perc_avg = 0;
+                for (i = 0; i < EXPIRED_HISTORY_LEN; i++) {
+                    expired_perc_avg += expired_history[i];
+                }
+                expired_perc_avg = (expired_perc_avg * 100) / (REDIS_EXPIRELOOKUPS_PER_CRON*EXPIRED_HISTORY_LEN);
+                // printf("Expired AVG: %d\n", expired_perc_avg);
+            }
+#endif
+            if (timelimit_exit) return;
         } while (expired > REDIS_EXPIRELOOKUPS_PER_CRON/4);
     }
 }
@@ -868,8 +932,12 @@ void clientsCron(void) {
 void databasesCron(void) {
     /* Expire keys by random sampling. Not required for slaves
      * as master will synthesize DELs for us. */
-    if (server.active_expire_enabled && server.masterhost == NULL)
-        activeExpireCycle();
+    if (server.active_expire_enabled && server.masterhost == NULL) {
+        long long totalex = server.stat_expiredkeys;
+        activeExpireCycle(0);
+        if (server.stat_expiredkeys - totalex)
+            printf("EXPIRED SLOW: %lld\n", server.stat_expiredkeys - totalex);
+    }
 
     /* Perform hash tables rehashing if needed, but only if there are no
      * other processes saving the DB on disk. Otherwise rehashing is bad
@@ -941,6 +1009,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
      * in objects at every object access, and accuracy is not needed.
      * To access a global var is faster than calling time(NULL) */
     server.unixtime = time(NULL);
+    server.mstime = mstime();
 
     run_with_period(100) trackOperationsPerSecond();
 
@@ -1110,6 +1179,14 @@ void beforeSleep(struct aeEventLoop *eventLoop) {
     listNode *ln;
     redisClient *c;
 
+    /* Run a fast expire cycle. */
+    {
+        long long totalex = server.stat_expiredkeys;
+        activeExpireCycle(1);
+        if (server.stat_expiredkeys - totalex)
+            printf("EXPIRED FAST: %lld\n", server.stat_expiredkeys - totalex);
+    }
+
     /* Try to process pending commands for clients that were just unblocked. */
     while (listLength(server.unblocked_clients)) {
         ln = listFirst(server.unblocked_clients);
@@ -1513,6 +1590,7 @@ void initServer() {
     server.ops_sec_last_sample_time = mstime();
     server.ops_sec_last_sample_ops = 0;
     server.unixtime = time(NULL);
+    server.mstime = mstime();
     server.lastbgsave_status = REDIS_OK;
     server.repl_good_slaves_count = 0;
 