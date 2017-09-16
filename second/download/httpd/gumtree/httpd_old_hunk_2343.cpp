	    else {

		grpname = gr->gr_name;

	    }

	}

	else {

	    if ((pw = getpwuid(r->server->server_uid)) == NULL) {

		ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

			     "getpwuid: invalid userid %ld",

			     (long) r->server->server_uid);

		return (pid);

	    }

	    execuser = ap_pstrdup(r->pool, pw->pw_name);



	    if ((gr = getgrgid(r->server->server_gid)) == NULL) {

		ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

			     "getgrgid: invalid groupid %ld",

			     (long) r->server->server_gid);

		return (pid);

	    }

	    grpname = gr->gr_name;

	}

-- apache_1.3.1/src/modules/example/mod_example.c	1998-06-15 05:10:25.000000000 +0800

