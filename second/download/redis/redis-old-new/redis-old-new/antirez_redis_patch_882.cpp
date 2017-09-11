@@ -391,6 +391,8 @@ void loadServerConfigFromString(char *config) {
             server.zset_max_ziplist_entries = memtoll(argv[1], NULL);
         } else if (!strcasecmp(argv[0],"zset-max-ziplist-value") && argc == 2) {
             server.zset_max_ziplist_value = memtoll(argv[1], NULL);
+        } else if (!strcasecmp(argv[0],"hll-sparse-max-bytes") && argc == 2) {
+            server.hll_sparse_max_bytes = memtoll(argv[1], NULL);
         } else if (!strcasecmp(argv[0],"rename-command") && argc == 3) {
             struct redisCommand *cmd = lookupCommand(argv[1]);
             int retval;
@@ -765,6 +767,9 @@ void configSetCommand(redisClient *c) {
     } else if (!strcasecmp(c->argv[2]->ptr,"zset-max-ziplist-value")) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
         server.zset_max_ziplist_value = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"hll-sparse-max-bytes")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
+        server.hll_sparse_max_bytes = ll;
     } else if (!strcasecmp(c->argv[2]->ptr,"lua-time-limit")) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
         server.lua_time_limit = ll;
@@ -974,6 +979,8 @@ void configGetCommand(redisClient *c) {
             server.zset_max_ziplist_entries);
     config_get_numerical_field("zset-max-ziplist-value",
             server.zset_max_ziplist_value);
+    config_get_numerical_field("hll-sparse-max-bytes",
+            server.hll_sparse_max_bytes);
     config_get_numerical_field("lua-time-limit",server.lua_time_limit);
     config_get_numerical_field("slowlog-log-slower-than",
             server.slowlog_log_slower_than);
@@ -1773,6 +1780,7 @@ int rewriteConfig(char *path) {
     rewriteConfigNumericalOption(state,"set-max-intset-entries",server.set_max_intset_entries,REDIS_SET_MAX_INTSET_ENTRIES);
     rewriteConfigNumericalOption(state,"zset-max-ziplist-entries",server.zset_max_ziplist_entries,REDIS_ZSET_MAX_ZIPLIST_ENTRIES);
     rewriteConfigNumericalOption(state,"zset-max-ziplist-value",server.zset_max_ziplist_value,REDIS_ZSET_MAX_ZIPLIST_VALUE);
+    rewriteConfigNumericalOption(state,"hll-sparse-max-bytes",server.hll_sparse_max_bytes,REDIS_DEFAULT_HLL_SPARSE_MAX_BYTES);
     rewriteConfigYesNoOption(state,"activerehashing",server.activerehashing,REDIS_DEFAULT_ACTIVE_REHASHING);
     rewriteConfigClientoutputbufferlimitOption(state);
     rewriteConfigNumericalOption(state,"hz",server.hz,REDIS_DEFAULT_HZ);