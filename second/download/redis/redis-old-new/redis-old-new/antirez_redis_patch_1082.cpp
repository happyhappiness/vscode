@@ -697,6 +697,7 @@ int activeExpireCycleTryExpire(redisDb *db, struct dictEntry *de, long long now)
  * more incrementally from the beforeSleep() function of the event loop. */
 
 #define EXPIRED_HISTORY_LEN 10
+#define EXPIRE_FAST_CYCLE_DURATION 1000
 
 void activeExpireCycle(int fast) {
     /* This function has some global state in order to continue the work
@@ -707,14 +708,25 @@ void activeExpireCycle(int fast) {
     unsigned int j, iteration = 0;
     unsigned int dbs_per_call = REDIS_DBCRON_DBS_PER_CALL;
     long long start = ustime(), timelimit;
+    static long long last_fast_cycle = 0;
 
 #if 0
     static int expired_history[EXPIRED_HISTORY_LEN];
     static int expired_history_id = 0;
     static int expired_perc_avg = 0;
 #endif
 
-    if (fast && !timelimit_exit) return;
+    if (fast) {
+        /* Don't start a fast cycle if the previous cycle did not exited
+         * for time limt. Also don't repeat a fast cycle for the same period
+         * as the fast cycle total duration itself. */
+        if (!timelimit_exit) return;
+        if (start < last_fast_cycle + EXPIRE_FAST_CYCLE_DURATION) {
+            printf("CANT START A FAST CYCLE\n");
+            return;
+        }
+        last_fast_cycle = start;
+    }
 
 #if 0
     if (fast) {
@@ -751,7 +763,7 @@ void activeExpireCycle(int fast) {
     timelimit_exit = 0;
     if (timelimit <= 0) timelimit = 1;
 
-    if (fast) timelimit = 1000; /* 1 millisecond. */
+    if (fast) timelimit = EXPIRE_FAST_CYCLE_DURATION; /* in microseconds. */
 
     for (j = 0; j < dbs_per_call; j++) {
         int expired;