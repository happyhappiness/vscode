int cmd_mailinfo(int argc, const char **argv, const char *prefix)
{
	const char *def_charset;

	/* NEEDSWORK: might want to do the optional .git/ directory
	 * discovery
	 */
	git_config(git_mailinfo_config, NULL);

	def_charset = get_commit_output_encoding();
	metainfo_charset = def_charset;

	while (1 < argc && argv[1][0] == '-') {
		if (!strcmp(argv[1], "-k"))
			keep_subject = 1;
		else if (!strcmp(argv[1], "-b"))
			keep_non_patch_brackets_in_subject = 1;
		else if (!strcmp(argv[1], "-u"))
			metainfo_charset = def_charset;
		else if (!strcmp(argv[1], "-n"))
			metainfo_charset = NULL;
		else if (starts_with(argv[1], "--encoding="))
			metainfo_charset = argv[1] + 11;
		else if (!strcmp(argv[1], "--scissors"))
			use_scissors = 1;
		else if (!strcmp(argv[1], "--no-scissors"))
			use_scissors = 0;
		else if (!strcmp(argv[1], "--no-inbody-headers"))
			use_inbody_headers = 0;
		else
			usage(mailinfo_usage);
		argc--; argv++;
	}

	if (argc != 3)
		usage(mailinfo_usage);

	return !!mailinfo(stdin, stdout, argv[1], argv[2]);
}