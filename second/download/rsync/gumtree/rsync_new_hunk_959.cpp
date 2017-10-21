			io_printf(f_out, "@ERROR: max connections (%d) reached -- try again later\n",
				lp_max_connections(i));
		}
		return -1;
	}

	read_only = lp_read_only(i); /* may also be overridden by auth_server() */
	auth_user = auth_server(f_in, f_out, i, host, addr, "@RSYNCD: AUTHREQD ");

	if (!auth_user) {
		io_printf(f_out, "@ERROR: auth failed on module %s\n", name);
		return -1;
	}
	set_env_str("RSYNC_USER_NAME", auth_user);

	module_id = i;

	if (lp_transfer_logging(i) && !logfile_format)
		logfile_format = lp_log_format(i);
	if (log_format_has(logfile_format, 'i'))
		logfile_format_has_i = 1;
	if (logfile_format_has_i || log_format_has(logfile_format, 'o'))
		logfile_format_has_o_or_i = 1;

	uid = MY_UID();
	am_root = (uid == 0);

	p = *lp_uid(i) ? lp_uid(i) : am_root ? NOBODY_USER : NULL;
	if (p) {
		if (!user_to_uid(p, &uid, True)) {
			rprintf(FLOG, "Invalid uid %s\n", p);
			io_printf(f_out, "@ERROR: invalid uid %s\n", p);
			return -1;
		}
		set_uid = 1;
	} else
		set_uid = 0;

	p = *lp_gid(i) ? strtok(lp_gid(i), ", ") : NULL;
	if (p) {
		/* The "*" gid must be the first item in the list. */
		if (strcmp(p, "*") == 0) {
#ifdef HAVE_GETGROUPLIST
			if (want_all_groups(f_out, uid) < 0)
				return -1;
#elif defined HAVE_INITGROUPS
			if ((pw = want_all_groups(f_out, uid)) == NULL)
				return -1;
#else
			rprintf(FLOG, "This rsync does not support a gid of \"*\"\n");
			io_printf(f_out, "@ERROR: invalid gid setting.\n");
			return -1;
#endif
		} else if (add_a_group(f_out, p) < 0)
			return -1;
		while ((p = strtok(NULL, ", ")) != NULL) {
#if defined HAVE_INITGROUPS && !defined HAVE_GETGROUPLIST
			if (pw) {
				rprintf(FLOG, "This rsync cannot add groups after \"*\".\n");
				io_printf(f_out, "@ERROR: invalid gid setting.\n");
				return -1;
			}
#endif
			if (add_a_group(f_out, p) < 0)
				return -1;
		}
	} else if (am_root) {
		if (add_a_group(f_out, NOBODY_GROUP) < 0)
			return -1;
	}

	module_dir = lp_path(i);
	if (*module_dir == '\0') {
		rprintf(FLOG, "No path specified for module %s\n", name);
		io_printf(f_out, "@ERROR: no path setting.\n");
		return -1;
	}
