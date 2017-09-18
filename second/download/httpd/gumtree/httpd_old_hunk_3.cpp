	   && ((!conf->anon_auth_mustemail) || strlen(sent_pw))
    /* does the password look like an email address ? */
	   && ((!conf->anon_auth_verifyemail)
	       || ((strpbrk("@", sent_pw) != NULL)
		   && (strpbrk(".", sent_pw) != NULL)))) {
	if (conf->anon_auth_logemail && ap_is_initial_req(r)) {
	    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, APR_SUCCESS, r,
			"Anonymous: Passwd <%s> Accepted",
			sent_pw ? sent_pw : "\'none\'");
	}
	return OK;
    }
    else {
	if (conf->anon_auth_authoritative) {
	    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, APR_SUCCESS, r,
			"Anonymous: Authoritative, Passwd <%s> not accepted",
			sent_pw ? sent_pw : "\'none\'");
	    return HTTP_UNAUTHORIZED;
	}
	/* Drop out the bottom to return DECLINED */
    }
