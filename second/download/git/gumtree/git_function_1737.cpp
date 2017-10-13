int main(int argc, char **argv)
{
	struct strbuf all_msgs = STRBUF_INIT;
	struct strbuf msg = STRBUF_INIT;
	struct imap_store *ctx = NULL;
	int ofs = 0;
	int r;
	int total, n = 0;
	int nongit_ok;

	git_extract_argv0_path(argv[0]);

	git_setup_gettext();

	if (argc != 1)
		usage(imap_send_usage);

	setup_git_directory_gently(&nongit_ok);
	git_imap_config();

	if (!server.port)
		server.port = server.use_ssl ? 993 : 143;

	if (!server.folder) {
		fprintf(stderr, "no imap store specified\n");
		return 1;
	}
	if (!server.host) {
		if (!server.tunnel) {
			fprintf(stderr, "no imap host specified\n");
			return 1;
		}
		server.host = "tunnel";
	}

	/* read the messages */
	if (read_message(stdin, &all_msgs)) {
		fprintf(stderr, "error reading input\n");
		return 1;
	}

	if (all_msgs.len == 0) {
		fprintf(stderr, "nothing to send\n");
		return 1;
	}

	total = count_messages(&all_msgs);
	if (!total) {
		fprintf(stderr, "no messages to send\n");
		return 1;
	}

	/* write it to the imap server */
	ctx = imap_open_store(&server, server.folder);
	if (!ctx) {
		fprintf(stderr, "failed to open store\n");
		return 1;
	}

	fprintf(stderr, "sending %d message%s\n", total, (total != 1) ? "s" : "");
	while (1) {
		unsigned percent = n * 100 / total;

		fprintf(stderr, "%4u%% (%d/%d) done\r", percent, n, total);
		if (!split_msg(&all_msgs, &msg, &ofs))
			break;
		if (server.use_html)
			wrap_in_html(&msg);
		r = imap_store_msg(ctx, &msg);
		if (r != DRV_OK)
			break;
		n++;
	}
	fprintf(stderr, "\n");

	imap_close_store(ctx);

	return 0;
}