static int rsync_module(int f_in, int f_out, int i)
{
	int argc=0;
	char *argv[MAX_ARGS];
	char **argp;
	char line[MAXPATHLEN];
	uid_t uid = (uid_t)-2;  /* canonically "nobody" */
	gid_t gid = (gid_t)-2;
	char *p;
	char *addr = client_addr(f_in);
	char *host = client_name(f_in);
	char *name = lp_name(i);
	int use_chroot = lp_use_chroot(i);
	int start_glob=0;
	int ret;
	char *request=NULL;
	extern int am_sender;
	extern int am_server;
	extern int am_daemon;
	extern int remote_version;
	extern int am_root;

	if (!allow_access(addr, host, lp_hosts_allow(i), lp_hosts_deny(i))) {
		rprintf(FERROR,"rsync denied on module %s from %s (%s)\n",
			name, host, addr);
		io_printf(f_out, "@ERROR: access denied to %s from %s (%s)\n",
			  name, host, addr);
		return -1;
	}

	if (am_daemon && am_server) {
		rprintf(FINFO, "rsync allowed access on module %s from %s (%s)\n",
			name, host, addr);
	}

	if (!claim_connection(lp_lock_file(i), lp_max_connections(i))) {
		if (errno) {
			rprintf(FERROR,"failed to open lock file %s : %s\n",
				lp_lock_file(i), strerror(errno));
			io_printf(f_out, "@ERROR: failed to open lock file %s : %s\n",
				  lp_lock_file(i), strerror(errno));
		} else {
			rprintf(FERROR,"max connections (%d) reached\n",
				lp_max_connections(i));
			io_printf(f_out, "@ERROR: max connections (%d) reached - try again later\n", lp_max_connections(i));
		}
		return -1;
	}

	
	auth_user = auth_server(f_in, f_out, i, addr, "@RSYNCD: AUTHREQD ");

	if (!auth_user) {
		rprintf(FERROR,"auth failed on module %s from %s (%s)\n",
			name, host, addr);
		io_printf(f_out, "@ERROR: auth failed on module %s\n", name);
		return -1;		
	}

	module_id = i;

	am_root = (getuid() == 0);

	if (am_root) {
		p = lp_uid(i);
		if (!name_to_uid(p, &uid)) {
			if (!isdigit(* (unsigned char *) p)) {
				rprintf(FERROR,"Invalid uid %s\n", p);
				io_printf(f_out, "@ERROR: invalid uid %s\n", p);
				return -1;
			} 
			uid = atoi(p);
		}

		p = lp_gid(i);
		if (!name_to_gid(p, &gid)) {
			if (!isdigit(* (unsigned char *) p)) {
				rprintf(FERROR,"Invalid gid %s\n", p);
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

	p = lp_include_from(i);
	add_exclude_file(p, 1, 1);

	p = lp_include(i);
	add_include_line(p);

	p = lp_exclude_from(i);
	add_exclude_file(p, 1, 0);

	p = lp_exclude(i);
	add_exclude_line(p);

	log_init();

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
			rsyserr(FERROR, errno, "chroot %s failed", lp_path(i));
			io_printf(f_out, "@ERROR: chroot failed\n");
			return -1;
		}

		if (!push_dir("/", 0)) {
                        rsyserr(FERROR, errno, "chdir %s failed\n", lp_path(i));
			io_printf(f_out, "@ERROR: chdir failed\n");
			return -1;
		}

	} else {
		if (!push_dir(lp_path(i), 0)) {
			rsyserr(FERROR, errno, "chdir %s failed\n", lp_path(i));
			io_printf(f_out, "@ERROR: chdir failed\n");
			return -1;
		}
		sanitize_paths = 1;
	}

	if (am_root) {
#ifdef HAVE_SETGROUPS
		/* Get rid of any supplementary groups this process
		 * might have inheristed. */
		if (setgroups(0, NULL)) {
			rsyserr(FERROR, errno, "setgroups failed");
			io_printf(f_out, "@ERROR: setgroups failed\n");
			return -1;
		}
#endif

		/* XXXX: You could argue that if the daemon is started
		 * by a non-root user and they explicitly specify a
		 * gid, then we should try to change to that gid --
		 * this could be possible if it's already in their
		 * supplementary groups. */

		/* TODO: Perhaps we need to document that if rsyncd is
		 * started by somebody other than root it will inherit
		 * all their supplementary groups. */

		if (setgid(gid)) {
			rsyserr(FERROR, errno, "setgid %d failed", (int) gid);
			io_printf(f_out, "@ERROR: setgid failed\n");
			return -1;
		}

		if (setuid(uid)) {
			rsyserr(FERROR, errno, "setuid %d failed", (int) uid);
			io_printf(f_out, "@ERROR: setuid failed\n");
			return -1;
		}

		am_root = (getuid() == 0);
	}

	io_printf(f_out, "@RSYNCD: OK\n");

	argv[argc++] = "rsyncd";

	while (1) {
		if (!read_line(f_in, line, sizeof(line)-1)) {
			return -1;
		}

		if (!*line) break;

		p = line;

		argv[argc] = strdup(p);
		if (!argv[argc]) {
			return -1;
		}

		if (start_glob) {
			if (start_glob == 1) {
				request = strdup(p);
				start_glob++;
			}
			glob_expand(name, argv, &argc, MAX_ARGS);
		} else {
			argc++;
		}

		if (strcmp(line,".") == 0) {
			start_glob = 1;
		}

		if (argc == MAX_ARGS) {
			return -1;
		}
	}

	if (sanitize_paths) {
		/*
		 * Note that this is applied to all parameters, whether or not
		 *    they are filenames, but no other legal parameters contain
		 *    the forms that need to be sanitized so it doesn't hurt;
		 *    it is not known at this point which parameters are files
		 *    and which aren't.
		 */
		for (i = 1; i < argc; i++) {
			sanitize_path(argv[i], NULL);
		}
	}

        argp = argv;
	ret = parse_arguments(&argc, (const char ***) &argp, 0);

	if (request) {
		if (*auth_user) {
			rprintf(FINFO,"rsync %s %s from %s@%s (%s)\n",
				am_sender?"on":"to",
				request, auth_user, host, addr);
		} else {
			rprintf(FINFO,"rsync %s %s from %s (%s)\n",
				am_sender?"on":"to",
				request, host, addr);
		}
		free(request);
	}

#ifndef DEBUG
	/* don't allow the logs to be flooded too fast */
	if (verbose > 1) verbose = 1;
#endif

	if (remote_version < 23) {
		if (remote_version == 22 || (remote_version > 17 && am_sender))
			io_start_multiplex_out(f_out);
	}
        
        /* For later protocol versions, we don't start multiplexing
         * until we've configured nonblocking in start_server.  That
         * means we're in a sticky situation now: there's no way to
         * convey errors to the client. */

        /* FIXME: Hold off on reporting option processing errors until
         * we've set up nonblocking and multiplexed IO and can get the
         * message back to them. */
	if (!ret) {
                option_error();
                exit_cleanup(RERR_UNSUPPORTED);
	}

	if (lp_timeout(i)) {
		extern int io_timeout;
		io_timeout = lp_timeout(i);
	}

	start_server(f_in, f_out, argc, argp);

	return 0;
}