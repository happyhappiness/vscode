@@ -893,6 +893,14 @@ struct redisMemOverhead *getMemoryOverheadData(void) {
     return mh;
 }
 
+/* Helper for "MEMORY allocator-stats", used as a callback for the jemalloc
+ * stats output. */
+void inputCatSds(void *result, const char *str) {
+    /* result is actually a (sds *), so re-cast it here */
+    sds *info = (sds *)result;
+    *info = sdscat(*info, str);
+}
+
 /* ======================= The OBJECT and MEMORY commands =================== */
 
 /* This is a helper function for the OBJECT command. We need to lookup keys
@@ -1023,12 +1031,41 @@ void memoryCommand(client *c) {
         addReplyDouble(c,mh->dataset_perc);
 
         freeMemoryOverheadData(mh);
+    } else if (!strcasecmp(c->argv[1]->ptr,"allocator-stats") && c->argc == 2) {
+#if defined(USE_JEMALLOC)
+        sds info = sdsempty();
+        je_malloc_stats_print(inputCatSds, &info, NULL);
+        addReplyBulkSds(c, info);
+#else
+        addReplyBulkCString(c,"Stats not supported for the current allocator");
+#endif
+    } else if (!strcasecmp(c->argv[1]->ptr,"purge") && c->argc == 2) {
+#if defined(USE_JEMALLOC)
+        char tmp[32];
+        unsigned narenas = 0;
+        size_t sz = sizeof(unsigned);
+        if (!je_mallctl("arenas.narenas", &narenas, &sz, NULL, 0)) {
+            sprintf(tmp, "arena.%d.purge", narenas);
+            if (!je_mallctl(tmp, NULL, 0, NULL, 0)) {
+                addReply(c, shared.ok);
+                return;
+            }
+        }
+        addReplyError(c, "Error purging dirty pages");
+#else
+        addReply(c, shared.ok);
+        /* Nothing to do for other allocators. */
+#endif
     } else if (!strcasecmp(c->argv[1]->ptr,"help") && c->argc == 2) {
-        addReplyMultiBulkLen(c,2);
+        addReplyMultiBulkLen(c,4);
+        addReplyBulkCString(c,
+"MEMORY USAGE <key> [SAMPLES <count>] - Estimate memory usage of key");
+        addReplyBulkCString(c,
+"MEMORY OVERHEAD                      - Show memory usage details");
         addReplyBulkCString(c,
-        "MEMORY USAGE <key> [SAMPLES <count>] - Estimate memory usage of key");
+"MEMORY PURGE                         - Ask the allocator to release memory");
         addReplyBulkCString(c,
-        "MEMORY OVERHEAD                      - Show memory usage details");
+"MEMORY ALLOCATOR-STATS               - Show allocator internal stats");
     } else {
         addReplyError(c,"Syntax error. Try MEMORY HELP");
     }