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
			const char *name = (const char *)merge_rr.items[i].util;
			diff_two(rerere_path(name, "preimage"), path, path, path);
		}
	} else
		usage_with_options(rerere_usage, options);

	string_list_clear(&merge_rr, 1);
	return 0;
}
