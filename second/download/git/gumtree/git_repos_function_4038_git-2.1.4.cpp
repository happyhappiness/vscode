int cmd_show_ref(int argc, const char **argv, const char *prefix)
{
	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage_with_options(show_ref_usage, show_ref_options);

	argc = parse_options(argc, argv, prefix, show_ref_options,
			     show_ref_usage, PARSE_OPT_NO_INTERNAL_HELP);

	if (exclude_arg)
		return exclude_existing(exclude_existing_arg);

	pattern = argv;
	if (!*pattern)
		pattern = NULL;

	if (verify) {
		if (!pattern)
			die("--verify requires a reference");
		while (*pattern) {
			unsigned char sha1[20];

			if (starts_with(*pattern, "refs/") &&
			    !read_ref(*pattern, sha1)) {
				if (!quiet)
					show_one(*pattern, sha1);
			}
			else if (!quiet)
				die("'%s' - not a valid ref", *pattern);
			else
				return 1;
			pattern++;
		}
		return 0;
	}

	if (show_head)
		head_ref(show_ref, NULL);
	for_each_ref(show_ref, NULL);
	if (!found_match) {
		if (verify && !quiet)
			die("No match");
		return 1;
	}
	return 0;
}