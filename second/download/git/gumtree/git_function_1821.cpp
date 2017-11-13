int main(int argc, char **argv)
{
	struct strbuf all_msgs = STRBUF_INIT;
	int total;
	int nongit_ok;

	git_extract_argv0_path(argv[0]);

	git_setup_gettext();

	setup_git_directory_gently(&nongit_ok);
	git_imap_config();

	argc = parse_options(argc, (const char **)argv, "", imap_send_options, imap_send_usage, 0);

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

	if (server.tunnel)
		return append_msgs_to_imap(&server, &all_msgs, total);

#ifdef USE_CURL_FOR_IMAP_SEND
	if (use_curl)
		return curl_append_msgs_to_imap(&server, &all_msgs, total);
#endif

	return append_msgs_to_imap(&server, &all_msgs, total);
}