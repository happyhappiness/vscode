@@ -252,6 +252,12 @@ void computeDatasetDigest(unsigned char *final) {
     }
 }
 
+void inputCatSds(void *result, const char *str) {
+    /* result is actually a (sds *), so re-cast it here */
+    sds *info = (sds *)result;
+    *info = sdscat(*info, str);
+}
+
 void debugCommand(redisClient *c) {
     if (!strcasecmp(c->argv[1]->ptr,"segfault")) {
         *((char*)-1) = 'x';
@@ -295,13 +301,46 @@ void debugCommand(redisClient *c) {
         val = dictGetVal(de);
         strenc = strEncoding(val->encoding);
 
+        char extra[128] = {0};
+        if (val->encoding == REDIS_ENCODING_QUICKLIST) {
+            char *nextra = extra;
+            int remaining = sizeof(extra);
+            quicklist *ql = val->ptr;
+            /* Add number of quicklist nodes */
+            int used = snprintf(nextra, remaining, " ql_nodes:%u", ql->len);
+            nextra += used;
+            remaining -= used;
+            /* Add average quicklist fill factor */
+            double avg = (double)ql->count/ql->len;
+            used = snprintf(nextra, remaining, " ql_avg_node:%.2f", avg);
+            nextra += used;
+            remaining -= used;
+            /* Add quicklist fill level / max ziplist size */
+            used = snprintf(nextra, remaining, " ql_ziplist_max:%d", ql->fill);
+            nextra += used;
+            remaining -= used;
+            /* Add isCompressed? */
+            int compressed = ql->compress != 0;
+            used = snprintf(nextra, remaining, " ql_compressed:%d", compressed);
+            nextra += used;
+            remaining -= used;
+            /* Add total uncompressed size */
+            unsigned long sz = 0;
+            for (quicklistNode *node = ql->head; node; node = node->next) {
+                sz += node->sz;
+            }
+            used = snprintf(nextra, remaining, " ql_uncompressed_size:%lu", sz);
+            nextra += used;
+            remaining -= used;
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
@@ -379,6 +418,18 @@ void debugCommand(redisClient *c) {
         errstr = sdsmapchars(errstr,"\n\r","  ",2); /* no newlines in errors. */
         errstr = sdscatlen(errstr,"\r\n",2);
         addReplySds(c,errstr);
+    } else if (!strcasecmp(c->argv[1]->ptr,"jemalloc") && c->argc == 3) {
+#if defined(USE_JEMALLOC)
+        if (!strcasecmp(c->argv[2]->ptr, "info")) {
+            sds info = sdsempty();
+            je_malloc_stats_print(inputCatSds, &info, NULL);
+            addReplyBulkSds(c, info);
+        } else {
+            addReplyErrorFormat(c, "Valid jemalloc debug fields: info");
+        }
+#else
+        addReplyErrorFormat(c, "jemalloc support not available");
+#endif
     } else {
         addReplyErrorFormat(c, "Unknown DEBUG subcommand or wrong number of arguments for '%s'",
             (char*)c->argv[1]->ptr);