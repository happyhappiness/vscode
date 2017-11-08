static int builtin_diff_files(struct rev_info *revs, int argc, const char **argv)
{
	unsigned int options = 0;

	while (1 < argc && argv[1][0] == '-') {
		if (!strcmp(argv[1], "--base"))
			revs->max_count = 1;
		else if (!strcmp(argv[1], "--ours"))
			revs->max_count = 2;
		else if (!strcmp(argv[1], "--theirs"))
			revs->max_count = 3;
		else if (!strcmp(argv[1], "-q"))
			options |= DIFF_SILENT_ON_REMOVED;
		else if (!strcmp(argv[1], "-h"))
			usage(builtin_diff_usage);
		else
			return error(_("invalid option: %s"), argv[1]);
		argv++; argc--;
	}

	/*
	 * "diff --base" should not combine merges because it was not
	 * asked to.  "diff -c" should not densify (if the user wants
	 * dense one, --cc can be explicitly asked for, or just rely
	 * on the default).
	 */
	if (revs->max_count == -1 && !revs->combine_merges &&
	    (revs->diffopt.output_format & DIFF_FORMAT_PATCH))
		revs->combine_merges = revs->dense_combined_merges = 1;

	setup_work_tree();
	if (read_cache_preload(&revs->diffopt.pathspec) < 0) {
		perror("read_cache_preload");
		return -1;
	}
	return run_diff_files(revs, options);
}