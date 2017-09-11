@@ -475,7 +475,6 @@ sds latencyCommandGenSparkeline(char *event, struct latencyTimeSeries *ts) {
     for (j = 0; j < LATENCY_TS_LEN; j++) {
         int i = (ts->idx + j) % LATENCY_TS_LEN;
         int elapsed;
-        char *label;
         char buf[64];
 
         if (ts->samples[i].time == 0) continue;
@@ -497,8 +496,7 @@ sds latencyCommandGenSparkeline(char *event, struct latencyTimeSeries *ts) {
             snprintf(buf,sizeof(buf),"%dh",elapsed/3600);
         else
             snprintf(buf,sizeof(buf),"%dd",elapsed/(3600*24));
-        label = zstrdup(buf);
-        sparklineSequenceAddSample(seq,ts->samples[i].latency,label);
+        sparklineSequenceAddSample(seq,ts->samples[i].latency,buf);
     }
 
     graph = sdscatprintf(graph,