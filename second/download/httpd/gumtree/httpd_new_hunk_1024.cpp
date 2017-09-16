	    else {

		grpname = gr->gr_name;

	    }

	}

	else {

	    if ((pw = getpwuid(r->server->server_uid)) == NULL) {

		ap_log_rerror(APLOG_MARK, APLOG_ERR, r,

			     "getpwuid: invalid userid %ld",

			     (long) r->server->server_uid);

		return (pid);

	    }

	    execuser = ap_pstrdup(r->pool, pw->pw_name);



	    if ((gr = getgrgid(r->server->server_gid)) == NULL) {

		ap_log_rerror(APLOG_MARK, APLOG_ERR, r,

			     "getgrgid: invalid groupid %ld",

			     (long) r->server->server_gid);

		return (pid);

	    }

	    grpname = gr->gr_name;

	}

