@@ -1162,6 +1162,10 @@ int dictSdsKeyCompare(void *privdata, const void *key1, const void *key2);
 void dictSdsDestructor(void *privdata, void *val);
 void dictListDestructor(void *privdata, void *val);
 
+/* Sentinel config rewriting is implemented inside sentinel.c by
+ * rewriteConfigSentinelOption(). */
+void rewriteConfigSentinelOption(struct rewriteConfigState *state);
+
 dictType optionToLineDictType = {
     dictSdsHash,                /* hash function */
     NULL,                       /* key dup */
@@ -1735,6 +1739,7 @@ int rewriteConfig(char *path) {
     rewriteConfigClientoutputbufferlimitOption(state);
     rewriteConfigNumericalOption(state,"hz",server.hz,REDIS_DEFAULT_HZ);
     rewriteConfigYesNoOption(state,"aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync,REDIS_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC);
+    if (server.sentinel_mode) rewriteConfigSentinelOption(state);
 
     /* Step 3: remove all the orphaned lines in the old file, that is, lines
      * that were used by a config option and are no longer used, like in case