@@ -79,6 +79,8 @@ static struct config {
     int latency_mode;
     int latency_dist_mode;
     int latency_history;
+    int lru_test_mode;
+    long long lru_test_sample_size;
     int cluster_mode;
     int cluster_reissue_command;
     int slave_mode;
@@ -781,6 +783,9 @@ static int parseOptions(int argc, char **argv) {
         } else if (!strcmp(argv[i],"--latency-history")) {
             config.latency_mode = 1;
             config.latency_history = 1;
+        } else if (!strcmp(argv[i],"--lru-test") && !lastarg) {
+            config.lru_test_mode = 1;
+            config.lru_test_sample_size = strtoll(argv[++i],NULL,10);
         } else if (!strcmp(argv[i],"--slave")) {
             config.slave_mode = 1;
         } else if (!strcmp(argv[i],"--stat")) {
@@ -872,6 +877,7 @@ static void usage(void) {
 "                     Default time interval is 15 sec. Change it using -i.\n"
 "  --latency-dist     Shows latency as a spectrum, requires xterm 256 colors.\n"
 "                     Default time interval is 1 sec. Change it using -i.\n"
+"  --lru-test <keys>  Simulate a cache workload with an 80-20 distribution.\n"
 "  --slave            Simulate a slave showing commands received from the master.\n"
 "  --rdb <filename>   Transfer an RDB dump from remote server to local file.\n"
 "  --pipe             Transfer raw Redis protocol from stdin to server.\n"
@@ -1992,6 +1998,94 @@ static void scanMode(void) {
 }
 
 /*------------------------------------------------------------------------------
+ * LRU test mode
+ *--------------------------------------------------------------------------- */
+
+/* Return an integer from min to max (both inclusive) using a power-law
+ * distribution, depending on the value of alpha: the greater the alpha
+ * the more bias towards lower values.
+ *
+ * With alpha = 6.2 the output follows the 80-20 rule where 20% of
+ * the returned numbers will account for 80% of the frequency. */
+long long powerLawRand(long long min, long long max, double alpha) {
+    double pl, r;
+
+    max += 1;
+    r = ((double)rand()) / RAND_MAX;
+    pl = pow(
+        ((pow(max,alpha+1) - pow(min,alpha+1))*r + pow(min,alpha+1)),
+        (1.0/(alpha+1)));
+    return (max-1-(long long)pl)+min;
+}
+
+/* Generates a key name among a set of lru_test_sample_size keys, using
+ * an 80-20 distribution. */
+void LRUTestGenKey(char *buf, size_t buflen) {
+    snprintf(buf, buflen, "lru:%lld\n",
+        powerLawRand(1, config.lru_test_sample_size, 6.2));
+}
+
+#define LRU_CYCLE_PERIOD 1000 /* 1000 milliseconds. */
+#define LRU_CYCLE_PIPELINE_SIZE 250
+static void LRUTestMode(void) {
+    redisReply *reply;
+    char key[128];
+    long long start_cycle;
+    int j;
+
+    srand(time(NULL)^getpid());
+    while(1) {
+        /* Perform cycles of 1 second with 50% writes and 50% reads.
+         * We use pipelining batching writes / reads N times per cycle in order
+         * to fill the target instance easily. */
+        start_cycle = mstime();
+        long long hits = 0, misses = 0;
+        while(mstime() - start_cycle < 1000) {
+            /* Write cycle. */
+            for (j = 0; j < LRU_CYCLE_PIPELINE_SIZE; j++) {
+                LRUTestGenKey(key,sizeof(key));
+                redisAppendCommand(context, "SET %s val",key);
+            }
+            for (j = 0; j < LRU_CYCLE_PIPELINE_SIZE; j++)
+                redisGetReply(context, (void**)&reply);
+
+            /* Read cycle. */
+            for (j = 0; j < LRU_CYCLE_PIPELINE_SIZE; j++) {
+                LRUTestGenKey(key,sizeof(key));
+                redisAppendCommand(context, "GET %s",key);
+            }
+            for (j = 0; j < LRU_CYCLE_PIPELINE_SIZE; j++) {
+                if (redisGetReply(context, (void**)&reply) == REDIS_OK) {
+                    switch(reply->type) {
+                        case REDIS_REPLY_ERROR:
+                            printf("%s\n", reply->str);
+                            break;
+                        case REDIS_REPLY_NIL:
+                            misses++;
+                            break;
+                        default:
+                            hits++;
+                            break;
+                    }
+                }
+            }
+
+            if (context->err) {
+                fprintf(stderr,"I/O error during LRU test\n");
+                exit(1);
+            }
+        }
+        /* Print stats. */
+        printf(
+            "%lld Gets/sec | Hits: %lld (%.2f%%) | Misses: %lld (%.2f%%)\n",
+            hits+misses,
+            hits, (double)hits/(hits+misses)*100,
+            misses, (double)misses/(hits+misses)*100);
+    }
+    exit(0);
+}
+
+/*------------------------------------------------------------------------------
  * Intrisic latency mode.
  *
  * Measure max latency of a running process that does not result from
@@ -2084,6 +2178,8 @@ int main(int argc, char **argv) {
     config.latency_mode = 0;
     config.latency_dist_mode = 0;
     config.latency_history = 0;
+    config.lru_test_mode = 0;
+    config.lru_test_sample_size = 0;
     config.cluster_mode = 0;
     config.slave_mode = 0;
     config.getrdb_mode = 0;
@@ -2160,6 +2256,12 @@ int main(int argc, char **argv) {
         scanMode();
     }
 
+    /* LRU test mode */
+    if (config.lru_test_mode) {
+        if (cliConnect(0) == REDIS_ERR) exit(1);
+        LRUTestMode();
+    }
+
     /* Intrinsic latency mode */
     if (config.intrinsic_latency_mode) intrinsicLatencyMode();
 