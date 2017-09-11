@@ -1123,6 +1123,12 @@ static void usage(void) {
 "  --csv              Output in CSV format.\n"
 "  --stat             Print rolling stats about server: mem, clients, ...\n"
 "  --latency          Enter a special mode continuously sampling latency.\n"
+"                     If you use this mode in an interactive session it runs\n"
+"                     forever displaying real-time stats. Otherwise if --raw or\n"
+"                     --csv is specified, or if you redirect the output to a non\n"
+"                     TTY, it samples the latency for 1 second (you can use\n"
+"                     -i to change the interval), then produces a single output\n"
+"                     and exits.\n"
 "  --latency-history  Like --latency but tracking latency changes over time.\n"
 "                     Default time interval is 15 sec. Change it using -i.\n"
 "  --latency-dist     Shows latency as a spectrum, requires xterm 256 colors.\n"
@@ -1472,6 +1478,18 @@ static int evalMode(int argc, char **argv) {
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
@@ -1483,6 +1501,14 @@ static void latencyMode(void) {
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
@@ -1503,9 +1529,19 @@ static void latencyMode(void) {
             tot += latency;
             avg = (double) tot/count;
         }
-        printf("\x1b[0G\x1b[2Kmin: %lld, max: %lld, avg: %.2f (%lld samples)",
-            min, max, avg, count);
-        fflush(stdout);
+
+        if (config.output == OUTPUT_STANDARD) {
+            printf("\x1b[0G\x1b[2K"); /* Clear the line. */
+            latencyModePrint(min,max,avg,count);
+        } else {
+            if (config.latency_history) {
+                latencyModePrint(min,max,avg,count);
+            } else if (mstime()-history_start > config.interval) {
+                latencyModePrint(min,max,avg,count);
+                exit(0);
+            }
+        }
+
         if (config.latency_history && mstime()-history_start > history_interval)
         {
             printf(" -- %.2f seconds range\n", (float)(mstime()-history_start)/1000);