int start_socket_client(char *host, char *path, int argc, char *argv[])
{
	int fd, i;
	char *sargs[MAX_ARGS];
	int sargc=0;
	char line[MAXPATHLEN];
	char *p, *user=NULL;
	extern int remote_version;
	extern int am_sender;
	extern char *shell_cmd;
	extern int list_only;
	extern int kludge_around_eof;
	extern char *bind_address;
	extern int default_af_hint;
       
	if (argc == 0 && !am_sender) {
		extern int list_only;
		list_only = 1;
	}

        /* This is just a friendliness enhancement: if the connection
         * is to an rsyncd then there is no point specifying the -e option.
         * Note that this is only set if the -e was explicitly specified,
         * not if the environment variable just happens to be set.
         * See http://lists.samba.org/pipermail/rsync/2000-September/002744.html
         */
        if (shell_cmd) {
                rprintf(FERROR, "WARNING: --rsh or -e option ignored when "
                        "connecting to rsync daemon\n");
                /* continue */
        }
        
	if (*path == '/') {
		rprintf(FERROR,"ERROR: The remote path must start with a module name not a /\n");
		return -1;
	}

	p = strchr(host, '@');
	if (p) {
		user = host;
		host = p+1;
		*p = 0;
	}

	if (!user) user = getenv("USER");
	if (!user) user = getenv("LOGNAME");

	if (verbose >= 2) {
		/* FIXME: If we're going to use a socket program for
		 * testing, then this message is wrong.  We need to
		 * say something like "(except really using %s)" */
		rprintf(FINFO, "opening tcp connection to %s port %d\n",
			host, rsync_port);
	}
	fd = open_socket_out_wrapped (host, rsync_port, bind_address,
				      default_af_hint);
	if (fd == -1) {
		exit_cleanup(RERR_SOCKETIO);
	}
	
	server_options(sargs,&sargc);

	sargs[sargc++] = ".";

	if (path && *path) 
		sargs[sargc++] = path;

	sargs[sargc] = NULL;

	io_printf(fd,"@RSYNCD: %d\n", PROTOCOL_VERSION);

	if (!read_line(fd, line, sizeof(line)-1)) {
		rprintf(FERROR, "rsync: did not see server greeting\n");
		return -1;
	}

	if (sscanf(line,"@RSYNCD: %d", &remote_version) != 1) {
		/* note that read_line strips of \n or \r */
		rprintf(FERROR, "rsync: server sent \"%s\" rather than greeting\n",
			line);
		return -1;
	}

	p = strchr(path,'/');
	if (p) *p = 0;
	io_printf(fd,"%s\n",path);
	if (p) *p = '/';

	/* Old servers may just drop the connection here,
	 rather than sending a proper EXIT command.  Yuck. */
	kludge_around_eof = list_only && (remote_version < 25);

	while (1) {
		if (!read_line(fd, line, sizeof(line)-1)) {
			rprintf(FERROR, "rsync: didn't get server startup line\n");
			return -1;
		}

		if (strncmp(line,"@RSYNCD: AUTHREQD ",18) == 0) {
			auth_client(fd, user, line+18);
			continue;
		}

		if (strcmp(line,"@RSYNCD: OK") == 0) break;

		if (strcmp(line,"@RSYNCD: EXIT") == 0) exit(0);

		if (strncmp(line, "@ERROR", 6) == 0)
			rprintf(FERROR,"%s\n", line);
		else
			rprintf(FINFO,"%s\n", line);
	}
	kludge_around_eof = False;

	for (i=0;i<sargc;i++) {
		io_printf(fd,"%s\n", sargs[i]);
	}
	io_printf(fd,"\n");

	if (remote_version < 23) {
		if (remote_version == 22 || (remote_version > 17 && !am_sender))
			io_start_multiplex_in(fd);
	}

	return client_run(fd, fd, -1, argc, argv);
}