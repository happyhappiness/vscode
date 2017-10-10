
	if (argc)
		usage_with_options(imap_send_usage, imap_send_options);

#ifndef USE_CURL_FOR_IMAP_SEND
	if (use_curl) {
		warning("--curl not supported in this build");
		use_curl = 0;
	}
#elif defined(NO_OPENSSL)
	if (!use_curl) {
		warning("--no-curl not supported in this build");
		use_curl = 1;
	}
#endif

	if (!server.port)
		server.port = server.use_ssl ? 993 : 143;

	if (!server.folder) {
