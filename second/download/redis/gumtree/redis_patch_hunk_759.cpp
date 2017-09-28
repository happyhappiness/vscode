 }
 
 /*------------------------------------------------------------------------------
  * Latency and latency history modes
  *--------------------------------------------------------------------------- */
 
+static void latencyModePrint(long long min, long long max, double avg, long long count) {
+    if (config.output == OUTPUT_STANDARD) {
+        printf("min: %lld, max: %lld, avg: %.2f (%lld samples)",
+                min, max, avg, count);
+        fflush(stdout);
+    } else if (config.output == OUTPUT_CSV) {
+        printf("%lld,%lld,%.2f,%lld\n", min, max, avg, count);
+    } else if (config.output == OUTPUT_RAW) {
+        printf("%lld %lld %.2f %lld\n", min, max, avg, count);
+    }
+}
+
 #define LATENCY_SAMPLE_RATE 10 /* milliseconds. */
 #define LATENCY_HISTORY_DEFAULT_INTERVAL 15000 /* milliseconds. */
 static void latencyMode(void) {
     redisReply *reply;
     long long start, latency, min = 0, max = 0, tot = 0, count = 0;
     long long history_interval =
         config.interval ? config.interval/1000 :
                           LATENCY_HISTORY_DEFAULT_INTERVAL;
     double avg;
     long long history_start = mstime();
 
+    /* Set a default for the interval in case of --latency option
+     * with --raw, --csv or when it is redirected to non tty. */
+    if (config.interval == 0) {
+        config.interval = 1000;
+    } else {
+        config.interval /= 1000; /* We need to convert to milliseconds. */
+    }
+
     if (!context) exit(1);
     while(1) {
         start = mstime();
         reply = reconnectingRedisCommand(context,"PING");
         if (reply == NULL) {
             fprintf(stderr,"\nI/O error\n");
