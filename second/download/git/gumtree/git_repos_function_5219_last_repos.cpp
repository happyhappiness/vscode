int cmd_show_ref(int argc, const char **argv, const char *prefix)
{
	argc = parse_options(argc, argv, prefix, show_ref_options,
			     show_ref_usage, 0);

	if (exclude_arg)
		return exclude_existing(exclude_existing_arg);

	pattern = argv;
	if (!*pattern)
		pattern = NULL;

	if (verify) {
		if (!pattern)
			die("--verify requires a reference");
		while (*pattern) {
			struct object_id oid;

			if ((starts_with(*pattern, "refs/") || !strcmp(*pattern, "HEAD")) &&
			    !read_ref(*pattern, oid.hash)) {
				show_one(*pattern, &oid);
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