
	free(response);

	return 0;
}

static struct imap_store *imap_open_store(struct imap_server_conf *srvc)
{
	struct credential cred = CREDENTIAL_INIT;
	struct imap_store *ctx;
	struct imap *imap;
	char *arg, *rsp;
	int s = -1, preauth;

	ctx = xcalloc(1, sizeof(*ctx));

	ctx->imap = imap = xcalloc(sizeof(*imap), 1);
	imap->buf.sock.fd[0] = imap->buf.sock.fd[1] = -1;
	imap->in_progress_append = &imap->in_progress;

	/* open connection to IMAP server */

	if (srvc->tunnel) {
		const char *argv[] = { srvc->tunnel, NULL };
		struct child_process tunnel = {NULL};

		imap_info("Starting tunnel '%s'... ", srvc->tunnel);

		tunnel.argv = argv;
		tunnel.use_shell = 1;
		tunnel.in = -1;
		tunnel.out = -1;
		if (start_command(&tunnel))
			die("cannot start proxy %s", argv[0]);

		imap->buf.sock.fd[0] = tunnel.out;
		imap->buf.sock.fd[1] = tunnel.in;

		imap_info("ok\n");
	} else {
