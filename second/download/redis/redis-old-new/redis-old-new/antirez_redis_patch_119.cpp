@@ -1328,7 +1328,7 @@ int rewriteAppendOnlyFileBackground(void) {
         redisSetProcTitle("redis-aof-rewrite");
         snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) getpid());
         if (rewriteAppendOnlyFile(tmpfile) == C_OK) {
-            size_t private_dirty = zmalloc_get_private_dirty();
+            size_t private_dirty = zmalloc_get_private_dirty(-1);
 
             if (private_dirty) {
                 serverLog(LL_NOTICE,