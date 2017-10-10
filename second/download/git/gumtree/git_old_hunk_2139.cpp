
	if (argc)
		usage_with_options(imap_send_usage, imap_send_options);

#ifndef USE_CURL_FOR_IMAP_SEND
	if (use_curl) {
		warning("--use-curl not supported in this build");
		use_curl = 0;
	}
#endif

	if (!server.port)
		server.port = server.use_ssl ? 993 : 143;

	if (!server.folder) {
