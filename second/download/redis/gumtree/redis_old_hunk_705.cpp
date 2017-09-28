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
      "protected-mode",server.protected_mode) {
    } config_set_bool_field(
      "stop-writes-on-bgsave-error",server.stop_writes_on_bgsave_err) {
    } config_set_bool_field(
      "no-appendfsync-on-rewrite",server.aof_no_fsync_on_rewrite) {

    /* Numerical fields.
     * config_set_numerical_field(name,var,min,max) */
    } config_set_numerical_field(
      "tcp-keepalive",server.tcpkeepalive,0,LLONG_MAX) {
    } config_set_numerical_field(
      "maxmemory-samples",server.maxmemory_samples,1,LLONG_MAX) {
    } config_set_numerical_field(
      "timeout",server.maxidletime,0,LONG_MAX) {
    } config_set_numerical_field(
      "auto-aof-rewrite-percentage",server.aof_rewrite_perc,0,LLONG_MAX){
    } config_set_numerical_field(
      "hash-max-ziplist-entries",server.hash_max_ziplist_entries,0,LLONG_MAX) {
    } config_set_numerical_field(
      "hash-max-ziplist-value",server.hash_max_ziplist_value,0,LLONG_MAX) {
    } config_set_numerical_field(
      "list-max-ziplist-size",server.list_max_ziplist_size,INT_MIN,INT_MAX) {
    } config_set_numerical_field(
