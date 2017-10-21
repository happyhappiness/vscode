
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

		if (start_glob) {
			if (start_glob == 1) {
				request = strdup(p);
				start_glob++;
			}
			glob_expand(name, &argv, &argc, &maxargs);
		} else
			argc++;

		if (strcmp(line, ".") == 0)
			start_glob = 1;
	}

	argp = argv;
	ret = parse_arguments(&argc, (const char ***) &argp, 0);

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
	if (verbose > lp_max_verbosity())
		verbose = lp_max_verbosity();
#endif

	if (protocol_version < 23
	    && (protocol_version == 22 || am_sender))
		io_start_multiplex_out();
	else if (!ret) {
		/* We have to get I/O multiplexing started so that we can
		 * get the error back to the client.  This means getting
		 * the protocol setup finished first in later versions. */
		setup_protocol(f_out, f_in);
		if (files_from && !am_sender && strcmp(files_from, "-") != 0)
			write_byte(f_out, 0);
		io_start_multiplex_out();
	}

	if (!ret) {
		option_error();
		msleep(400);
		exit_cleanup(RERR_UNSUPPORTED);
	}

	if (lp_timeout(i))
		io_timeout = lp_timeout(i);

	start_server(f_in, f_out, argc, argp);

	return 0;
}

