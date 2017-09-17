ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
	"access to %s failed for %s, reason: user %s not allowed access",
	r->uri,
	ap_get_remote_host(r->connection, r->per_dir_config, REMOTE_NAME),
	user);