     rewriteConfigNumericalOption(state,"hash-max-ziplist-value",server.hash_max_ziplist_value,REDIS_HASH_MAX_ZIPLIST_VALUE);
     rewriteConfigNumericalOption(state,"list-max-ziplist-entries",server.list_max_ziplist_entries,REDIS_LIST_MAX_ZIPLIST_ENTRIES);
     rewriteConfigNumericalOption(state,"list-max-ziplist-value",server.list_max_ziplist_value,REDIS_LIST_MAX_ZIPLIST_VALUE);
     rewriteConfigNumericalOption(state,"set-max-intset-entries",server.set_max_intset_entries,REDIS_SET_MAX_INTSET_ENTRIES);
     rewriteConfigNumericalOption(state,"zset-max-ziplist-entries",server.zset_max_ziplist_entries,REDIS_ZSET_MAX_ZIPLIST_ENTRIES);
     rewriteConfigNumericalOption(state,"zset-max-ziplist-value",server.zset_max_ziplist_value,REDIS_ZSET_MAX_ZIPLIST_VALUE);
+    rewriteConfigNumericalOption(state,"hll-sparse-max-bytes",server.hll_sparse_max_bytes,REDIS_DEFAULT_HLL_SPARSE_MAX_BYTES);
     rewriteConfigYesNoOption(state,"activerehashing",server.activerehashing,REDIS_DEFAULT_ACTIVE_REHASHING);
     rewriteConfigClientoutputbufferlimitOption(state);
     rewriteConfigNumericalOption(state,"hz",server.hz,REDIS_DEFAULT_HZ);
     rewriteConfigYesNoOption(state,"aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync,REDIS_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC);
     if (server.sentinel_mode) rewriteConfigSentinelOption(state);
 
