int cmd_upload_archive_writer(int argc, const char **argv, const char *prefix)
{
	struct argv_array sent_argv = ARGV_ARRAY_INIT;
	const char *arg_cmd = "argument ";

	if (argc != 2)
		usage(upload_archive_usage);

	if (!enter_repo(argv[1], 0))
		die("'%s' does not appear to be a git repository", argv[1]);

	/* put received options in sent_argv[] */
	argv_array_push(&sent_argv, "git-upload-archive");
	for (;;) {
		char *buf = packet_read_line(0, NULL);
		if (!buf)
			break;	/* got a flush */
		if (sent_argv.argc > MAX_ARGS)
			die("Too many options (>%d)", MAX_ARGS - 1);

		if (!starts_with(buf, arg_cmd))
			die("'argument' token or flush expected");
		argv_array_push(&sent_argv, buf + strlen(arg_cmd));
	}

	/* parse all options sent by the client */
	return write_archive(sent_argv.argc, sent_argv.argv, prefix, 0, NULL, 1);
}