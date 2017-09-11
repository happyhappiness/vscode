            server.client_obuf_limits[class].soft_limit_seconds = soft_seconds;
        }
        sdsfreesplitres(v,vlen);
    } else if (!strcasecmp(c->argv[2]->ptr,"repl-backlog-size")) {
        ll = memtoll(o->ptr,&err);
        if (err || ll < 0) goto badfmt;
        resizeReplicationBacklog(ll);
    } else if (!strcasecmp(c->argv[2]->ptr,"watchdog-period")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        if (ll)
            enableWatchdog(ll);
        else
            disableWatchdog();
    } else if (!strcasecmp(c->argv[2]->ptr,"notify-keyspace-events")) {
        int flags = keyspaceEventsStringToFlags(o->ptr);

        if (flags == -1) goto badfmt;
        server.notify_keyspace_events = flags;

    /* Boolean fields.
     * config_set_bool_field(name,var). */
    config_set_bool_field(
      "rdbcompression", server.rdb_compression) {
    } config_set_bool_field(
      "repl-disable-tcp-nodelay",server.repl_disable_tcp_nodelay) {
    } config_set_bool_field(
      "repl-diskless-sync",server.repl_diskless_sync) {
    } config_set_bool_field(
      "cluster-require-full-coverage",server.cluster_require_full_coverage) {
    } config_set_bool_field(
      "aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync) {
    } config_set_bool_field(
      "aof-load-truncated",server.aof_load_truncated) {
    } config_set_bool_field(
      "slave-serve-stale-data",server.repl_serve_stale_data) {
    } config_set_bool_field(
      "slave-read-only",server.repl_slave_ro) {
    } config_set_bool_field(
      "activerehashing",server.activerehashing) {
    } config_set_bool_field(
      "stop-writes-on-bgsave-error",server.stop_writes_on_bgsave_err) {
    } config_set_bool_field(
      "tcp-keepalive",server.tcpkeepalive) {

    /* Numerical fields.
     * config_set_numerical_field(name,var,min,max) */
    } config_set_numerical_field(
      "maxmemory-samples",server.maxmemory_samples,1,LLONG_MAX) {
    } config_set_numerical_field(
      "timeout",server.maxidletime,0,LONG_MAX) {
    } config_set_numerical_field(
      "auto-aof-rewrite-percentage",server.aof_rewrite_perc,0,LLONG_MAX){
    } config_set_numerical_field(
      "auto-aof-rewrite-min-size",server.aof_rewrite_min_size,0,LLONG_MAX) {
    } config_set_numerical_field(
      "hash-max-ziplist-entries",server.hash_max_ziplist_entries,0,LLONG_MAX) {
    } config_set_numerical_field(
      "hash-max-ziplist-value",server.hash_max_ziplist_value,0,LLONG_MAX) {
    } config_set_numerical_field(
      "list-max-ziplist-size",server.list_max_ziplist_size,0,LLONG_MAX) {
    } config_set_numerical_field(
      "list-compress-depth",server.list_compress_depth,0,LLONG_MAX) {
    } config_set_numerical_field(
      "set-max-intset-entries",server.set_max_intset_entries,0,LLONG_MAX) {
    } config_set_numerical_field(
      "zset-max-ziplist-entries",server.zset_max_ziplist_entries,0,LLONG_MAX) {
    } config_set_numerical_field(
      "zset-max-ziplist-value",server.zset_max_ziplist_value,0,LLONG_MAX) {
    } config_set_numerical_field(
      "hll-sparse-max-bytes",server.hll_sparse_max_bytes,0,LLONG_MAX) {
    } config_set_numerical_field(
      "lua-time-limit",server.lua_time_limit,0,LLONG_MAX) {
    } config_set_numerical_field(
      "slowlog-log-slower-than",server.slowlog_log_slower_than,0,LLONG_MAX) {
    } config_set_numerical_field(
      "latency-monitor-threshold",server.latency_monitor_threshold,0,LLONG_MAX){
    } config_set_numerical_field(
      "repl-ping-slave-period",server.repl_ping_slave_period,1,LLONG_MAX) {
    } config_set_numerical_field(
      "repl-timeout",server.repl_timeout,1,LLONG_MAX) {
    } config_set_numerical_field(
      "repl-backlog-ttl",server.repl_backlog_time_limit,0,LLONG_MAX) {
    } config_set_numerical_field(
      "repl-diskless-sync-delay",server.repl_diskless_sync_delay,0,LLONG_MAX) {
    } config_set_numerical_field(
      "slave-priority",server.slave_priority,0,LLONG_MAX) {
    } config_set_numerical_field(
      "min-slaves-to-write",server.repl_min_slaves_to_write,0,LLONG_MAX) {
        refreshGoodSlavesCount();
    } config_set_numerical_field(
      "min-slaves-max-lag",server.repl_min_slaves_max_lag,0,LLONG_MAX) {
        refreshGoodSlavesCount();
    } config_set_numerical_field(
      "cluster-node-timeout",server.cluster_node_timeout,0,LLONG_MAX) {
    } config_set_numerical_field(
      "cluster-migration-barrier",server.cluster_migration_barrier,0,LLONG_MAX){
    } config_set_numerical_field(
      "cluster-slave-validity-factor",server.cluster_slave_validity_factor,0,LLONG_MAX) {
    } config_set_numerical_field(
      "hz",server.hz,0,LLONG_MAX) {
        /* Hz is more an hint from the user, so we accept values out of range
         * but cap them to reasonable values. */
        if (server.hz < REDIS_MIN_HZ) server.hz = REDIS_MIN_HZ;
        if (server.hz > REDIS_MAX_HZ) server.hz = REDIS_MAX_HZ;
    }

    /* Everyhing else is an error... */
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
