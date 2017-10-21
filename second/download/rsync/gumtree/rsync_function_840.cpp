static int rsync_module(int f_in, int f_out, int i, char *addr, char *host)
{
	int argc = 0;
	int maxargs;
	char **argv;
	char line[BIGPATHBUFLEN];
	uid_t uid = (uid_t)-2;  /* canonically "nobody" */
	gid_t gid = (gid_t)-2;
	char *p, *err_msg = NULL;
	char *name = lp_name(i);
	int use_chroot = lp_use_chroot(i);
	int start_glob = 0;
	int ret, pre_exec_fd = -1;
	pid_t pre_exec_pid = 0;
	char *request = NULL;

	if (!allow_access(addr, host, lp_hosts_allow(i), lp_hosts_deny(i))) {
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

	auth_user = auth_server(f_in, f_out, i, host, addr, "@RSYNCD: AUTHREQD ");

	if (!auth_user) {
		io_printf(f_out, "@ERROR: auth failed on module %s\n", name);
		return -1;
	}

	module_id = i;

	if (lp_read_only(i))
		read_only = 1;

	if (lp_transfer_logging(i) && !logfile_format)
		logfile_format = lp_log_format(i);
	if (log_format_has(logfile_format, 'i'))
		logfile_format_has_i = 1;
	if (logfile_format_has_i || log_format_has(logfile_format, 'o'))
		logfile_format_has_o_or_i = 1;

	am_root = (MY_UID() == 0);

	if (am_root) {
		p = lp_uid(i);
		if (!name_to_uid(p, &uid)) {
			if (!isdigit(*(unsigned char *)p)) {
				rprintf(FLOG, "Invalid uid %s\n", p);
				io_printf(f_out, "@ERROR: invalid uid %s\n", p);
				return -1;
			}
			uid = atoi(p);
		}

		p = lp_gid(i);
		if (!name_to_gid(p, &gid)) {
			if (!isdigit(*(unsigned char *)p)) {
				rprintf(FLOG, "Invalid gid %s\n", p);
				io_printf(f_out, "@ERROR: invalid gid %s\n", p);
				return -1;
			}
			gid = atoi(p);
		}
	}

	/* TODO: If we're not root, but the configuration requests
	 * that we change to some uid other than the current one, then
	 * log a warning. */

	/* TODO: Perhaps take a list of gids, and make them into the
	 * supplementary groups. */

	if (use_chroot || (module_dirlen = strlen(lp_path(i))) == 1) {
		module_dirlen = 0;
		set_filter_dir("/", 1);
	} else
		set_filter_dir(lp_path(i), module_dirlen);

	p = lp_filter(i);
	parse_rule(&server_filter_list, p, MATCHFLG_WORD_SPLIT,
		   XFLG_ABS_IF_SLASH);

	p = lp_include_from(i);
	parse_filter_file(&server_filter_list, p, MATCHFLG_INCLUDE,
	    XFLG_ABS_IF_SLASH | XFLG_OLD_PREFIXES | XFLG_FATAL_ERRORS);

	p = lp_include(i);
	parse_rule(&server_filter_list, p,
		   MATCHFLG_INCLUDE | MATCHFLG_WORD_SPLIT,
		   XFLG_ABS_IF_SLASH | XFLG_OLD_PREFIXES);

	p = lp_exclude_from(i);
	parse_filter_file(&server_filter_list, p, 0,
	    XFLG_ABS_IF_SLASH | XFLG_OLD_PREFIXES | XFLG_FATAL_ERRORS);

	p = lp_exclude(i);
	parse_rule(&server_filter_list, p, MATCHFLG_WORD_SPLIT,
		   XFLG_ABS_IF_SLASH | XFLG_OLD_PREFIXES);

	log_init(1);

#ifdef HAVE_PUTENV
	if (*lp_prexfer_exec(i) || *lp_postxfer_exec(i)) {
		char *modname, *modpath, *hostaddr, *hostname, *username;
		int status;
		if (asprintf(&modname, "RSYNC_MODULE_NAME=%s", name) < 0
		 || asprintf(&modpath, "RSYNC_MODULE_PATH=%s", lp_path(i)) < 0
		 || asprintf(&hostaddr, "RSYNC_HOST_ADDR=%s", addr) < 0
		 || asprintf(&hostname, "RSYNC_HOST_NAME=%s", host) < 0
		 || asprintf(&username, "RSYNC_USER_NAME=%s", auth_user) < 0)
			out_of_memory("rsync_module");
		putenv(modname);
		putenv(modpath);
		putenv(hostaddr);
		putenv(hostname);
		putenv(username);
		umask(orig_umask);
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
				if (asprintf(&p, "RSYNC_PID=%ld", (long)pid) > 0)
					putenv(p);
				if (wait_process(pid, &status, 0) < 0)
					status = -1;
				if (asprintf(&p, "RSYNC_RAW_STATUS=%d", status) > 0)
					putenv(p);
				if (WIFEXITED(status))
					status = WEXITSTATUS(status);
				else
					status = -1;
				if (asprintf(&p, "RSYNC_EXIT_STATUS=%d", status) > 0)
					putenv(p);
				system(lp_postxfer_exec(i));
				_exit(status);
			}
		}
		/* For pre-xfer exec, fork a child process to run the indicated
		 * command, though it first waits for the parent process to
		 * send us the user's request via a pipe. */
		if (*lp_prexfer_exec(i)) {
			int fds[2];
			if (asprintf(&p, "RSYNC_PID=%ld", (long)getpid()) > 0)
				putenv(p);
			if (pipe(fds) < 0 || (pre_exec_pid = fork()) < 0) {
				rsyserr(FLOG, errno, "pre-xfer exec preparation failed");
				io_printf(f_out, "@ERROR: pre-xfer exec preparation failed\n");
				return -1;
			}
			if (pre_exec_pid == 0) {
				char buf[BIGPATHBUFLEN];
				int j, len;
				close(fds[1]);
				set_blocking(fds[0]);
				len = read_arg_from_pipe(fds[0], buf, BIGPATHBUFLEN);
				if (len <= 0)
					_exit(1);
				if (asprintf(&p, "RSYNC_REQUEST=%s", buf) > 0)
					putenv(p);
				for (j = 0; ; j++) {
					len = read_arg_from_pipe(fds[0], buf,
								 BIGPATHBUFLEN);
					if (len <= 0) {
						if (!len)
							break;
						_exit(1);
					}
					if (asprintf(&p, "RSYNC_ARG%d=%s", j, buf) > 0)
						putenv(p);
				}
				close(fds[0]);
				close(STDIN_FILENO);
				close(STDOUT_FILENO);
				status = system(lp_prexfer_exec(i));
				if (!WIFEXITED(status))
					_exit(1);
				_exit(WEXITSTATUS(status));
			}
			close(fds[0]);
			set_blocking(fds[1]);
			pre_exec_fd = fds[1];
		}
		umask(0);
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
		if (chroot(lp_path(i))) {
			rsyserr(FLOG, errno, "chroot %s failed",
				lp_path(i));
			io_printf(f_out, "@ERROR: chroot failed\n");
			return -1;
		}

		if (!push_dir("/", 0)) {
			rsyserr(FLOG, errno, "chdir %s failed\n",
				lp_path(i));
			io_printf(f_out, "@ERROR: chdir failed\n");
			return -1;
		}

	} else {
		if (!push_dir(lp_path(i), 0)) {
			rsyserr(FLOG, errno, "chdir %s failed\n",
				lp_path(i));
			io_printf(f_out, "@ERROR: chdir failed\n");
			return -1;
		}
		sanitize_paths = 1;
	}

	if (am_root) {
		/* XXXX: You could argue that if the daemon is started
		 * by a non-root user and they explicitly specify a
		 * gid, then we should try to change to that gid --
		 * this could be possible if it's already in their
		 * supplementary groups. */

		/* TODO: Perhaps we need to document that if rsyncd is
		 * started by somebody other than root it will inherit
		 * all their supplementary groups. */

		if (setgid(gid)) {
			rsyserr(FLOG, errno, "setgid %d failed", (int)gid);
			io_printf(f_out, "@ERROR: setgid failed\n");
			return -1;
		}
#ifdef HAVE_SETGROUPS
		/* Get rid of any supplementary groups this process
		 * might have inheristed. */
		if (setgroups(1, &gid)) {
			rsyserr(FLOG, errno, "setgroups failed");
			io_printf(f_out, "@ERROR: setgroups failed\n");
			return -1;
		}
#endif

		if (setuid(uid)) {
			rsyserr(FLOG, errno, "setuid %d failed", (int)uid);
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

	maxargs = MAX_ARGS;
	if (!(argv = new_array(char *, maxargs)))
		out_of_memory("rsync_module");
	argv[argc++] = "rsyncd";

	while (1) {
		if (!read_line(f_in, line, sizeof line - 1))
			return -1;

		if (!*line)
			break;

		p = line;

		if (argc == maxargs) {
			maxargs += MAX_ARGS;
			if (!(argv = realloc_array(argv, char *, maxargs)))
				out_of_memory("rsync_module");
		}
		if (!(argv[argc] = strdup(p)))
			out_of_memory("rsync_module");

		switch (start_glob) {
		case 0:
			argc++;
			if (strcmp(line, ".") == 0)
				start_glob = 1;
			break;
		case 1:
			if (pre_exec_pid) {
				err_msg = finish_pre_exec(pre_exec_pid,
							  pre_exec_fd, p,
							  argc, argv);
				pre_exec_pid = 0;
			}
			request = strdup(p);
			start_glob = 2;
			/* FALL THROUGH */
		default:
			if (!err_msg)
				glob_expand(name, &argv, &argc, &maxargs);
			break;
		}
	}

	if (pre_exec_pid) {
		err_msg = finish_pre_exec(pre_exec_pid, pre_exec_fd, request,
					  argc, argv);
	}

	verbose = 0; /* future verbosity is controlled by client options */
	ret = parse_arguments(&argc, (const char ***) &argv, 0);
	quiet = 0; /* Don't let someone try to be tricky. */

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
	if (verbose > lp_max_verbosity(i))
		verbose = lp_max_verbosity(i);
#endif

	if (protocol_version < 23
	    && (protocol_version == 22 || am_sender))
		io_start_multiplex_out();
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
		io_start_multiplex_out();
	}

	if (!ret || err_msg) {
		if (err_msg)
			rprintf(FERROR, err_msg);
		else
			option_error();
		msleep(400);
		exit_cleanup(RERR_UNSUPPORTED);
	}

	if (lp_timeout(i) && lp_timeout(i) > io_timeout)
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