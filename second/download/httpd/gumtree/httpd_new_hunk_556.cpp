    if (!method_restricted)

	return OK;



    if (!(sec->auth_authoritative))

	return DECLINED;



    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

	"access to %s failed for %s, reason: user %s not allowed access",

	r->uri,

	ap_get_remote_host(r->connection, r->per_dir_config, REMOTE_NAME),

	user);

	

    ap_note_basic_auth_failure(r);

    return AUTH_REQUIRED;

}



module MODULE_VAR_EXPORT auth_module =

{

++ apache_1.3.1/src/modules/standard/mod_auth_db.c	1998-07-04 06:08:50.000000000 +0800

