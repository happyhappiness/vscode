ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
	"access to %s failed, reason: user %s not allowed access",
	r->uri, user);