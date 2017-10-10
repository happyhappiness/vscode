	git_setup_gettext();

	if (argc != 1)
		usage(imap_send_usage);

	setup_git_directory_gently(&nongit_ok);
	git_config(git_imap_config, NULL);

	if (!server.port)
		server.port = server.use_ssl ? 993 : 143;

	if (!imap_folder) {
		fprintf(stderr, "no imap store specified\n");
		return 1;
	}
	if (!server.host) {
		if (!server.tunnel) {
			fprintf(stderr, "no imap host specified\n");
