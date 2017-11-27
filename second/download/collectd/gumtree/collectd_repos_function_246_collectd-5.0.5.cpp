static void varnish_monitor (const user_config_t *conf, struct varnish_stats *VSL_stats) /* {{{ */
{
	if (conf->collect_cache)
	{
		/* Cache hits */
		varnish_submit_derive (conf->instance, "cache", "cache_result", "hit",     VSL_stats->cache_hit);
		/* Cache misses */
		varnish_submit_derive (conf->instance, "cache", "cache_result", "miss",    VSL_stats->cache_miss);
		/* Cache hits for pass */
		varnish_submit_derive (conf->instance, "cache", "cache_result", "hitpass", VSL_stats->cache_hitpass);
	}

	if (conf->collect_connections)
	{
		/* Client connections accepted */
		varnish_submit_derive (conf->instance, "connections", "connections", "accepted", VSL_stats->client_conn);
		/* Connection dropped, no sess */
		varnish_submit_derive (conf->instance, "connections", "connections", "dropped" , VSL_stats->client_drop);
		/* Client requests received    */
		varnish_submit_derive (conf->instance, "connections", "connections", "received", VSL_stats->client_req);
	}

	if (conf->collect_esi)
	{
		/* Objects ESI parsed (unlock) */
		varnish_submit_derive (conf->instance, "esi", "total_operations", "parsed", VSL_stats->esi_parse);
		/* ESI parse errors (unlock)   */
		varnish_submit_derive (conf->instance, "esi", "total_operations", "error",  VSL_stats->esi_errors);
	}

	if (conf->collect_backend)
	{
		/* Backend conn. success       */
		varnish_submit_derive (conf->instance, "backend", "connections", "success"      , VSL_stats->backend_conn);
		/* Backend conn. not attempted */
		varnish_submit_derive (conf->instance, "backend", "connections", "not-attempted", VSL_stats->backend_unhealthy);
		/* Backend conn. too many      */
		varnish_submit_derive (conf->instance, "backend", "connections", "too-many"     , VSL_stats->backend_busy);
		/* Backend conn. failures      */
		varnish_submit_derive (conf->instance, "backend", "connections", "failures"     , VSL_stats->backend_fail);
		/* Backend conn. reuses        */
		varnish_submit_derive (conf->instance, "backend", "connections", "reuses"       , VSL_stats->backend_reuse);
		/* Backend conn. was closed    */
		varnish_submit_derive (conf->instance, "backend", "connections", "was-closed"   , VSL_stats->backend_toolate);
		/* Backend conn. recycles      */
		varnish_submit_derive (conf->instance, "backend", "connections", "recycled"     , VSL_stats->backend_recycle);
		/* Backend conn. unused        */
		varnish_submit_derive (conf->instance, "backend", "connections", "unused"       , VSL_stats->backend_unused);
	}

	if (conf->collect_fetch)
	{
		/* Fetch head                */
		varnish_submit_derive (conf->instance, "fetch", "http_requests", "head"       , VSL_stats->fetch_head);
		/* Fetch with length         */
		varnish_submit_derive (conf->instance, "fetch", "http_requests", "length"     , VSL_stats->fetch_length);
		/* Fetch chunked             */
		varnish_submit_derive (conf->instance, "fetch", "http_requests", "chunked"    , VSL_stats->fetch_chunked);
		/* Fetch EOF                 */
		varnish_submit_derive (conf->instance, "fetch", "http_requests", "eof"        , VSL_stats->fetch_eof);
		/* Fetch bad headers         */
		varnish_submit_derive (conf->instance, "fetch", "http_requests", "bad_headers", VSL_stats->fetch_bad);
		/* Fetch wanted close        */
		varnish_submit_derive (conf->instance, "fetch", "http_requests", "close"      , VSL_stats->fetch_close);
		/* Fetch pre HTTP/1.1 closed */
		varnish_submit_derive (conf->instance, "fetch", "http_requests", "oldhttp"    , VSL_stats->fetch_oldhttp);
		/* Fetch zero len            */
		varnish_submit_derive (conf->instance, "fetch", "http_requests", "zero"       , VSL_stats->fetch_zero);
		/* Fetch failed              */
		varnish_submit_derive (conf->instance, "fetch", "http_requests", "failed"     , VSL_stats->fetch_failed);
	}

	if (conf->collect_hcb)
	{
		/* HCB Lookups without lock */
		varnish_submit_derive (conf->instance, "hcb", "cache_operation", "lookup_nolock", VSL_stats->hcb_nolock);
		/* HCB Lookups with lock    */
		varnish_submit_derive (conf->instance, "hcb", "cache_operation", "lookup_lock",   VSL_stats->hcb_lock);
		/* HCB Inserts              */
		varnish_submit_derive (conf->instance, "hcb", "cache_operation", "insert",        VSL_stats->hcb_insert);
	}

	if (conf->collect_shm)
	{
		/* SHM records                 */
		varnish_submit_derive (conf->instance, "shm", "total_operations", "records"   , VSL_stats->shm_records);
		/* SHM writes                  */
		varnish_submit_derive (conf->instance, "shm", "total_operations", "writes"    , VSL_stats->shm_writes);
		/* SHM flushes due to overflow */
		varnish_submit_derive (conf->instance, "shm", "total_operations", "flushes"   , VSL_stats->shm_flushes);
		/* SHM MTX contention          */
		varnish_submit_derive (conf->instance, "shm", "total_operations", "contention", VSL_stats->shm_cont);
		/* SHM cycles through buffer   */
		varnish_submit_derive (conf->instance, "shm", "total_operations", "cycles"    , VSL_stats->shm_cycles);
	}

	if (conf->collect_sm)
	{
		/* allocator requests */
		varnish_submit_derive (conf->instance, "sm", "total_requests", "nreq",  VSL_stats->sm_nreq);
		/* outstanding allocations */
		varnish_submit_gauge (conf->instance,  "sm", "requests", "outstanding", VSL_stats->sm_nobj);
		/* bytes allocated */
		varnish_submit_derive (conf->instance,  "sm", "total_bytes", "allocated",      VSL_stats->sm_balloc);
		/* bytes free */
		varnish_submit_derive (conf->instance,  "sm", "total_bytes", "free",           VSL_stats->sm_bfree);
	}

	if (conf->collect_sma)
	{
		/* SMA allocator requests */
		varnish_submit_derive (conf->instance, "sma", "total_requests", "nreq",  VSL_stats->sma_nreq);
		/* SMA outstanding allocations */
		varnish_submit_gauge (conf->instance,  "sma", "requests", "outstanding", VSL_stats->sma_nobj);
		/* SMA outstanding bytes */
		varnish_submit_gauge (conf->instance,  "sma", "bytes", "outstanding",    VSL_stats->sma_nbytes);
		/* SMA bytes allocated */
		varnish_submit_derive (conf->instance,  "sma", "total_bytes", "allocated",      VSL_stats->sma_balloc);
		/* SMA bytes free */
		varnish_submit_derive (conf->instance,  "sma", "total_bytes", "free" ,          VSL_stats->sma_bfree);
	}

	if (conf->collect_sms)
	{
		/* SMS allocator requests */
		varnish_submit_derive (conf->instance, "sms", "total_requests", "allocator", VSL_stats->sms_nreq);
		/* SMS outstanding allocations */
		varnish_submit_gauge (conf->instance,  "sms", "requests", "outstanding",     VSL_stats->sms_nobj);
		/* SMS outstanding bytes */
		varnish_submit_gauge (conf->instance,  "sms", "bytes", "outstanding",        VSL_stats->sms_nbytes);
		/* SMS bytes allocated */
		varnish_submit_derive (conf->instance,  "sms", "total_bytes", "allocated",          VSL_stats->sms_balloc);
		/* SMS bytes freed */
		varnish_submit_derive (conf->instance,  "sms", "total_bytes", "free",               VSL_stats->sms_bfree);
	}

	if (conf->collect_totals)
	{
		/* Total Sessions */
		varnish_submit_derive (conf->instance, "totals", "total_sessions", "sessions",  VSL_stats->s_sess);
		/* Total Requests */
		varnish_submit_derive (conf->instance, "totals", "total_requests", "requests",  VSL_stats->s_req);
		/* Total pipe */
		varnish_submit_derive (conf->instance, "totals", "total_operations", "pipe",    VSL_stats->s_pipe);
		/* Total pass */
		varnish_submit_derive (conf->instance, "totals", "total_operations", "pass",    VSL_stats->s_pass);
		/* Total fetch */
		varnish_submit_derive (conf->instance, "totals", "total_operations", "fetches", VSL_stats->s_fetch);
		/* Total header bytes */
		varnish_submit_derive (conf->instance, "totals", "total_bytes", "header-bytes", VSL_stats->s_hdrbytes);
		/* Total body byte */
		varnish_submit_derive (conf->instance, "totals", "total_bytes", "body-bytes",   VSL_stats->s_bodybytes);
	}

	if (conf->collect_workers)
	{
		/* worker threads */
		varnish_submit_gauge (conf->instance, "workers", "threads", "worker",            VSL_stats->n_wrk);
		/* worker threads created */
		varnish_submit_derive (conf->instance, "workers", "total_threads", "created",     VSL_stats->n_wrk_create);
		/* worker threads not created */
		varnish_submit_derive (conf->instance, "workers", "total_threads", "failed",      VSL_stats->n_wrk_failed);
		/* worker threads limited */
		varnish_submit_derive (conf->instance, "workers", "total_threads", "limited",     VSL_stats->n_wrk_max);
		/* queued work requests */
		varnish_submit_derive (conf->instance, "workers", "total_requests", "queued",     VSL_stats->n_wrk_queue);
		/* overflowed work requests */
		varnish_submit_derive (conf->instance, "workers", "total_requests", "overflowed", VSL_stats->n_wrk_overflow);
		/* dropped work requests */
		varnish_submit_derive (conf->instance, "workers", "total_requests", "dropped",    VSL_stats->n_wrk_drop);
	}
}