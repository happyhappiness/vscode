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

++ apache_1.3.2/src/modules/standard/mod_auth_db.c	1998-09-19 20:12:36.000000000 +0800

