static void varnish_monitor(const user_config_t *conf, /* {{{ */
                            const c_varnish_stats_t *stats) {
  if (conf->collect_cache) {
    /* Cache hits */
    varnish_submit_derive(conf->instance, "cache", "cache_result", "hit",
                          stats->cache_hit);
    /* Cache misses */
    varnish_submit_derive(conf->instance, "cache", "cache_result", "miss",
                          stats->cache_miss);
    /* Cache hits for pass */
    varnish_submit_derive(conf->instance, "cache", "cache_result", "hitpass",
                          stats->cache_hitpass);
  }

  if (conf->collect_connections) {
    /* Client connections accepted */
    varnish_submit_derive(conf->instance, "connections", "connections",
                          "accepted", stats->client_conn);
    /* Connection dropped, no sess */
    varnish_submit_derive(conf->instance, "connections", "connections",
                          "dropped", stats->client_drop);
    /* Client requests received    */
    varnish_submit_derive(conf->instance, "connections", "connections",
                          "received", stats->client_req);
  }

  if (conf->collect_esi) {
    /* ESI parse errors (unlock)   */
    varnish_submit_derive(conf->instance, "esi", "total_operations", "error",
                          stats->esi_errors);
    /* Objects ESI parsed (unlock) */
    varnish_submit_derive(conf->instance, "esi", "total_operations", "parsed",
                          stats->esi_parse);
  }

  if (conf->collect_backend) {
    /* Backend conn. success       */
    varnish_submit_derive(conf->instance, "backend", "connections", "success",
                          stats->backend_conn);
    /* Backend conn. not attempted */
    varnish_submit_derive(conf->instance, "backend", "connections",
                          "not-attempted", stats->backend_unhealthy);
    /* Backend conn. too many      */
    varnish_submit_derive(conf->instance, "backend", "connections", "too-many",
                          stats->backend_busy);
    /* Backend conn. failures      */
    varnish_submit_derive(conf->instance, "backend", "connections", "failures",
                          stats->backend_fail);
    /* Backend conn. reuses        */
    varnish_submit_derive(conf->instance, "backend", "connections", "reuses",
                          stats->backend_reuse);
    /* Backend conn. was closed    */
    varnish_submit_derive(conf->instance, "backend", "connections",
                          "was-closed", stats->backend_toolate);
    /* Backend conn. recycles      */
    varnish_submit_derive(conf->instance, "backend", "connections", "recycled",
                          stats->backend_recycle);
    /* Backend conn. unused        */
    varnish_submit_derive(conf->instance, "backend", "connections", "unused",
                          stats->backend_unused);
    /* Backend requests mades      */
    varnish_submit_derive(conf->instance, "backend", "http_requests",
                          "requests", stats->backend_req);
    /* N backends                  */
    varnish_submit_gauge(conf->instance, "backend", "backends", "n_backends",
                         stats->n_backend);
  }

  if (conf->collect_fetch) {
    /* Fetch head                */
    varnish_submit_derive(conf->instance, "fetch", "http_requests", "head",
                          stats->fetch_head);
    /* Fetch with length         */
    varnish_submit_derive(conf->instance, "fetch", "http_requests", "length",
                          stats->fetch_length);
    /* Fetch chunked             */
    varnish_submit_derive(conf->instance, "fetch", "http_requests", "chunked",
                          stats->fetch_chunked);
    /* Fetch EOF                 */
    varnish_submit_derive(conf->instance, "fetch", "http_requests", "eof",
                          stats->fetch_eof);
    /* Fetch bad headers         */
    varnish_submit_derive(conf->instance, "fetch", "http_requests",
                          "bad_headers", stats->fetch_bad);
    /* Fetch wanted close        */
    varnish_submit_derive(conf->instance, "fetch", "http_requests", "close",
                          stats->fetch_close);
    /* Fetch pre HTTP/1.1 closed */
    varnish_submit_derive(conf->instance, "fetch", "http_requests", "oldhttp",
                          stats->fetch_oldhttp);
    /* Fetch zero len            */
    varnish_submit_derive(conf->instance, "fetch", "http_requests", "zero",
                          stats->fetch_zero);
    /* Fetch failed              */
    varnish_submit_derive(conf->instance, "fetch", "http_requests", "failed",
                          stats->fetch_failed);
  }

  if (conf->collect_hcb) {
    /* HCB Lookups without lock */
    varnish_submit_derive(conf->instance, "hcb", "cache_operation",
                          "lookup_nolock", stats->hcb_nolock);
    /* HCB Lookups with lock    */
    varnish_submit_derive(conf->instance, "hcb", "cache_operation",
                          "lookup_lock", stats->hcb_lock);
    /* HCB Inserts              */
    varnish_submit_derive(conf->instance, "hcb", "cache_operation", "insert",
                          stats->hcb_insert);
  }

  if (conf->collect_objects) {
    /* N expired objects             */
    varnish_submit_derive(conf->instance, "objects", "total_objects", "expired",
                          stats->n_expired);
    /* N LRU nuked objects           */
    varnish_submit_derive(conf->instance, "objects", "total_objects",
                          "lru_nuked", stats->n_lru_nuked);
    /* N LRU saved objects           */
    varnish_submit_derive(conf->instance, "objects", "total_objects",
                          "lru_saved", stats->n_lru_saved);
    /* N LRU moved objects           */
    varnish_submit_derive(conf->instance, "objects", "total_objects",
                          "lru_moved", stats->n_lru_moved);
    /* N objects on deathrow         */
    varnish_submit_derive(conf->instance, "objects", "total_objects",
                          "deathrow", stats->n_deathrow);
    /* HTTP header overflows         */
    varnish_submit_derive(conf->instance, "objects", "total_objects",
                          "header_overflow", stats->losthdr);
    /* Objects sent with sendfile    */
    varnish_submit_derive(conf->instance, "objects", "total_objects",
                          "sent_sendfile", stats->n_objsendfile);
    /* Objects sent with write       */
    varnish_submit_derive(conf->instance, "objects", "total_objects",
                          "sent_write", stats->n_objwrite);
    /* Objects overflowing workspace */
    varnish_submit_derive(conf->instance, "objects", "total_objects",
                          "workspace_overflow", stats->n_objoverflow);
  }

  if (conf->collect_purge) {
    /* N total active purges      */
    varnish_submit_derive(conf->instance, "purge", "total_operations", "total",
                          stats->n_purge);
    /* N new purges added         */
    varnish_submit_derive(conf->instance, "purge", "total_operations", "added",
                          stats->n_purge_add);
    /* N old purges deleted       */
    varnish_submit_derive(conf->instance, "purge", "total_operations",
                          "deleted", stats->n_purge_retire);
    /* N objects tested           */
    varnish_submit_derive(conf->instance, "purge", "total_operations",
                          "objects_tested", stats->n_purge_obj_test);
    /* N regexps tested against   */
    varnish_submit_derive(conf->instance, "purge", "total_operations",
                          "regexps_tested", stats->n_purge_re_test);
    /* N duplicate purges removed */
    varnish_submit_derive(conf->instance, "purge", "total_operations",
                          "duplicate", stats->n_purge_dups);
  }

  if (conf->collect_session) {
    /* Session Closed     */
    varnish_submit_derive(conf->instance, "session", "total_operations",
                          "closed", stats->sess_closed);
    /* Session Pipeline   */
    varnish_submit_derive(conf->instance, "session", "total_operations",
                          "pipeline", stats->sess_pipeline);
    /* Session Read Ahead */
    varnish_submit_derive(conf->instance, "session", "total_operations",
                          "readahead", stats->sess_readahead);
    /* Session Linger     */
    varnish_submit_derive(conf->instance, "session", "total_operations",
                          "linger", stats->sess_linger);
    /* Session herd       */
    varnish_submit_derive(conf->instance, "session", "total_operations", "herd",
                          stats->sess_herd);
  }

  if (conf->collect_shm) {
    /* SHM records                 */
    varnish_submit_derive(conf->instance, "shm", "total_operations", "records",
                          stats->shm_records);
    /* SHM writes                  */
    varnish_submit_derive(conf->instance, "shm", "total_operations", "writes",
                          stats->shm_writes);
    /* SHM flushes due to overflow */
    varnish_submit_derive(conf->instance, "shm", "total_operations", "flushes",
                          stats->shm_flushes);
    /* SHM MTX contention          */
    varnish_submit_derive(conf->instance, "shm", "total_operations",
                          "contention", stats->shm_cont);
    /* SHM cycles through buffer   */
    varnish_submit_derive(conf->instance, "shm", "total_operations", "cycles",
                          stats->shm_cycles);
  }

  if (conf->collect_sm) {
    /* allocator requests */
    varnish_submit_derive(conf->instance, "sm", "total_requests", "nreq",
                          stats->sm_nreq);
    /* outstanding allocations */
    varnish_submit_gauge(conf->instance, "sm", "requests", "outstanding",
                         stats->sm_nobj);
    /* bytes allocated */
    varnish_submit_derive(conf->instance, "sm", "total_bytes", "allocated",
                          stats->sm_balloc);
    /* bytes free */
    varnish_submit_derive(conf->instance, "sm", "total_bytes", "free",
                          stats->sm_bfree);
  }

  if (conf->collect_sma) {
    /* SMA allocator requests */
    varnish_submit_derive(conf->instance, "sma", "total_requests", "nreq",
                          stats->sma_nreq);
    /* SMA outstanding allocations */
    varnish_submit_gauge(conf->instance, "sma", "requests", "outstanding",
                         stats->sma_nobj);
    /* SMA outstanding bytes */
    varnish_submit_gauge(conf->instance, "sma", "bytes", "outstanding",
                         stats->sma_nbytes);
    /* SMA bytes allocated */
    varnish_submit_derive(conf->instance, "sma", "total_bytes", "allocated",
                          stats->sma_balloc);
    /* SMA bytes free */
    varnish_submit_derive(conf->instance, "sma", "total_bytes", "free",
                          stats->sma_bfree);
  }

  if (conf->collect_sms) {
    /* SMS allocator requests */
    varnish_submit_derive(conf->instance, "sms", "total_requests", "allocator",
                          stats->sms_nreq);
    /* SMS outstanding allocations */
    varnish_submit_gauge(conf->instance, "sms", "requests", "outstanding",
                         stats->sms_nobj);
    /* SMS outstanding bytes */
    varnish_submit_gauge(conf->instance, "sms", "bytes", "outstanding",
                         stats->sms_nbytes);
    /* SMS bytes allocated */
    varnish_submit_derive(conf->instance, "sms", "total_bytes", "allocated",
                          stats->sms_balloc);
    /* SMS bytes freed */
    varnish_submit_derive(conf->instance, "sms", "total_bytes", "free",
                          stats->sms_bfree);
  }

  if (conf->collect_struct) {
    /* N struct sess_mem       */
    varnish_submit_gauge(conf->instance, "struct", "current_sessions",
                         "sess_mem", stats->n_sess_mem);
    /* N struct sess           */
    varnish_submit_gauge(conf->instance, "struct", "current_sessions", "sess",
                         stats->n_sess);
    /* N struct object         */
    varnish_submit_gauge(conf->instance, "struct", "objects", "object",
                         stats->n_object);
    /* N struct objecthead     */
    varnish_submit_gauge(conf->instance, "struct", "objects", "objecthead",
                         stats->n_objecthead);
    /* N struct smf            */
    varnish_submit_gauge(conf->instance, "struct", "objects", "smf",
                         stats->n_smf);
    /* N small free smf         */
    varnish_submit_gauge(conf->instance, "struct", "objects", "smf_frag",
                         stats->n_smf_frag);
    /* N large free smf         */
    varnish_submit_gauge(conf->instance, "struct", "objects", "smf_large",
                         stats->n_smf_large);
    /* N struct vbe_conn        */
    varnish_submit_gauge(conf->instance, "struct", "objects", "vbe_conn",
                         stats->n_vbe_conn);
  }

  if (conf->collect_totals) {
    /* Total Sessions */
    varnish_submit_derive(conf->instance, "totals", "total_sessions",
                          "sessions", stats->s_sess);
    /* Total Requests */
    varnish_submit_derive(conf->instance, "totals", "total_requests",
                          "requests", stats->s_req);
    /* Total pipe */
    varnish_submit_derive(conf->instance, "totals", "total_operations", "pipe",
                          stats->s_pipe);
    /* Total pass */
    varnish_submit_derive(conf->instance, "totals", "total_operations", "pass",
                          stats->s_pass);
    /* Total fetch */
    varnish_submit_derive(conf->instance, "totals", "total_operations",
                          "fetches", stats->s_fetch);
    /* Total header bytes */
    varnish_submit_derive(conf->instance, "totals", "total_bytes",
                          "header-bytes", stats->s_hdrbytes);
    /* Total body byte */
    varnish_submit_derive(conf->instance, "totals", "total_bytes", "body-bytes",
                          stats->s_bodybytes);
  }

  if (conf->collect_vcl) {
    /* N vcl total     */
    varnish_submit_gauge(conf->instance, "vcl", "vcl", "total_vcl",
                         stats->n_vcl);
    /* N vcl available */
    varnish_submit_gauge(conf->instance, "vcl", "vcl", "avail_vcl",
                         stats->n_vcl_avail);
    /* N vcl discarded */
    varnish_submit_gauge(conf->instance, "vcl", "vcl", "discarded_vcl",
                         stats->n_vcl_discard);
  }

  if (conf->collect_workers) {
    /* worker threads */
    varnish_submit_gauge(conf->instance, "workers", "threads", "worker",
                         stats->n_wrk);
    /* worker threads created */
    varnish_submit_derive(conf->instance, "workers", "total_threads", "created",
                          stats->n_wrk_create);
    /* worker threads not created */
    varnish_submit_derive(conf->instance, "workers", "total_threads", "failed",
                          stats->n_wrk_failed);
    /* worker threads limited */
    varnish_submit_derive(conf->instance, "workers", "total_threads", "limited",
                          stats->n_wrk_max);
    /* dropped work requests */
    varnish_submit_derive(conf->instance, "workers", "total_threads", "dropped",
                          stats->n_wrk_drop);
    /* queued work requests */
    varnish_submit_derive(conf->instance, "workers", "total_requests", "queued",
                          stats->n_wrk_queue);
    /* overflowed work requests */
    varnish_submit_derive(conf->instance, "workers", "total_requests",
                          "overflowed", stats->n_wrk_overflow);
  }

}