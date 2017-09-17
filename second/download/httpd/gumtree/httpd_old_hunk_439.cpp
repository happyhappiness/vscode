	    }
	}
#endif
	return (pid);
    }
#else
    if (ap_suexec_enabled &&
	((r->server->server_uid != ap_user_id) ||
	 (r->server->server_gid != ap_group_id) ||
	 (!strncmp("/~", r->uri, 2)))) {

	char *execuser, *grpname;
	struct passwd *pw;
	struct group *gr;

	if (!strncmp("/~", r->uri, 2)) {
	    gid_t user_gid;
	    char *username = ap_pstrdup(r->pool, r->uri + 2);
	    char *pos = strchr(username, '/');

	    if (pos)
		*pos = '\0';

	    if ((pw = getpwnam(username)) == NULL) {
		ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			    "getpwnam: invalid username %s", username);
		return (pid);
	    }
	    execuser = ap_pstrcat(r->pool, "~", pw->pw_name, NULL);
	    user_gid = pw->pw_gid;

	    if ((gr = getgrgid(user_gid)) == NULL) {
		if ((grpname = ap_palloc(r->pool, 16)) == NULL)
		    return (pid);
		else
		    ap_snprintf(grpname, 16, "%ld", (long) user_gid);
	    }
	    else
		grpname = gr->gr_name;
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

	if (shellcmd)
	    execle(SUEXEC_BIN, SUEXEC_BIN, execuser, grpname, argv0, NULL, env);

	else if ((!r->args) || (!r->args[0]) || strchr(r->args, '='))
	    execle(SUEXEC_BIN, SUEXEC_BIN, execuser, grpname, argv0, NULL, env);

	else {
	    execve(SUEXEC_BIN,
		   create_argv(r->pool, SUEXEC_BIN, execuser, grpname,
			       argv0, r->args),
		   env);
	}
    }
    else {
	if (shellcmd)
	    execle(SHELL_PATH, SHELL_PATH, "-c", argv0, NULL, env);

	else if ((!r->args) || (!r->args[0]) || strchr(r->args, '='))
	    execle(r->filename, argv0, NULL, env);

	else
	    execve(r->filename,
		   create_argv(r->pool, NULL, NULL, NULL, argv0, r->args),
		   env);
    }
    return (pid);
#endif
}
-- apache_1.3.0/src/main/util_uri.c	1998-05-30 09:54:30.000000000 +0800
