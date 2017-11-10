int cmd_rerere(int argc, const char **argv, const char *prefix)
{
	struct string_list merge_rr = STRING_LIST_INIT_DUP;
	int i, autoupdate = -1, flags = 0;

	struct option options[] = {
		OPT_SET_INT(0, "rerere-autoupdate", &autoupdate,
			N_("register clean resolutions in index"), 1),
		OPT_END(),
	};

	argc = parse_options(argc, argv, prefix, options, rerere_usage, 0);

	git_config(git_xmerge_config, NULL);

	if (autoupdate == 1)
		flags = RERERE_AUTOUPDATE;
	if (autoupdate == 0)
		flags = RERERE_NOAUTOUPDATE;

	if (argc < 1)
		return rerere(flags);

	if (!strcmp(argv[0], "forget")) {
		struct pathspec pathspec;
		if (argc < 2)
			warning("'git rerere forget' without paths is deprecated");
		parse_pathspec(&pathspec, 0, PATHSPEC_PREFER_CWD,
			       prefix, argv + 1);
		return rerere_forget(&pathspec);
	}

	if (!strcmp(argv[0], "clear")) {
		rerere_clear(&merge_rr);
	} else if (!strcmp(argv[0], "gc"))
		rerere_gc(&merge_rr);
	else if (!strcmp(argv[0], "status")) {
		if (setup_rerere(&merge_rr, flags | RERERE_READONLY) < 0)
			return 0;
		for (i = 0; i < merge_rr.nr; i++)
			printf("%s\n", merge_rr.items[i].string);
	} else if (!strcmp(argv[0], "remaining")) {
		rerere_remaining(&merge_rr);
		for (i = 0; i < merge_rr.nr; i++) {
			if (merge_rr.items[i].util != RERERE_RESOLVED)
				printf("%s\n", merge_rr.items[i].string);
			else
				/* prepare for later call to
				 * string_list_clear() */
				merge_rr.items[i].util = NULL;
		}
	} else if (!strcmp(argv[0], "diff")) {
		if (setup_rerere(&merge_rr, flags | RERERE_READONLY) < 0)
			return 0;
		for (i = 0; i < merge_rr.nr; i++) {
			const char *path = merge_rr.items[i].string;
			const struct rerere_id *id = merge_rr.items[i].util;
			if (diff_two(rerere_path(id, "preimage"), path, path, path))
				die("unable to generate diff for %s", rerere_path(id, NULL));
		}
	} else
		usage_with_options(rerere_usage, options);

	string_list_clear(&merge_rr, 1);
	return 0;
}