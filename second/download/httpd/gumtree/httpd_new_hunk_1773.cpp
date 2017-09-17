  (void *)XtOffsetOf (server_rec, srm_confname), RSRC_CONF, TAKE1,
  "The filename of the resource config file" },
{ "ServerAlias", set_server_alias, NULL, RSRC_CONF, RAW_ARGS,
  "A name or names alternately used to access the server" },
{ "ServerPath", set_serverpath, NULL, RSRC_CONF, TAKE1,
  "The pathname the server can be reached at" },
{ "Timeout", set_timeout, NULL, RSRC_CONF, TAKE1, "Timeout duration (sec)" },
{ "KeepAliveTimeout", set_keep_alive_timeout, NULL, RSRC_CONF, TAKE1,
  "Keep-Alive timeout duration (sec)"},
{ "MaxKeepAliveRequests", set_keep_alive_max, NULL, RSRC_CONF, TAKE1,
  "Maximum number of Keep-Alive requests per connection, or 0 for infinite" },
{ "KeepAlive", set_keep_alive, NULL, RSRC_CONF, TAKE1,
  "Whether persistent connections should be On or Off" },
{ "IdentityCheck", set_idcheck, NULL, RSRC_CONF|ACCESS_CONF, FLAG,
  "Enable identd (RFC 1413) user lookups - SLOW" },
{ "ContentDigest", set_content_md5, NULL, RSRC_CONF|ACCESS_CONF|OR_AUTHCFG,
  FLAG, "whether or not to send a Content-MD5 header with each request" },
{ "UseCanonicalName", set_use_canonical_name, NULL,
  RSRC_CONF|ACCESS_CONF|OR_AUTHCFG, FLAG,
  "Whether or not to always use the canonical ServerName : Port when "
  "constructing URLs" },
{ "StartServers", set_daemons_to_start, NULL, RSRC_CONF, TAKE1,
  "Number of child processes launched at server startup" },
{ "MinSpareServers", set_min_free_servers, NULL, RSRC_CONF, TAKE1,
  "Minimum number of idle children, to handle request spikes" },
{ "MaxSpareServers", set_max_free_servers, NULL, RSRC_CONF, TAKE1,
  "Maximum number of idle children" },
{ "MaxServers", set_max_free_servers, NULL, RSRC_CONF, TAKE1,
  "Deprecated equivalent to MaxSpareServers" },
{ "ServersSafetyLimit", set_server_limit, NULL, RSRC_CONF, TAKE1,
  "Deprecated equivalent to MaxClients" },
{ "MaxClients", set_server_limit, NULL, RSRC_CONF, TAKE1,
  "Maximum number of children alive at the same time" },
{ "MaxRequestsPerChild", set_max_requests, NULL, RSRC_CONF, TAKE1,
  "Maximum number of requests a particular child serves before dying." },
{ "RLimitCPU",
#ifdef RLIMIT_CPU
  set_limit_cpu, (void*)XtOffsetOf(core_dir_config, limit_cpu),
#else
  no_set_limit, NULL,
#endif
  OR_ALL, TAKE12, "Soft/hard limits for max CPU usage in seconds" },
{ "RLimitMEM",
#if defined (RLIMIT_DATA) || defined (RLIMIT_VMEM) || defined (RLIMIT_AS)
  set_limit_mem, (void*)XtOffsetOf(core_dir_config, limit_mem),
#else
  no_set_limit, NULL,
#endif
  OR_ALL, TAKE12, "Soft/hard limits for max memory usage per process" },
{ "RLimitNPROC",
#ifdef RLIMIT_NPROC
  set_limit_nproc, (void*)XtOffsetOf(core_dir_config, limit_nproc),
#else
  no_set_limit, NULL,
#endif
   OR_ALL, TAKE12, "soft/hard limits for max number of processes per uid" },
{ "BindAddress", set_bind_address, NULL, RSRC_CONF, TAKE1,
  "'*', a numeric IP address, or the name of a host with a unique IP address"},
{ "Listen", set_listener, NULL, RSRC_CONF, TAKE1,
  "A port number or a numeric IP address and a port number"},
{ "SendBufferSize", set_send_buffer_size, NULL, RSRC_CONF, TAKE1,
  "Send buffer size in bytes"},
{ "AddModule", add_module_command, NULL, RSRC_CONF, ITERATE,
  "The name of a module" },
{ "ClearModuleList", clear_module_list_command, NULL, RSRC_CONF, NO_ARGS, 
  NULL },
{ "ThreadsPerChild", set_threads, NULL, RSRC_CONF, TAKE1,
  "Number of threads a child creates" },
{ "ExcessRequestsPerChild", set_excess_requests, NULL, RSRC_CONF, TAKE1,
  "Maximum number of requests a particular child serves after it is ready "
  "to die." },
{ "ListenBacklog", set_listenbacklog, NULL, RSRC_CONF, TAKE1,
  "Maximum length of the queue of pending connections, as used by listen(2)" },
{ "CoreDumpDirectory", set_coredumpdir, NULL, RSRC_CONF, TAKE1,
  "The location of the directory Apache changes to before dumping core" },
{ "Include", include_config, NULL, RSRC_CONF, TAKE1,
  "Name of the config file to be included" },
{ "LogLevel", set_loglevel, NULL, RSRC_CONF, TAKE1,
  "Level of verbosity in error logging" },
{ "NameVirtualHost", ap_set_name_virtual_host, NULL, RSRC_CONF, TAKE1,
  "A numeric IP address:port, or the name of a host" },
#ifdef _OSD_POSIX
{ "BS2000AuthFile", set_bs2000_authfile, NULL, RSRC_CONF, TAKE1,
  "Name of server User's bs2000 logon password file (read-protected)" },
#endif
{ "ServerTokens", set_serv_tokens, NULL, RSRC_CONF, TAKE1,
  "Determine tokens displayed in the Server: header - Min(imal), OS or Full" },
{ NULL },
};

/*****************************************************************
 *
 * Core handlers for various phases of server operation...
 */

static int core_translate(request_rec *r)
{
    void *sconf = r->server->module_config;
    core_server_config *conf = ap_get_module_config(sconf, &core_module);
  
    if (r->proxyreq) {
        return HTTP_FORBIDDEN;
    }
    if ((r->uri[0] != '/') && strcmp(r->uri, "*")) {
	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
		     "Invalid URI in request %s", r->the_request);
	return BAD_REQUEST;
    }
    
    if (r->server->path 
	&& !strncmp(r->uri, r->server->path, r->server->pathlen)
	&& (r->server->path[r->server->pathlen - 1] == '/'
	    || r->uri[r->server->pathlen] == '/'
	    || r->uri[r->server->pathlen] == '\0')) {
        r->filename = ap_pstrcat(r->pool, conf->ap_document_root,
				 (r->uri + r->server->pathlen), NULL);
    }
    else {
        r->filename = ap_pstrcat(r->pool, conf->ap_document_root, r->uri,
				 NULL);
    }

    return OK;
}

static int do_nothing(request_rec *r) { return OK; }

#ifdef USE_MMAP_FILES
struct mmap {
    void *mm;
    size_t length;
};

static void mmap_cleanup(void *mmv)
{
    struct mmap *mmd = mmv;

    munmap(mmd->mm, mmd->length);
}
#endif
