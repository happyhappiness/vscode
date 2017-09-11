@@ -140,6 +140,7 @@ void analyzeLatencyForEvent(char *event, struct latencyStats *ls) {
     ls->max = 0;
     ls->mad = 0;
     ls->samples = 0;
+    ls->period = 0;
     if (!ts) return;
 
     /* First pass, populate everything but the MAD. */
@@ -156,8 +157,20 @@ void analyzeLatencyForEvent(char *event, struct latencyStats *ls) {
                 ls->max = ts->samples[j].latency;
         }
         sum += ts->samples[j].latency;
+
+        /* Track the oldest event time in ls->period. */
+        if (ls->period == 0 || ts->samples[j].time < ls->period)
+            ls->period = ts->samples[j].time;
+    }
+
+    /* So far avg is actually the sum of the latencies, and period is
+     * the oldest event time. We need to make the first an average and
+     * the second a range of seconds. */
+    if (ls->samples) {
+        ls->avg = sum / ls->samples;
+        ls->period = time(NULL) - ls->period;
+        if (ls->period == 0) ls->period = 1;
     }
-    if (ls->samples) ls->avg = sum / ls->samples;
 
     /* Second pass, compute MAD. */
     sum = 0;
@@ -172,6 +185,68 @@ void analyzeLatencyForEvent(char *event, struct latencyStats *ls) {
     if (ls->samples) ls->mad = sum / ls->samples;
 }
 
+/* Create a human readable report of latency events for this Redis instance. */
+sds createLatencyReport(void) {
+    sds report = sdsempty();
+
+    /* Return ASAP if the latency engine is disabled and it looks like it
+     * was never enabled so far. */
+    if (dictSize(server.latency_events) == 0 &&
+        server.latency_monitor_threshold == 0)
+    {
+        report = sdscat(report,"I'm sorry, Dave, I can't do that. Latency monitoring is disabled in this Redis instance. You may use \"CONFIG SET latency-monitor-threshold <milliseconds>.\" in order to enable it. If we weren't in a deep space mission I'd suggest to take a look at http://redis.io/topics/latency-monitor.");
+        return report;
+    }
+
+    /* Show all the events stats and add for each event some event-related
+     * comment depending on the values. */
+    dictIterator *di;
+    dictEntry *de;
+    int eventnum = 0;
+
+    di = dictGetIterator(server.latency_events);
+    while((de = dictNext(di)) != NULL) {
+        char *event = dictGetKey(de);
+        struct latencyTimeSeries *ts = dictGetVal(de);
+        struct latencyStats ls;
+        int nontrivial, severe;
+
+        if (ts == NULL) continue;
+        eventnum++;
+        if (eventnum == 1) {
+            report = sdscat(report,"Dave, I have observed latency spikes in this Redis instance. You don't mind talking about it, do you Dave?\n\n");
+        }
+        analyzeLatencyForEvent(event,&ls);
+
+        report = sdscatprintf(report,
+            "%d. %s: %d latency spikes (average %lums, mean deviation %lums, period %lu sec). Worst all time event %lums.",
+            eventnum, event,
+            ls.samples,
+            (unsigned long) ls.avg,
+            (unsigned long) ls.mad,
+            (unsigned long) ls.period/ls.samples,
+            (unsigned long) ts->max);
+
+        /* Add some event specific information. */
+        nontrivial = ts->max > 100;
+        severe = ts->max > 500;
+
+        /* Fork */
+        if (!strcasecmp(event,"fork")) {
+            double fork_bandwidth = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024); /* GB per second. */
+        }
+
+        report = sdscatlen(report,"\n",1);
+    }
+    dictReleaseIterator(di);
+
+    if (eventnum == 0) {
+        report = sdscat(report,"Dave, no latency spike was observed during the lifetime of this Redis instance, not in the slightest bit. I honestly think you ought to sit down calmly, take a stress pill, and think things over.\n");
+    }
+
+    return report;
+}
+
 /* ---------------------- Latency command implementation -------------------- */
 
 /* latencyCommand() helper to produce a time-delay reply for all the samples
@@ -293,6 +368,12 @@ void latencyCommand(redisClient *c) {
     } else if (!strcasecmp(c->argv[1]->ptr,"latest") && c->argc == 2) {
         /* LATENCY LATEST */
         latencyCommandReplyWithLatestEvents(c);
+    } else if (!strcasecmp(c->argv[1]->ptr,"doctor") && c->argc == 2) {
+        /* LATENCY DOCTOR */
+        sds report = createLatencyReport();
+
+        addReplyBulkCBuffer(c,report,sdslen(report));
+        sdsfree(report);
     } else if (!strcasecmp(c->argv[1]->ptr,"reset") && c->argc >= 2) {
         /* LATENCY RESET */
         if (c->argc == 2) {