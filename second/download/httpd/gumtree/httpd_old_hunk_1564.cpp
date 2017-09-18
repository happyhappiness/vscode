    if (!sec->auth_dbpwfile)
	return DECLINED;

    if (!(real_pw = get_db_pw(r, c->user, sec->auth_dbpwfile))) {
	if (!(sec->auth_dbauthoritative))
	    return DECLINED;
	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
		    "DB user %s not found: %s", c->user, r->filename);
	ap_note_basic_auth_failure(r);
	return AUTH_REQUIRED;
    }
    /* Password is up to first : if exists */
    colon_pw = strchr(real_pw, ':');
    if (colon_pw)
	*colon_pw = '\0';
    /* anyone know where the prototype for crypt is? */
    if (strcmp(real_pw, (char *) crypt(sent_pw, real_pw))) {
	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
		    "DB user %s: password mismatch: %s", c->user, r->uri);
	ap_note_basic_auth_failure(r);
	return AUTH_REQUIRED;
    }
    return OK;
}
