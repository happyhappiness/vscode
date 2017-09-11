@@ -58,7 +58,7 @@
 #define OUTPUT_RAW 1
 #define OUTPUT_CSV 2
 #define REDIS_CLI_KEEPALIVE_INTERVAL 15 /* seconds */
-#define REDIS_DEFAULT_PIPE_TIMEOUT 30 /* seconds */
+#define REDIS_CLI_DEFAULT_PIPE_TIMEOUT 30 /* seconds */
 
 static redisContext *context;
 static struct config {
@@ -82,6 +82,8 @@ static struct config {
     int getrdb_mode;
     int stat_mode;
     int scan_mode;
+    int intrinsic_latency_mode;
+    int intrinsic_latency_duration;
     char *pattern;
     char *rdb_filename;
     int bigkeys;
@@ -732,6 +734,9 @@ static int parseOptions(int argc, char **argv) {
             config.scan_mode = 1;
         } else if (!strcmp(argv[i],"--pattern")) {
             config.pattern = argv[++i];
+        } else if (!strcmp(argv[i],"--intrinsic-latency") && !lastarg) {
+            config.intrinsic_latency_mode = 1;
+            config.intrinsic_latency_duration = atoi(argv[++i]);
         } else if (!strcmp(argv[i],"--rdb") && !lastarg) {
             config.getrdb_mode = 1;
             config.rdb_filename = argv[++i];
@@ -817,6 +822,8 @@ static void usage() {
 "  --bigkeys          Sample Redis keys looking for big keys.\n"
 "  --scan             List all keys using the SCAN command.\n"
 "  --pattern <pat>    Useful with --scan to specify a SCAN pattern.\n"
+"  --intrinsic-latency <sec> Run a test to measure intrinsic system latency.\n"
+"                     The test will run for the specified amount of seconds.\n"
 "  --eval <file>      Send an EVAL command using the Lua script at <file>.\n"
 "  --help             Output this help and exit.\n"
 "  --version          Output version and exit.\n"
@@ -834,7 +841,7 @@ static void usage() {
 "When no command is given, redis-cli starts in interactive mode.\n"
 "Type \"help\" in interactive mode for information on available commands.\n"
 "\n",
-        version, REDIS_DEFAULT_PIPE_TIMEOUT);
+        version, REDIS_CLI_DEFAULT_PIPE_TIMEOUT);
     sdsfree(version);
     exit(1);
 }
@@ -1581,6 +1588,73 @@ static void scanMode() {
     exit(0);
 }
 
+/*------------------------------------------------------------------------------
+ * Intrisic latency mode.
+ *
+ * Measure max latency of a running process that does not result from
+ * syscalls. Basically this software should provide an hint about how much
+ * time the kernel leaves the process without a chance to run.
+ *--------------------------------------------------------------------------- */
+
+/* This is just some computation the compiler can't optimize out.
+ * Should run in less than 100-200 microseconds even using very
+ * slow hardware. Runs in less than 10 microseconds in modern HW. */
+uint64_t compute_something_fast(void) {
+    uint8_t s[256], i, j, t;
+    int count = 1000, k;
+    uint64_t output = 0;
+
+    for (k = 0; k < 256; k++) s[k] = k;
+
+    i = 0;
+    j = 0;
+    while(count--) {
+        i++;
+        j = j + s[i];
+        t = s[i];
+        s[i] = s[j];
+        s[j] = t;
+        output += s[(s[i]+s[j])&255];
+    }
+    return output;
+}
+
+static void intrinsicLatencyMode(void) {
+    long long test_end, run_time, max_latency = 0, runs = 0;
+
+    run_time = config.intrinsic_latency_duration*1000000;
+    test_end = ustime() + run_time;
+
+    while(1) {
+        long long start, end, latency;
+
+        start = ustime();
+        compute_something_fast();
+        end = ustime();
+        latency = end-start;
+        runs++;
+        if (latency <= 0) continue;
+
+        /* Reporting */
+        if (latency > max_latency) {
+            max_latency = latency;
+            printf("Max latency so far: %lld microseconds.\n", max_latency);
+        }
+
+        if (end > test_end) {
+            printf("\n%lld total runs (avg %lld microseconds per run).\n",
+                runs, run_time/runs);
+            printf("Worst run took %.02fx times the avarege.\n",
+                (double) max_latency / (run_time/runs));
+            exit(0);
+        }
+    }
+}
+
+/*------------------------------------------------------------------------------
+ * Program main()
+ *--------------------------------------------------------------------------- */
+
 int main(int argc, char **argv) {
     int firstarg;
 
@@ -1601,10 +1675,11 @@ int main(int argc, char **argv) {
     config.getrdb_mode = 0;
     config.stat_mode = 0;
     config.scan_mode = 0;
+    config.intrinsic_latency_mode = 0;
     config.pattern = NULL;
     config.rdb_filename = NULL;
     config.pipe_mode = 0;
-    config.pipe_timeout = REDIS_DEFAULT_PIPE_TIMEOUT;
+    config.pipe_timeout = REDIS_CLI_DEFAULT_PIPE_TIMEOUT;
     config.bigkeys = 0;
     config.stdinarg = 0;
     config.auth = NULL;
@@ -1663,6 +1738,9 @@ int main(int argc, char **argv) {
         scanMode();
     }
 
+    /* Intrinsic latency mode */
+    if (config.intrinsic_latency_mode) intrinsicLatencyMode();
+
     /* Start interactive mode when no command is provided */
     if (argc == 0 && !config.eval) {
         /* Note that in repl mode we don't abort on connection error.