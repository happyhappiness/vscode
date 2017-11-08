int start_socket_client(char *host, char *path, int argc, char *argv[])
{
	int fd, ret;
	char *p, *user=NULL;
	extern char *bind_address;
	extern int default_af_hint;

	/* this is redundant with code in start_inband_exchange(), but
	 * this short-circuits a problem before we open a socket, and
	 * the extra check won't hurt */
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

	if (verbose >= 2) {
		/* FIXME: If we're going to use a socket program for
		 * testing, then this message is wrong.  We need to
		 * say something like "(except really using %s)" */
		rprintf(FINFO, "opening tcp connection to %s port %d\n",
			host, rsync_port);
	}
	fd = open_socket_out_wrapped(host, rsync_port, bind_address,
				     default_af_hint);
	if (fd == -1) {
		exit_cleanup(RERR_SOCKETIO);
	}

	ret = start_inband_exchange(user, path, fd, fd, argc);

	return ret < 0? ret : client_run(fd, fd, -1, argc, argv);
}