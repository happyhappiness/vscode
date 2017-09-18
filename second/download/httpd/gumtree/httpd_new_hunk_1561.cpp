    if (!sec->auth_pwfile)
	return DECLINED;

    if (!(real_pw = get_pw(r, c->user, sec->auth_pwfile))) {
	if (!(sec->auth_authoritative))
	    return DECLINED;
	ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
		    "user %s not found: %s", c->user, r->uri);
	ap_note_basic_auth_failure(r);
	return AUTH_REQUIRED;
    }
    /* anyone know where the prototype for crypt is? */
    if (strcmp(real_pw, (char *) crypt(sent_pw, real_pw))) {
	ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
		    "user %s: password mismatch: %s", c->user, r->uri);
	ap_note_basic_auth_failure(r);
	return AUTH_REQUIRED;
    }
    return OK;
}
