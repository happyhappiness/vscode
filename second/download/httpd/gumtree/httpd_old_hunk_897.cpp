    if (!method_restricted)

	return OK;



    if (!(sec->auth_authoritative))

	return DECLINED;



    ap_note_basic_auth_failure(r);

    return AUTH_REQUIRED;

}



module MODULE_VAR_EXPORT auth_module =

{

-- apache_1.3.0/src/modules/standard/mod_auth_db.c	1998-04-11 20:00:44.000000000 +0800

