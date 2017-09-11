@@ -307,7 +307,7 @@ void debugCommand(redisClient *c) {
             int remaining = sizeof(extra);
             quicklist *ql = val->ptr;
             double avg = (double)ql->count/ql->len;
-            int used = snprintf(nextra, remaining, " ql_nodes:%lu", ql->len);
+            int used = snprintf(nextra, remaining, " ql_nodes:%u", ql->len);
             nextra += used;
             remaining -= used;
             snprintf(nextra, remaining, " ql_avg_node:%.2f", avg);