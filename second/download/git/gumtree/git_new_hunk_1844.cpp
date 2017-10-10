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
