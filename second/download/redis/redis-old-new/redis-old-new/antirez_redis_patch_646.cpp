@@ -301,13 +301,25 @@ void debugCommand(redisClient *c) {
         val = dictGetVal(de);
         strenc = strEncoding(val->encoding);
 
+        char extra[128] = {0};
+        if (val->encoding == REDIS_ENCODING_QUICKLIST) {
+            char *nextra = extra;
+            int remaining = sizeof(extra);
+            quicklist *ql = val->ptr;
+            double avg = (double)ql->count/ql->len;
+            int used = snprintf(nextra, remaining, " ql_nodes:%lu", ql->len);
+            nextra += used;
+            remaining -= used;
+            snprintf(nextra, remaining, " ql_avg_node:%.2f", avg);
+        }
+
         addReplyStatusFormat(c,
             "Value at:%p refcount:%d "
             "encoding:%s serializedlength:%lld "
-            "lru:%d lru_seconds_idle:%llu",
+            "lru:%d lru_seconds_idle:%llu%s",
             (void*)val, val->refcount,
             strenc, (long long) rdbSavedObjectLen(val),
-            val->lru, estimateObjectIdleTime(val)/1000);
+            val->lru, estimateObjectIdleTime(val)/1000, extra);
     } else if (!strcasecmp(c->argv[1]->ptr,"sdslen") && c->argc == 3) {
         dictEntry *de;
         robj *val;