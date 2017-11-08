int start_socket_client(char *host, int remote_argc, char *remote_argv[],
			int argc, char *argv[])
{
	int fd, ret;
	char *p, *user = NULL;

	/* This is redundant with code in start_inband_exchange(), but this
	 * short-circuits a problem in the client before we open a socket,
	 * and the extra check won't hurt. */
	if (**remote_argv == '/') {
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

#ifdef ICONV_CONST
	setup_iconv();
#endif

	ret = start_inband_exchange(fd, fd, user, remote_argc, remote_argv);

	return ret ? ret : client_run(fd, fd, -1, argc, argv);
}