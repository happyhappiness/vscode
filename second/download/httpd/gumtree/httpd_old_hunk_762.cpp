{
    anon_auth_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                      &auth_anon_module);
    const char *sent_pw;
    int res = DECLINED;

    if ((res = ap_get_basic_auth_pw(r, &sent_pw)))
	return res;

    /* Ignore if we are not configured */
    if (!conf->anon_auth_passwords)
	return DECLINED;

    /* Do we allow an empty userID and/or is it the magic one
     */

    if ((!(r->user[0])) && (conf->anon_auth_nouserid)) {
	res = OK;
    }
    else {
	anon_auth *p = conf->anon_auth_passwords;
	res = DECLINED;
	while ((res == DECLINED) && (p != NULL)) {
	    if (!(strcasecmp(r->user, p->password)))
		res = OK;
	    p = p->next;
	}
    }
    if (
    /* username is OK */
	   (res == OK)
    /* password been filled out ? */
	   && ((!conf->anon_auth_mustemail) || strlen(sent_pw))
    /* does the password look like an email address ? */
	   && ((!conf->anon_auth_verifyemail)
	       || ((strpbrk("@", sent_pw) != NULL)
		   && (strpbrk(".", sent_pw) != NULL)))) {
	if (conf->anon_auth_logemail && ap_is_initial_req(r)) {
	    ap_log_rerror(APLOG_MARK, APLOG_INFO, APR_SUCCESS, r,
			"Anonymous: Passwd <%s> Accepted",
