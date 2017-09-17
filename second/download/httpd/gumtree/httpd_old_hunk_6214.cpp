
	    if (pos) {
		*pos = '\0';
	    }

	    if ((pw = getpwnam(username)) == NULL) {
		ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			     "getpwnam: invalid username %s", username);
		return (pid);
	    }
	    execuser = ap_pstrcat(r->pool, "~", pw->pw_name, NULL);
	    user_gid = pw->pw_gid;

