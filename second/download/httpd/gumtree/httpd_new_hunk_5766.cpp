    if (!method_restricted)
	return OK;

    if (!(sec->auth_authoritative))
	return DECLINED;

    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
	"access to %s failed, reason: user %s not allowed access",
	r->uri, user);
	
    ap_note_basic_auth_failure(r);
    return AUTH_REQUIRED;
}

module MODULE_VAR_EXPORT auth_module =
