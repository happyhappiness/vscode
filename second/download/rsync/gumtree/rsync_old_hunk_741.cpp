
		/* TODO: Perhaps we need to document that if rsyncd is
		 * started by somebody other than root it will inherit
		 * all their supplementary groups. */

		if (setgid(gid)) {
			rsyserr(FERROR, errno, "setgid %d failed", (int) gid);
			io_printf(f_out, "@ERROR: setgid failed\n");
			return -1;
		}
#ifdef HAVE_SETGROUPS
		/* Get rid of any supplementary groups this process
		 * might have inheristed. */
		if (setgroups(1, &gid)) {
			rsyserr(FERROR, errno, "setgroups failed");
			io_printf(f_out, "@ERROR: setgroups failed\n");
			return -1;
		}
#endif

		if (setuid(uid)) {
			rsyserr(FERROR, errno, "setuid %d failed", (int) uid);
			io_printf(f_out, "@ERROR: setuid failed\n");
			return -1;
		}

		am_root = (MY_UID() == 0);
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

	argp = argv;
	ret = parse_arguments(&argc, (const char ***) &argp, 0);

	if (filesfrom_fd == 0)
		filesfrom_fd = f_in;

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
	if (verbose > lp_max_verbosity())
		verbose = lp_max_verbosity();
#endif

	if (protocol_version < 23) {
		if (protocol_version == 22 || am_sender)
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
		io_timeout = lp_timeout(i);
	}

	start_server(f_in, f_out, argc, argp);

	return 0;
}

