@@ -95,6 +95,7 @@ static struct config {
     char *eval;
 } config;
 
+static volatile sig_atomic_t force_cancel_loop = 0;
 static void usage();
 static void slaveMode(void);
 char *redisGitSHA1(void);
@@ -1807,11 +1808,17 @@ unsigned long compute_something_fast(void) {
     return output;
 }
 
+static void intrinsicLatencyModeStop(int s) {
+    REDIS_NOTUSED(s);
+    force_cancel_loop = 1;
+}
+
 static void intrinsicLatencyMode(void) {
     long long test_end, run_time, max_latency = 0, runs = 0;
 
     run_time = config.intrinsic_latency_duration*1000000;
     test_end = ustime() + run_time;
+    signal(SIGINT, intrinsicLatencyModeStop);
 
     while(1) {
         long long start, end, latency;
@@ -1829,7 +1836,7 @@ static void intrinsicLatencyMode(void) {
             printf("Max latency so far: %lld microseconds.\n", max_latency);
         }
 
-        if (end > test_end) {
+        if (force_cancel_loop || end > test_end) {
             printf("\n%lld total runs (avg %lld microseconds per run).\n",
                 runs, run_time/runs);
             printf("Worst run took %.02fx times the average.\n",