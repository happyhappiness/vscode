int start_socket_client(char *host, char *path, int argc, char *argv[])
{
	int fd, ret;
	char *p, *user = NULL;

	/* This is redundant with code in start_inband_exchange(), but this
	 * short-circuits a problem in the client before we open a socket,
	 * and the extra check won't hurt. */
	if (*path == '/') {
		rprintf(FERROR,
			"ERROR: The remote path must start with a module name not a /\n");
		return -1;
	}

	if ((p = strrchr(host, '@')) != NULL) {
		user = host;
		host = p+1;
		*p = '\0';
	}

	fd = open_socket_out_wrapped(host, rsync_port, bind_address,
				     default_af_hint);
	if (fd == -1)
		exit_cleanup(RERR_SOCKETIO);

	set_socket_options(fd, sockopts);

	ret = start_inband_exchange(user, path, fd, fd, argc);

	return ret ? ret : client_run(fd, fd, -1, argc, argv);
}