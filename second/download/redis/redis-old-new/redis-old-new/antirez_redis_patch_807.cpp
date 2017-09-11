@@ -178,7 +178,7 @@ void analyzeLatencyForEvent(char *event, struct latencyStats *ls) {
         int64_t delta;
 
         if (ts->samples[j].time == 0) continue;
-        delta = ls->avg - ts->samples[j].latency;
+        delta = (int64_t)ls->avg - ts->samples[j].latency;
         if (delta < 0) delta = -delta;
         sum += delta;
     }
@@ -219,12 +219,12 @@ sds createLatencyReport(void) {
         analyzeLatencyForEvent(event,&ls);
 
         report = sdscatprintf(report,
-            "%d. %s: %d latency spikes (average %lums, mean deviation %lums, period %lu sec). Worst all time event %lums.",
+            "%d. %s: %d latency spikes (average %lums, mean deviation %lums, period %.2f sec). Worst all time event %lums.",
             eventnum, event,
             ls.samples,
             (unsigned long) ls.avg,
             (unsigned long) ls.mad,
-            (unsigned long) ls.period/ls.samples,
+            (double) ls.period/ls.samples,
             (unsigned long) ts->max);
 
         /* Add some event specific information. */