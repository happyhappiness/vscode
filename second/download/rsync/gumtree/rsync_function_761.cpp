int start_inband_exchange(int f_in, int f_out, const char *user, int argc, char *argv[])
{
	int i, modlen;
	char line[BIGPATHBUFLEN];
	char *sargs[MAX_ARGS];
	int sargc = 0;
	char *p, *modname;

	assert(argc > 0);

	if (**argv == '/') {
		rprintf(FERROR,
			"ERROR: The remote path must start with a module name\n");
		return -1;
	}

	if (!(p = strchr(*argv, '/')))
		modlen = strlen(*argv);
	else
		modlen = p - *argv;

	if (!(modname = new_array(char, modlen+1+1))) /* room for '/' & '\0' */
		out_of_memory("start_inband_exchange");
	strlcpy(modname, *argv, modlen + 1);
	modname[modlen] = '/';
	modname[modlen+1] = '\0';

	if (!user)
		user = getenv("USER");
	if (!user)
		user = getenv("LOGNAME");

	if (exchange_protocols(f_in, f_out, line, sizeof line, 1) < 0)
		return -1;

	/* set daemon_over_rsh to false since we need to build the
	 * true set of args passed through the rsh/ssh connection;
	 * this is a no-op for direct-socket-connection mode */
	daemon_over_rsh = 0;
	server_options(sargs, &sargc);

	if (sargc >= MAX_ARGS - 2)
		goto arg_overflow;

	sargs[sargc++] = ".";

	while (argc > 0) {
		if (sargc >= MAX_ARGS - 1) {
		  arg_overflow:
			rprintf(FERROR, "internal: args[] overflowed in do_cmd()\n");
			exit_cleanup(RERR_SYNTAX);
		}
		if (strncmp(*argv, modname, modlen) == 0
		 && argv[0][modlen] == '\0')
			sargs[sargc++] = modname; /* we send "modname/" */
		else
			sargs[sargc++] = *argv;
		argv++;
		argc--;
	}

	sargs[sargc] = NULL;

	if (verbose > 1)
		print_child_argv("sending daemon args:", sargs);

	io_printf(f_out, "%.*s\n", modlen, modname);

	/* Old servers may just drop the connection here,
	 rather than sending a proper EXIT command.  Yuck. */
	kluge_around_eof = list_only && protocol_version < 25 ? 1 : 0;

	while (1) {
		if (!read_line_old(f_in, line, sizeof line)) {
			rprintf(FERROR, "rsync: didn't get server startup line\n");
			return -1;
		}

		if (strncmp(line,"@RSYNCD: AUTHREQD ",18) == 0) {
			auth_client(f_out, user, line+18);
			continue;
		}

		if (strcmp(line,"@RSYNCD: OK") == 0)
			break;

		if (strcmp(line,"@RSYNCD: EXIT") == 0) {
			/* This is sent by recent versions of the
			 * server to terminate the listing of modules.
			 * We don't want to go on and transfer
			 * anything; just exit. */
			exit(0);
		}

		if (strncmp(line, "@ERROR", 6) == 0) {
			rprintf(FERROR, "%s\n", line);
			/* This is always fatal; the server will now
			 * close the socket. */
			return -1;
		}

		/* This might be a MOTD line or a module listing, but there is
		 * no way to differentiate it.  The manpage mentions this. */
		if (output_motd)
			rprintf(FINFO, "%s\n", line);
	}
	kluge_around_eof = 0;

	if (rl_nulls) {
		for (i = 0; i < sargc; i++) {
			write_sbuf(f_out, sargs[i]);
			write_byte(f_out, 0);
		}
		write_byte(f_out, 0);
	} else {
		for (i = 0; i < sargc; i++)
			io_printf(f_out, "%s\n", sargs[i]);
		write_sbuf(f_out, "\n");
	}

	if (protocol_version < 23) {
		if (protocol_version == 22 || !am_sender)
			io_start_multiplex_in();
	}

	free(modname);

	return 0;
}