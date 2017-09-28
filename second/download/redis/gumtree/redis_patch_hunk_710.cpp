     rewriteConfigNumericalOption(state,"list-compress-depth",server.list_compress_depth,OBJ_LIST_COMPRESS_DEPTH);
     rewriteConfigNumericalOption(state,"set-max-intset-entries",server.set_max_intset_entries,OBJ_SET_MAX_INTSET_ENTRIES);
     rewriteConfigNumericalOption(state,"zset-max-ziplist-entries",server.zset_max_ziplist_entries,OBJ_ZSET_MAX_ZIPLIST_ENTRIES);
     rewriteConfigNumericalOption(state,"zset-max-ziplist-value",server.zset_max_ziplist_value,OBJ_ZSET_MAX_ZIPLIST_VALUE);
     rewriteConfigNumericalOption(state,"hll-sparse-max-bytes",server.hll_sparse_max_bytes,CONFIG_DEFAULT_HLL_SPARSE_MAX_BYTES);
     rewriteConfigYesNoOption(state,"activerehashing",server.activerehashing,CONFIG_DEFAULT_ACTIVE_REHASHING);
+    rewriteConfigYesNoOption(state,"activedefrag",server.active_defrag_enabled,CONFIG_DEFAULT_ACTIVE_DEFRAG);
     rewriteConfigYesNoOption(state,"protected-mode",server.protected_mode,CONFIG_DEFAULT_PROTECTED_MODE);
     rewriteConfigClientoutputbufferlimitOption(state);
     rewriteConfigNumericalOption(state,"hz",server.hz,CONFIG_DEFAULT_HZ);
     rewriteConfigYesNoOption(state,"aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync,CONFIG_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC);
     rewriteConfigYesNoOption(state,"aof-load-truncated",server.aof_load_truncated,CONFIG_DEFAULT_AOF_LOAD_TRUNCATED);
+    rewriteConfigYesNoOption(state,"aof-use-rdb-preamble",server.aof_use_rdb_preamble,CONFIG_DEFAULT_AOF_USE_RDB_PREAMBLE);
     rewriteConfigEnumOption(state,"supervised",server.supervised_mode,supervised_mode_enum,SUPERVISED_NONE);
+    rewriteConfigYesNoOption(state,"lazyfree-lazy-eviction",server.lazyfree_lazy_eviction,CONFIG_DEFAULT_LAZYFREE_LAZY_EVICTION);
+    rewriteConfigYesNoOption(state,"lazyfree-lazy-expire",server.lazyfree_lazy_expire,CONFIG_DEFAULT_LAZYFREE_LAZY_EXPIRE);
+    rewriteConfigYesNoOption(state,"lazyfree-lazy-server-del",server.lazyfree_lazy_server_del,CONFIG_DEFAULT_LAZYFREE_LAZY_SERVER_DEL);
+    rewriteConfigYesNoOption(state,"slave-lazy-flush",server.repl_slave_lazy_flush,CONFIG_DEFAULT_SLAVE_LAZY_FLUSH);
 
     /* Rewrite Sentinel config if in Sentinel mode. */
     if (server.sentinel_mode) rewriteConfigSentinelOption(state);
 
     /* Step 3: remove all the orphaned lines in the old file, that is, lines
      * that were used by a config option and are no longer used, like in case
