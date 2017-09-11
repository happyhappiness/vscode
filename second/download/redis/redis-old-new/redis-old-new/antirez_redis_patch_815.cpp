@@ -140,6 +140,53 @@ void latencyCommandReplyWithLatestEvents(redisClient *c) {
     dictReleaseIterator(di);
 }
 
+#define LATENCY_GRAPH_COLS 80
+sds latencyCommandGenSparkeline(char *event, struct latencyTimeSeries *ts) {
+    int j;
+    struct sequence *seq = createSparklineSequence();
+    sds graph = sdsempty();
+    uint32_t min, max;
+
+    for (j = 0; j < LATENCY_TS_LEN; j++) {
+        int i = (ts->idx + j) % LATENCY_TS_LEN;
+        int elapsed;
+        char *label;
+        char buf[64];
+
+        if (ts->samples[i].time == 0) continue;
+        /* Update min and max. */
+        if (seq->length == 0) {
+            min = max = ts->samples[i].latency;
+        } else {
+            if (ts->samples[i].latency > max) max = ts->samples[i].latency;
+            if (ts->samples[i].latency < min) min = ts->samples[i].latency;
+        }
+        /* Use as label the number of seconds / minutes / hours / days
+         * ago the event happened. */
+        elapsed = time(NULL) - ts->samples[i].time;
+        if (elapsed < 60)
+            snprintf(buf,sizeof(buf),"%ds",elapsed);
+        else if (elapsed < 3600)
+            snprintf(buf,sizeof(buf),"%dm",elapsed/60);
+        else if (elapsed < 3600*24)
+            snprintf(buf,sizeof(buf),"%dh",elapsed/3600);
+        else
+            snprintf(buf,sizeof(buf),"%dd",elapsed/(3600*24));
+        label = zstrdup(buf);
+        sparklineSequenceAddSample(seq,ts->samples[i].latency,label);
+    }
+
+    graph = sdscatprintf(graph,
+        "%s - high %lu ms, low %lu ms (all time high %lu ms)\n", event,
+        (unsigned long) max, (unsigned long) min, (unsigned long) ts->max);
+    for (j = 0; j < LATENCY_GRAPH_COLS; j++)
+        graph = sdscatlen(graph,"-",1);
+    graph = sdscatlen(graph,"\n",1);
+    graph = sparklineRender(graph,seq,LATENCY_GRAPH_COLS,4,SPARKLINE_NO_FLAGS);
+    freeSparklineSequence(seq);
+    return graph;
+}
+
 /* LATENCY command implementations.
  *
  * LATENCY SAMPLES: return time-latency samples for the specified event.
@@ -155,12 +202,25 @@ void latencyCommand(redisClient *c) {
         ts = dictFetchValue(server.latency_events,c->argv[2]->ptr);
         if (ts == NULL) goto nodataerr;
         latencyCommandReplyWithSamples(c,ts);
+    } else if (!strcasecmp(c->argv[1]->ptr,"graph") && c->argc == 3) {
+        /* LATENCY GRAPH <event> */
+        sds graph;
+        dictEntry *de;
+        char *event;
+
+        de = dictFind(server.latency_events,c->argv[2]->ptr);
+        if (de == NULL) goto nodataerr;
+        ts = dictGetVal(de);
+        event = dictGetKey(de);
+
+        graph = latencyCommandGenSparkeline(event,ts);
+        addReplyBulkCString(c,graph);
+        sdsfree(graph);
     } else if (!strcasecmp(c->argv[1]->ptr,"latest") && c->argc == 2) {
         /* LATENCY LATEST */
         latencyCommandReplyWithLatestEvents(c);
     } else {
         addReply(c,shared.syntaxerr);
-        return;
     }
     return;
 