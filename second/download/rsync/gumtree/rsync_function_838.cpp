static int rsync_module(int f_in, int f_out, int i, const char *addr, const char *host)
{
	int argc;
	char **argv, **orig_argv, **orig_early_argv, *module_chdir;
	char line[BIGPATHBUFLEN];
#if defined HAVE_INITGROUPS && !defined HAVE_GETGROUPLIST
	struct passwd *pw = NULL;
#endif
	uid_t uid;
	int set_uid;
	char *p, *err_msg = NULL;
	char *name = lp_name(i);
	int use_chroot = lp_use_chroot(i);
	int ret, pre_exec_arg_fd = -1, pre_exec_error_fd = -1;
	int save_munge_symlinks;
	pid_t pre_exec_pid = 0;
	char *request = NULL;

	set_env_str("RSYNC_MODULE_NAME", name);

#ifdef ICONV_OPTION
	iconv_opt = lp_charset(i);
	if (*iconv_opt)
		setup_iconv();
	iconv_opt = NULL;
#endif

	/* If reverse lookup is disabled globally but enabled for this module,
	 * we need to do it now before the access check. */
	if (host == undetermined_hostname && lp_reverse_lookup(i))
		host = client_name(f_in);
	set_env_str("RSYNC_HOST_NAME", host);
	set_env_str("RSYNC_HOST_ADDR", addr);

	if (!allow_access(addr, &host, i)) {
		rprintf(FLOG, "rsync denied on module %s from %s (%s)\n",
			name, host, addr);
		if (!lp_list(i))
			io_printf(f_out, "@ERROR: Unknown module '%s'\n", name);
		else {
			io_printf(f_out,
				  "@ERROR: access denied to %s from %s (%s)\n",
				  name, host, addr);
		}
		return -1;
	}

	if (am_daemon && am_server) {
		rprintf(FLOG, "rsync allowed access on module %s from %s (%s)\n",
			name, host, addr);
	}

	if (!claim_connection(lp_lock_file(i), lp_max_connections(i))) {
		if (errno) {
			rsyserr(FLOG, errno, "failed to open lock file %s",
				lp_lock_file(i));
			io_printf(f_out, "@ERROR: failed to open lock file\n");
		} else {
			rprintf(FLOG, "max connections (%d) reached\n",
				lp_max_connections(i));
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
	if (use_chroot) {
		if ((p = strstr(module_dir, "/./")) != NULL) {
			*p = '\0'; /* Temporary... */
			if (!(module_chdir = normalize_path(module_dir, True, NULL)))
				return path_failure(f_out, module_dir, False);
			*p = '/';
			if (!(p = normalize_path(p + 2, True, &module_dirlen)))
				return path_failure(f_out, strstr(module_dir, "/./"), False);
			if (!(full_module_path = normalize_path(module_dir, False, NULL)))
				full_module_path = module_dir;
			module_dir = p;
		} else {
			if (!(module_chdir = normalize_path(module_dir, False, NULL)))
				return path_failure(f_out, module_dir, False);
			full_module_path = module_chdir;
			module_dir = "/";
			module_dirlen = 1;
		}
	} else {
		if (!(module_chdir = normalize_path(module_dir, False, &module_dirlen)))
			return path_failure(f_out, module_dir, False);
		full_module_path = module_dir = module_chdir;
	}
	set_env_str("RSYNC_MODULE_PATH", full_module_path);

	if (module_dirlen == 1) {
		module_dirlen = 0;
		set_filter_dir("/", 1);
	} else
		set_filter_dir(module_dir, module_dirlen);

	p = lp_filter(i);
	parse_filter_str(&daemon_filter_list, p, rule_template(FILTRULE_WORD_SPLIT),
		   XFLG_ABS_IF_SLASH | XFLG_DIR2WILD3);

	p = lp_include_from(i);
	parse_filter_file(&daemon_filter_list, p, rule_template(FILTRULE_INCLUDE),
	    XFLG_ABS_IF_SLASH | XFLG_DIR2WILD3 | XFLG_OLD_PREFIXES | XFLG_FATAL_ERRORS);

	p = lp_include(i);
	parse_filter_str(&daemon_filter_list, p,
		   rule_template(FILTRULE_INCLUDE | FILTRULE_WORD_SPLIT),
		   XFLG_ABS_IF_SLASH | XFLG_DIR2WILD3 | XFLG_OLD_PREFIXES);

	p = lp_exclude_from(i);
	parse_filter_file(&daemon_filter_list, p, rule_template(0),
	    XFLG_ABS_IF_SLASH | XFLG_DIR2WILD3 | XFLG_OLD_PREFIXES | XFLG_FATAL_ERRORS);

	p = lp_exclude(i);
	parse_filter_str(&daemon_filter_list, p, rule_template(FILTRULE_WORD_SPLIT),
		   XFLG_ABS_IF_SLASH | XFLG_DIR2WILD3 | XFLG_OLD_PREFIXES);

	log_init(1);

#ifdef HAVE_PUTENV
	if (*lp_prexfer_exec(i) || *lp_postxfer_exec(i)) {
		int status;

		/* For post-xfer exec, fork a new process to run the rsync
		 * daemon while this process waits for the exit status and
		 * runs the indicated command at that point. */
		if (*lp_postxfer_exec(i)) {
			pid_t pid = fork();
			if (pid < 0) {
				rsyserr(FLOG, errno, "fork failed");
				io_printf(f_out, "@ERROR: fork failed\n");
				return -1;
			}
			if (pid) {
				close(f_in);
				if (f_out != f_in)
					close(f_out);
				set_env_num("RSYNC_PID", (long)pid);
				if (wait_process(pid, &status, 0) < 0)
					status = -1;
				set_env_num("RSYNC_RAW_STATUS", status);
				if (WIFEXITED(status))
					status = WEXITSTATUS(status);
				else
					status = -1;
				set_env_num("RSYNC_EXIT_STATUS", status);
				if (system(lp_postxfer_exec(i)) < 0)
					status = -1;
				_exit(status);
			}
		}
		/* For pre-xfer exec, fork a child process to run the indicated
		 * command, though it first waits for the parent process to
		 * send us the user's request via a pipe. */
		if (*lp_prexfer_exec(i)) {
			int arg_fds[2], error_fds[2];
			set_env_num("RSYNC_PID", (long)getpid());
			if (pipe(arg_fds) < 0 || pipe(error_fds) < 0 || (pre_exec_pid = fork()) < 0) {
				rsyserr(FLOG, errno, "pre-xfer exec preparation failed");
				io_printf(f_out, "@ERROR: pre-xfer exec preparation failed\n");
				return -1;
			}
			if (pre_exec_pid == 0) {
				char buf[BIGPATHBUFLEN];
				int j, len;
				close(arg_fds[1]);
				close(error_fds[0]);
				pre_exec_arg_fd = arg_fds[0];
				pre_exec_error_fd = error_fds[1];
				set_blocking(pre_exec_arg_fd);
				set_blocking(pre_exec_error_fd);
				len = read_arg_from_pipe(pre_exec_arg_fd, buf, BIGPATHBUFLEN);
				if (len <= 0)
					_exit(1);
				set_env_str("RSYNC_REQUEST", buf);
				for (j = 0; ; j++) {
					len = read_arg_from_pipe(pre_exec_arg_fd, buf,
								 BIGPATHBUFLEN);
					if (len <= 0) {
						if (!len)
							break;
						_exit(1);
					}
					if (asprintf(&p, "RSYNC_ARG%d=%s", j, buf) >= 0)
						putenv(p);
				}
				close(pre_exec_arg_fd);
				close(STDIN_FILENO);
				dup2(pre_exec_error_fd, STDOUT_FILENO);
				close(pre_exec_error_fd);
				status = system(lp_prexfer_exec(i));
				if (!WIFEXITED(status))
					_exit(1);
				_exit(WEXITSTATUS(status));
			}
			close(arg_fds[0]);
			close(error_fds[1]);
			pre_exec_arg_fd = arg_fds[1];
			pre_exec_error_fd = error_fds[0];
			set_blocking(pre_exec_arg_fd);
			set_blocking(pre_exec_error_fd);
		}
	}
#endif

	if (use_chroot) {
		/*
		 * XXX: The 'use chroot' flag is a fairly reliable
		 * source of confusion, because it fails under two
		 * important circumstances: running as non-root,
		 * running on Win32 (or possibly others).  On the
		 * other hand, if you are running as root, then it
		 * might be better to always use chroot.
		 *
		 * So, perhaps if we can't chroot we should just issue
		 * a warning, unless a "require chroot" flag is set,
		 * in which case we fail.
		 */
		if (chroot(module_chdir)) {
			rsyserr(FLOG, errno, "chroot %s failed", module_chdir);
			io_printf(f_out, "@ERROR: chroot failed\n");
			return -1;
		}
		module_chdir = module_dir;
	}

	if (!change_dir(module_chdir, CD_NORMAL))
		return path_failure(f_out, module_chdir, True);
	if (module_dirlen || !use_chroot)
		sanitize_paths = 1;

	if ((munge_symlinks = lp_munge_symlinks(i)) < 0)
		munge_symlinks = !use_chroot || module_dirlen;
	if (munge_symlinks) {
		STRUCT_STAT st;
		char prefix[SYMLINK_PREFIX_LEN]; /* NOT +1 ! */
		strlcpy(prefix, SYMLINK_PREFIX, sizeof prefix); /* trim the trailing slash */
		if (do_stat(prefix, &st) == 0 && S_ISDIR(st.st_mode)) {
			rprintf(FLOG, "Symlink munging is unsafe when a %s directory exists.\n",
				prefix);
			io_printf(f_out, "@ERROR: daemon security issue -- contact admin\n", name);
			exit_cleanup(RERR_UNSUPPORTED);
		}
	}

	if (gid_count) {
		if (setgid(gid_list[0])) {
			rsyserr(FLOG, errno, "setgid %ld failed", (long)gid_list[0]);
			io_printf(f_out, "@ERROR: setgid failed\n");
			return -1;
		}
#ifdef HAVE_SETGROUPS
		/* Set the group(s) we want to be active. */
		if (setgroups(gid_count, gid_list)) {
			rsyserr(FLOG, errno, "setgroups failed");
			io_printf(f_out, "@ERROR: setgroups failed\n");
			return -1;
		}
#endif
#if defined HAVE_INITGROUPS && !defined HAVE_GETGROUPLIST
		/* pw is set if the user wants all the user's groups. */
		if (pw && initgroups(pw->pw_name, pw->pw_gid) < 0) {
			rsyserr(FLOG, errno, "initgroups failed");
			io_printf(f_out, "@ERROR: initgroups failed\n");
			return -1;
		}
#endif
	}

	if (set_uid) {
		if (setuid(uid) < 0
#ifdef HAVE_SETEUID
		 || seteuid(uid) < 0
#endif
		) {
			rsyserr(FLOG, errno, "setuid %ld failed", (long)uid);
			io_printf(f_out, "@ERROR: setuid failed\n");
			return -1;
		}

		am_root = (MY_UID() == 0);
	}

	if (lp_temp_dir(i) && *lp_temp_dir(i)) {
		tmpdir = lp_temp_dir(i);
		if (strlen(tmpdir) >= MAXPATHLEN - 10) {
			rprintf(FLOG,
				"the 'temp dir' value for %s is WAY too long -- ignoring.\n",
				name);
			tmpdir = NULL;
		}
	}

	io_printf(f_out, "@RSYNCD: OK\n");

	read_args(f_in, name, line, sizeof line, rl_nulls, &argv, &argc, &request);
	orig_argv = argv;

	save_munge_symlinks = munge_symlinks;

	reset_output_levels(); /* future verbosity is controlled by client options */
	ret = parse_arguments(&argc, (const char ***) &argv);
	if (protect_args && ret) {
		orig_early_argv = orig_argv;
		protect_args = 2;
		read_args(f_in, name, line, sizeof line, 1, &argv, &argc, &request);
		orig_argv = argv;
		ret = parse_arguments(&argc, (const char ***) &argv);
	} else
		orig_early_argv = NULL;

	munge_symlinks = save_munge_symlinks; /* The client mustn't control this. */

	if (pre_exec_pid) {
		err_msg = finish_pre_exec(pre_exec_pid, pre_exec_arg_fd, pre_exec_error_fd,
					  request, orig_early_argv, orig_argv);
	}

	if (orig_early_argv)
		free(orig_early_argv);

	am_server = 1; /* Don't let someone try to be tricky. */
	quiet = 0;
	if (lp_ignore_errors(module_id))
		ignore_errors = 1;
	if (write_batch < 0)
		dry_run = 1;

	if (lp_fake_super(i)) {
		if (preserve_xattrs > 1)
			preserve_xattrs = 1;
		am_root = -1;
	} else if (am_root < 0) /* Treat --fake-super from client as --super. */
		am_root = 2;

	if (filesfrom_fd == 0)
		filesfrom_fd = f_in;

	if (request) {
		if (*auth_user) {
			rprintf(FLOG, "rsync %s %s from %s@%s (%s)\n",
				am_sender ? "on" : "to",
				request, auth_user, host, addr);
		} else {
			rprintf(FLOG, "rsync %s %s from %s (%s)\n",
				am_sender ? "on" : "to",
				request, host, addr);
		}
		free(request);
	}

#ifndef DEBUG
	/* don't allow the logs to be flooded too fast */
	limit_output_verbosity(lp_max_verbosity(i));
#endif

	if (protocol_version < 23
	    && (protocol_version == 22 || am_sender))
		io_start_multiplex_out(f_out);
	else if (!ret || err_msg) {
		/* We have to get I/O multiplexing started so that we can
		 * get the error back to the client.  This means getting
		 * the protocol setup finished first in later versions. */
		setup_protocol(f_out, f_in);
		if (!am_sender) {
			/* Since we failed in our option parsing, we may not
			 * have finished parsing that the client sent us a
			 * --files-from option, so look for it manually.
			 * Without this, the socket would be in the wrong
			 * state for the upcoming error message. */
			if (!files_from) {
				int i;
				for (i = 0; i < argc; i++) {
					if (strncmp(argv[i], "--files-from", 12) == 0) {
						files_from = "";
						break;
					}
				}
			}
			if (files_from)
				write_byte(f_out, 0);
		}
		io_start_multiplex_out(f_out);
	}

	if (!ret || err_msg) {
		if (err_msg) {
			while ((p = strchr(err_msg, '\n')) != NULL) {
				int len = p - err_msg + 1;
				rwrite(FERROR, err_msg, len, 0);
				err_msg += len;
			}
			if (*err_msg)
				rprintf(FERROR, "%s\n", err_msg);
		} else
			option_error();
		msleep(400);
		exit_cleanup(RERR_UNSUPPORTED);
	}

#ifdef ICONV_OPTION
	if (!iconv_opt) {
		if (ic_send != (iconv_t)-1) {
			iconv_close(ic_send);
			ic_send = (iconv_t)-1;
		}
		if (ic_recv != (iconv_t)-1) {
			iconv_close(ic_recv);
			ic_recv = (iconv_t)-1;
		}
	}
#endif

	if (!numeric_ids
	 && (use_chroot ? lp_numeric_ids(i) != False : lp_numeric_ids(i) == True))
		numeric_ids = -1; /* Set --numeric-ids w/o breaking protocol. */

	if (lp_timeout(i) && (!io_timeout || lp_timeout(i) < io_timeout))
		set_io_timeout(lp_timeout(i));

	/* If we have some incoming/outgoing chmod changes, append them to
	 * any user-specified changes (making our changes have priority).
	 * We also get a pointer to just our changes so that a receiver
	 * process can use them separately if --perms wasn't specified. */
	if (am_sender)
		p = lp_outgoing_chmod(i);
	else
		p = lp_incoming_chmod(i);
	if (*p && !(daemon_chmod_modes = parse_chmod(p, &chmod_modes))) {
		rprintf(FLOG, "Invalid \"%sing chmod\" directive: %s\n",
			am_sender ? "outgo" : "incom", p);
	}

	start_server(f_in, f_out, argc, argv);

	return 0;
}