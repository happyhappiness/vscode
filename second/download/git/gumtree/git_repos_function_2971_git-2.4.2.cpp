void diff_no_index(struct rev_info *revs,
		   int argc, const char **argv,
		   const char *prefix)
{
	int i, prefixlen;
	const char *paths[2];
	struct strbuf replacement = STRBUF_INIT;

	diff_setup(&revs->diffopt);
	for (i = 1; i < argc - 2; ) {
		int j;
		if (!strcmp(argv[i], "--no-index"))
			i++;
		else if (!strcmp(argv[i], "--"))
			i++;
		else {
			j = diff_opt_parse(&revs->diffopt, argv + i, argc - i);
			if (j <= 0)
				die("invalid diff option/value: %s", argv[i]);
			i += j;
		}
	}

	prefixlen = prefix ? strlen(prefix) : 0;
	for (i = 0; i < 2; i++) {
		const char *p = argv[argc - 2 + i];
		if (!strcmp(p, "-"))
			/*
			 * stdin should be spelled as "-"; if you have
			 * path that is "-", spell it as "./-".
			 */
			p = file_from_standard_input;
		else if (prefixlen)
			p = xstrdup(prefix_filename(prefix, prefixlen, p));
		paths[i] = p;
	}

	fixup_paths(paths, &replacement);

	revs->diffopt.skip_stat_unmatch = 1;
	if (!revs->diffopt.output_format)
		revs->diffopt.output_format = DIFF_FORMAT_PATCH;

	DIFF_OPT_SET(&revs->diffopt, NO_INDEX);

	revs->max_count = -2;
	diff_setup_done(&revs->diffopt);

	setup_diff_pager(&revs->diffopt);
	DIFF_OPT_SET(&revs->diffopt, EXIT_WITH_STATUS);

	if (queue_diff(&revs->diffopt, paths[0], paths[1]))
		exit(1);
	diff_set_mnemonic_prefix(&revs->diffopt, "1/", "2/");
	diffcore_std(&revs->diffopt);
	diff_flush(&revs->diffopt);

	strbuf_release(&replacement);

	/*
	 * The return code for --no-index imitates diff(1):
	 * 0 = no changes, 1 = changes, else error
	 */
	exit(diff_result_code(&revs->diffopt, 0));
}