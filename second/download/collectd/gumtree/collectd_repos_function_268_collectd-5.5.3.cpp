static int varnish_monitor (void *priv, const struct VSC_point * const pt) /* {{{ */
{
	uint64_t val;
	const user_config_t *conf;
	const char *class;
	const char *name;

	if (pt == NULL)
		return (0);

	conf = priv;

#if HAVE_VARNISH_V4
	class = pt->section->fantom->type;
	name  = pt->desc->name;

	if (strcmp(class, "MAIN") != 0)
		return (0);

#elif HAVE_VARNISH_V3
	class = pt->class;
	name  = pt->name;

	if (strcmp(class, "") != 0)
		return (0);
#endif

	val = *(const volatile uint64_t*) pt->ptr;

	if (conf->collect_cache)
	{
		if (strcmp(name, "cache_hit") == 0)
			return varnish_submit_derive (conf->instance, "cache", "cache_result", "hit",     val);
		else if (strcmp(name, "cache_miss") == 0)
			return varnish_submit_derive (conf->instance, "cache", "cache_result", "miss",    val);
		else if (strcmp(name, "cache_hitpass") == 0)
			return varnish_submit_derive (conf->instance, "cache", "cache_result", "hitpass", val);
	}

	if (conf->collect_connections)
	{
		if (strcmp(name, "client_conn") == 0)
			return varnish_submit_derive (conf->instance, "connections", "connections", "accepted", val);
		else if (strcmp(name, "client_drop") == 0)
			return varnish_submit_derive (conf->instance, "connections", "connections", "dropped" , val);
		else if (strcmp(name, "client_req") == 0)
			return varnish_submit_derive (conf->instance, "connections", "connections", "received", val);
	}

#ifdef HAVE_VARNISH_V3
	if (conf->collect_dirdns)
	{
		if (strcmp(name, "dir_dns_lookups") == 0)
			return varnish_submit_derive (conf->instance, "dirdns", "cache_operation", "lookups",    val);
		else if (strcmp(name, "dir_dns_failed") == 0)
			return varnish_submit_derive (conf->instance, "dirdns", "cache_result",    "failed",     val);
		else if (strcmp(name, "dir_dns_hit") == 0)
			return varnish_submit_derive (conf->instance, "dirdns", "cache_result",    "hits",       val);
		else if (strcmp(name, "dir_dns_cache_full") == 0)
			return varnish_submit_derive (conf->instance, "dirdns", "cache_result",    "cache_full", val);
	}
#endif

	if (conf->collect_esi)
	{
		if (strcmp(name, "esi_errors") == 0)
			return varnish_submit_derive (conf->instance, "esi", "total_operations", "error",   val);
		else if (strcmp(name, "esi_parse") == 0)
			return varnish_submit_derive (conf->instance, "esi", "total_operations", "parsed",  val);
		else if (strcmp(name, "esi_warnings") == 0)
			return varnish_submit_derive (conf->instance, "esi", "total_operations", "warning", val);
	}

	if (conf->collect_backend)
	{
		if (strcmp(name, "backend_conn") == 0)
			return varnish_submit_derive (conf->instance, "backend", "connections", "success",       val);
		else if (strcmp(name, "backend_unhealthy") == 0)
			return varnish_submit_derive (conf->instance, "backend", "connections", "not-attempted", val);
		else if (strcmp(name, "backend_busy") == 0)
			return varnish_submit_derive (conf->instance, "backend", "connections", "too-many",      val);
		else if (strcmp(name, "backend_fail") == 0)
			return varnish_submit_derive (conf->instance, "backend", "connections", "failures",      val);
		else if (strcmp(name, "backend_reuse") == 0)
			return varnish_submit_derive (conf->instance, "backend", "connections", "reuses",        val);
		else if (strcmp(name, "backend_toolate") == 0)
			return varnish_submit_derive (conf->instance, "backend", "connections", "was-closed",    val);
		else if (strcmp(name, "backend_recycle") == 0)
			return varnish_submit_derive (conf->instance, "backend", "connections", "recycled",      val);
		else if (strcmp(name, "backend_unused") == 0)
			return varnish_submit_derive (conf->instance, "backend", "connections", "unused",        val);
		else if (strcmp(name, "backend_retry") == 0)
			return varnish_submit_derive (conf->instance, "backend", "connections", "retries",       val);
		else if (strcmp(name, "backend_req") == 0)
			return varnish_submit_derive (conf->instance, "backend", "http_requests", "requests",    val);
		else if (strcmp(name, "n_backend") == 0)
			return varnish_submit_gauge  (conf->instance, "backend", "backends", "n_backends",       val);
	}

	if (conf->collect_fetch)
	{
		if (strcmp(name, "fetch_head") == 0)
			return varnish_submit_derive (conf->instance, "fetch", "http_requests", "head",        val);
		else if (strcmp(name, "fetch_length") == 0)
			return varnish_submit_derive (conf->instance, "fetch", "http_requests", "length",      val);
		else if (strcmp(name, "fetch_chunked") == 0)
			return varnish_submit_derive (conf->instance, "fetch", "http_requests", "chunked",     val);
		else if (strcmp(name, "fetch_eof") == 0)
			return varnish_submit_derive (conf->instance, "fetch", "http_requests", "eof",         val);
		else if (strcmp(name, "fetch_bad") == 0)
			return varnish_submit_derive (conf->instance, "fetch", "http_requests", "bad_headers", val);
		else if (strcmp(name, "fetch_close") == 0)
			return varnish_submit_derive (conf->instance, "fetch", "http_requests", "close",       val);
		else if (strcmp(name, "fetch_oldhttp") == 0)
			return varnish_submit_derive (conf->instance, "fetch", "http_requests", "oldhttp",     val);
		else if (strcmp(name, "fetch_zero") == 0)
			return varnish_submit_derive (conf->instance, "fetch", "http_requests", "zero",        val);
		else if (strcmp(name, "fetch_failed") == 0)
			return varnish_submit_derive (conf->instance, "fetch", "http_requests", "failed",      val);
		else if (strcmp(name, "fetch_1xx") == 0)
			return varnish_submit_derive (conf->instance, "fetch", "http_requests", "no_body_1xx", val);
		else if (strcmp(name, "fetch_204") == 0)
			return varnish_submit_derive (conf->instance, "fetch", "http_requests", "no_body_204", val);
		else if (strcmp(name, "fetch_304") == 0)
			return varnish_submit_derive (conf->instance, "fetch", "http_requests", "no_body_304", val);
	}

	if (conf->collect_hcb)
	{
		if (strcmp(name, "hcb_nolock") == 0)
			return varnish_submit_derive (conf->instance, "hcb", "cache_operation", "lookup_nolock", val);
		else if (strcmp(name, "hcb_lock") == 0)
			return varnish_submit_derive (conf->instance, "hcb", "cache_operation", "lookup_lock",   val);
		else if (strcmp(name, "hcb_insert") == 0)
			return varnish_submit_derive (conf->instance, "hcb", "cache_operation", "insert",        val);
	}

	if (conf->collect_objects)
	{
		if (strcmp(name, "n_expired") == 0)
			return varnish_submit_derive (conf->instance, "objects", "total_objects", "expired",            val);
		else if (strcmp(name, "n_lru_nuked") == 0)
			return varnish_submit_derive (conf->instance, "objects", "total_objects", "lru_nuked",          val);
		else if (strcmp(name, "n_lru_saved") == 0)
			return varnish_submit_derive (conf->instance, "objects", "total_objects", "lru_saved",          val);
		else if (strcmp(name, "n_lru_moved") == 0)
			return varnish_submit_derive (conf->instance, "objects", "total_objects", "lru_moved",          val);
		else if (strcmp(name, "n_deathrow") == 0)
			return varnish_submit_derive (conf->instance, "objects", "total_objects", "deathrow",           val);
		else if (strcmp(name, "losthdr") == 0)
			return varnish_submit_derive (conf->instance, "objects", "total_objects", "header_overflow",    val);
		else if (strcmp(name, "n_obj_purged") == 0)
			return varnish_submit_derive (conf->instance, "objects", "total_objects", "purged",             val);
		else if (strcmp(name, "n_objsendfile") == 0)
			return varnish_submit_derive (conf->instance, "objects", "total_objects", "sent_sendfile",      val);
		else if (strcmp(name, "n_objwrite") == 0)
			return varnish_submit_derive (conf->instance, "objects", "total_objects", "sent_write",         val);
		else if (strcmp(name, "n_objoverflow") == 0)
			return varnish_submit_derive (conf->instance, "objects", "total_objects", "workspace_overflow", val);
	}

#if HAVE_VARNISH_V3
	if (conf->collect_ban)
	{
		if (strcmp(name, "n_ban") == 0)
			return varnish_submit_derive (conf->instance, "ban", "total_operations", "total",          val);
		else if (strcmp(name, "n_ban_add") == 0)
			return varnish_submit_derive (conf->instance, "ban", "total_operations", "added",          val);
		else if (strcmp(name, "n_ban_retire") == 0)
			return varnish_submit_derive (conf->instance, "ban", "total_operations", "deleted",        val);
		else if (strcmp(name, "n_ban_obj_test") == 0)
			return varnish_submit_derive (conf->instance, "ban", "total_operations", "objects_tested", val);
		else if (strcmp(name, "n_ban_re_test") == 0)
			return varnish_submit_derive (conf->instance, "ban", "total_operations", "regexps_tested", val);
		else if (strcmp(name, "n_ban_dups") == 0)
			return varnish_submit_derive (conf->instance, "ban", "total_operations", "duplicate",      val);
	}
#endif
#if HAVE_VARNISH_V4
	if (conf->collect_ban)
	{
		if (strcmp(name, "bans") == 0)
			return varnish_submit_derive (conf->instance, "ban", "total_operations", "total",     val);
		else if (strcmp(name, "bans_added") == 0)
			return varnish_submit_derive (conf->instance, "ban", "total_operations", "added",     val);
		else if (strcmp(name, "bans_obj") == 0)
			return varnish_submit_derive (conf->instance, "ban", "total_operations", "obj",       val);
		else if (strcmp(name, "bans_req") == 0)
			return varnish_submit_derive (conf->instance, "ban", "total_operations", "req",       val);
		else if (strcmp(name, "bans_completed") == 0)
			return varnish_submit_derive (conf->instance, "ban", "total_operations", "completed", val);
		else if (strcmp(name, "bans_deleted") == 0)
			return varnish_submit_derive (conf->instance, "ban", "total_operations", "deleted",   val);
		else if (strcmp(name, "bans_tested") == 0)
			return varnish_submit_derive (conf->instance, "ban", "total_operations", "tested",    val);
		else if (strcmp(name, "bans_dups") == 0)
			return varnish_submit_derive (conf->instance, "ban", "total_operations", "duplicate", val);
	}
#endif

	if (conf->collect_session)
	{
		if (strcmp(name, "sess_closed") == 0)
			return varnish_submit_derive (conf->instance, "session", "total_operations", "closed",    val);
		else if (strcmp(name, "sess_pipeline") == 0)
			return varnish_submit_derive (conf->instance, "session", "total_operations", "pipeline",  val);
		else if (strcmp(name, "sess_readahead") == 0)
			return varnish_submit_derive (conf->instance, "session", "total_operations", "readahead", val);
		else if (strcmp(name, "sess_conn") == 0)
			return varnish_submit_derive (conf->instance, "session", "total_operations", "accepted",  val);
		else if (strcmp(name, "sess_drop") == 0)
			return varnish_submit_derive (conf->instance, "session", "total_operations", "dropped",   val);
		else if (strcmp(name, "sess_fail") == 0)
			return varnish_submit_derive (conf->instance, "session", "total_operations", "failed",    val);
		else if (strcmp(name, "sess_pipe_overflow") == 0)
			return varnish_submit_derive (conf->instance, "session", "total_operations", "overflow",  val);
		else if (strcmp(name, "sess_queued") == 0)
			return varnish_submit_derive (conf->instance, "session", "total_operations", "queued",    val);
		else if (strcmp(name, "sess_linger") == 0)
			return varnish_submit_derive (conf->instance, "session", "total_operations", "linger",    val);
		else if (strcmp(name, "sess_herd") == 0)
			return varnish_submit_derive (conf->instance, "session", "total_operations", "herd",      val);
	}

	if (conf->collect_shm)
	{
		if (strcmp(name, "shm_records") == 0)
			return varnish_submit_derive (conf->instance, "shm", "total_operations", "records",    val);
		else if (strcmp(name, "shm_writes") == 0)
			return varnish_submit_derive (conf->instance, "shm", "total_operations", "writes",     val);
		else if (strcmp(name, "shm_flushes") == 0)
			return varnish_submit_derive (conf->instance, "shm", "total_operations", "flushes",    val);
		else if (strcmp(name, "shm_cont") == 0)
			return varnish_submit_derive (conf->instance, "shm", "total_operations", "contention", val);
		else if (strcmp(name, "shm_cycles") == 0)
			return varnish_submit_derive (conf->instance, "shm", "total_operations", "cycles",     val);
	}

	if (conf->collect_sms)
	{
		if (strcmp(name, "sms_nreq") == 0)
			return varnish_submit_derive (conf->instance, "sms", "total_requests", "allocator", val);
		else if (strcmp(name, "sms_nobj") == 0)
			return varnish_submit_gauge (conf->instance,  "sms", "requests", "outstanding",     val);
		else if (strcmp(name, "sms_nbytes") == 0)
			return varnish_submit_gauge (conf->instance,  "sms", "bytes", "outstanding",        val);
		else if (strcmp(name, "sms_balloc") == 0)
			return varnish_submit_derive (conf->instance,  "sms", "total_bytes", "allocated",   val);
		else if (strcmp(name, "sms_bfree") == 0)
			return varnish_submit_derive (conf->instance,  "sms", "total_bytes", "free",        val);
	}

	if (conf->collect_struct)
	{
		if (strcmp(name, "n_sess_mem") == 0)
			return varnish_submit_gauge (conf->instance, "struct", "current_sessions", "sess_mem",  val);
		else if (strcmp(name, "n_sess") == 0)
			return varnish_submit_gauge (conf->instance, "struct", "current_sessions", "sess",      val);
		else if (strcmp(name, "n_object") == 0)
			return varnish_submit_gauge (conf->instance, "struct", "objects", "object",             val);
		else if (strcmp(name, "n_vampireobject") == 0)
			return varnish_submit_gauge (conf->instance, "struct", "objects", "vampireobject",      val);
		else if (strcmp(name, "n_objectcore") == 0)
			return varnish_submit_gauge (conf->instance, "struct", "objects", "objectcore",         val);
		else if (strcmp(name, "n_waitinglist") == 0)
			return varnish_submit_gauge (conf->instance, "struct", "objects", "waitinglist",        val);
		else if (strcmp(name, "n_objecthead") == 0)
			return varnish_submit_gauge (conf->instance, "struct", "objects", "objecthead",         val);
		else if (strcmp(name, "n_smf") == 0)
			return varnish_submit_gauge (conf->instance, "struct", "objects", "smf",                val);
		else if (strcmp(name, "n_smf_frag") == 0)
			return varnish_submit_gauge (conf->instance, "struct", "objects", "smf_frag",           val);
		else if (strcmp(name, "n_smf_large") == 0)
			return varnish_submit_gauge (conf->instance, "struct", "objects", "smf_large",          val);
		else if (strcmp(name, "n_vbe_conn") == 0)
			return varnish_submit_gauge (conf->instance, "struct", "objects", "vbe_conn",           val);
	}

	if (conf->collect_totals)
	{
		if (strcmp(name, "s_sess") == 0)
			return varnish_submit_derive (conf->instance, "totals", "total_sessions", "sessions",  val);
		else if (strcmp(name, "s_req") == 0)
			return varnish_submit_derive (conf->instance, "totals", "total_requests", "requests",  val);
		else if (strcmp(name, "s_pipe") == 0)
			return varnish_submit_derive (conf->instance, "totals", "total_operations", "pipe",    val);
		else if (strcmp(name, "s_pass") == 0)
			return varnish_submit_derive (conf->instance, "totals", "total_operations", "pass",    val);
		else if (strcmp(name, "s_fetch") == 0)
			return varnish_submit_derive (conf->instance, "totals", "total_operations", "fetches", val);
		else if (strcmp(name, "s_synth") == 0)
			return varnish_submit_derive (conf->instance, "totals", "total_bytes", "synth",        val);
		else if (strcmp(name, "s_req_hdrbytes") == 0)
			return varnish_submit_derive (conf->instance, "totals", "total_bytes", "req_header",   val);
		else if (strcmp(name, "s_req_bodybytes") == 0)
			return varnish_submit_derive (conf->instance, "totals", "total_bytes", "req_body",     val);
		else if (strcmp(name, "s_resp_hdrbytes") == 0)
			return varnish_submit_derive (conf->instance, "totals", "total_bytes", "resp_header",  val);
		else if (strcmp(name, "s_resp_bodybytes") == 0)
			return varnish_submit_derive (conf->instance, "totals", "total_bytes", "resp_body",    val);
		else if (strcmp(name, "s_pipe_hdrbytes") == 0)
			return varnish_submit_derive (conf->instance, "totals", "total_bytes", "pipe_header",  val);
		else if (strcmp(name, "s_pipe_in") == 0)
			return varnish_submit_derive (conf->instance, "totals", "total_bytes", "pipe_in",      val);
		else if (strcmp(name, "s_pipe_out") == 0)
			return varnish_submit_derive (conf->instance, "totals", "total_bytes", "pipe_out",     val);
		else if (strcmp(name, "n_purges") == 0)
			return varnish_submit_derive (conf->instance, "totals", "total_operations", "purges",  val);
		else if (strcmp(name, "s_hdrbytes") == 0)
			return varnish_submit_derive (conf->instance, "totals", "total_bytes", "header-bytes", val);
		else if (strcmp(name, "s_bodybytes") == 0)
			return varnish_submit_derive (conf->instance, "totals", "total_bytes", "body-bytes",   val);
		else if (strcmp(name, "n_gzip") == 0)
			return varnish_submit_derive (conf->instance, "totals", "total_operations", "gzip",    val);
		else if (strcmp(name, "n_gunzip") == 0)
			return varnish_submit_derive (conf->instance, "totals", "total_operations", "gunzip",  val);
	}

	if (conf->collect_uptime)
	{
		if (strcmp(name, "uptime") == 0)
			return varnish_submit_gauge (conf->instance, "uptime", "uptime", "client_uptime", val);
	}

	if (conf->collect_vcl)
	{
		if (strcmp(name, "n_vcl") == 0)
			return varnish_submit_gauge (conf->instance, "vcl", "vcl", "total_vcl",     val);
		else if (strcmp(name, "n_vcl_avail") == 0)
			return varnish_submit_gauge (conf->instance, "vcl", "vcl", "avail_vcl",     val);
		else if (strcmp(name, "n_vcl_discard") == 0)
			return varnish_submit_gauge (conf->instance, "vcl", "vcl", "discarded_vcl", val);
		else if (strcmp(name, "vmods") == 0)
			return varnish_submit_gauge (conf->instance, "vcl", "objects", "vmod",      val);
	}

	if (conf->collect_workers)
	{
		if (strcmp(name, "threads") == 0)
			return varnish_submit_gauge (conf->instance, "workers", "threads", "worker",               val);
		else if (strcmp(name, "threads_created") == 0)
			return varnish_submit_derive (conf->instance, "workers", "total_threads", "created",       val);
		else if (strcmp(name, "threads_failed") == 0)
			return varnish_submit_derive (conf->instance, "workers", "total_threads", "failed",        val);
		else if (strcmp(name, "threads_limited") == 0)
			return varnish_submit_derive (conf->instance, "workers", "total_threads", "limited",       val);
		else if (strcmp(name, "threads_destroyed") == 0)
			return varnish_submit_derive (conf->instance, "workers", "total_threads", "dropped",       val);
		else if (strcmp(name, "thread_queue_len") == 0)
			return varnish_submit_derive (conf->instance, "workers", "queue_length",  "threads",       val);
		else if (strcmp(name, "n_wrk") == 0)
			return varnish_submit_gauge (conf->instance, "workers", "threads", "worker",               val);
		else if (strcmp(name, "n_wrk_create") == 0)
			return varnish_submit_derive (conf->instance, "workers", "total_threads", "created",       val);
		else if (strcmp(name, "n_wrk_failed") == 0)
			return varnish_submit_derive (conf->instance, "workers", "total_threads", "failed",        val);
		else if (strcmp(name, "n_wrk_max") == 0)
			return varnish_submit_derive (conf->instance, "workers", "total_threads", "limited",       val);
		else if (strcmp(name, "n_wrk_drop") == 0)
			return varnish_submit_derive (conf->instance, "workers", "total_threads", "dropped",       val);
		else if (strcmp(name, "n_wrk_queue") == 0)
			return varnish_submit_derive (conf->instance, "workers", "total_requests", "queued",       val);
		else if (strcmp(name, "n_wrk_overflow") == 0)
			return varnish_submit_derive (conf->instance, "workers", "total_requests", "overflowed",   val);
		else if (strcmp(name, "n_wrk_queued") == 0)
			return varnish_submit_derive (conf->instance, "workers", "total_requests", "queued",       val);
		else if (strcmp(name, "n_wrk_lqueue") == 0)
			return varnish_submit_derive (conf->instance, "workers", "total_requests", "queue_length", val);
	}

#if HAVE_VARNISH_V4
	if (conf->collect_vsm)
	{
		if (strcmp(name, "vsm_free") == 0)
			return varnish_submit_gauge (conf->instance, "vsm", "bytes", "free",              val);
		else if (strcmp(name, "vsm_used") == 0)
			return varnish_submit_gauge (conf->instance, "vsm", "bytes", "used",              val);
		else if (strcmp(name, "vsm_cooling") == 0)
			return varnish_submit_gauge (conf->instance, "vsm", "bytes", "cooling",           val);
		else if (strcmp(name, "vsm_overflow") == 0)
			return varnish_submit_gauge (conf->instance, "vsm", "bytes", "overflow",          val);
		else if (strcmp(name, "vsm_overflowed") == 0)
			return varnish_submit_derive (conf->instance, "vsm", "total_bytes", "overflowed", val);
	}
#endif

	return (0);

}