@@ -89,5 +89,49 @@ void latencyAddSample(char *event, mstime_t latency) {
 
 /* ---------------------- Latency command implementation -------------------- */
 
+/* latencyCommand() helper to produce a time-delay reply for all the samples
+ * in memory for the specified time series. */
+void latencyCommandReplyWithSamples(redisClient *c, struct latencyTimeSeries *ts) {
+    void *replylen = addDeferredMultiBulkLength(c);
+    int samples = 0, j;
+
+    for (j = 0; j < LATENCY_TS_LEN; j++) {
+        int i = (ts->idx + j) % LATENCY_TS_LEN;
+
+        if (ts->samples[i].time == 0) continue;
+        addReplyMultiBulkLen(c,2);
+        addReplyLongLong(c,ts->samples[i].time);
+        addReplyLongLong(c,ts->samples[i].latency);
+        samples++;
+    }
+    setDeferredMultiBulkLength(c,replylen,samples);
+}
+
+/* LATENCY command implementations.
+ *
+ * LATENCY SAMPLES: return time-latency samples for the specified event.
+ * LATENCY LATEST: return the latest latency for all the events classes.
+ * LATENCY DOCTOR: returns an human readable analysis of instance latency.
+ * LATENCY GRAPH: provide an ASCII graph of the latency of the specified event.
+ */
 void latencyCommand(redisClient *c) {
+    struct latencyTimeSeries *ts;
+
+    if (!strcasecmp(c->argv[1]->ptr,"samples") && c->argc == 3) {
+        /* LATENCY SAMPLES <event> */
+        ts = dictFetchValue(server.latency_events,c->argv[2]->ptr);
+        if (ts == NULL) goto nodataerr;
+        latencyCommandReplyWithSamples(c,ts);
+    } else {
+        addReply(c,shared.syntaxerr);
+        return;
+    }
+    return;
+
+nodataerr:
+    /* Common error when the user asks for an event we have no latency
+     * information about. */
+    addReplyErrorFormat(c,
+        "No samples available for event '%s'", c->argv[2]->ptr);
 }
+