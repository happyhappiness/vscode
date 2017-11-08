int add_files_to_cache(const char *prefix,
		       const struct pathspec *pathspec, int flags)
{
	struct update_callback_data data;
	struct rev_info rev;

	memset(&data, 0, sizeof(data));
	data.flags = flags;

	init_revisions(&rev, prefix);
	setup_revisions(0, NULL, &rev, NULL);
	if (pathspec)
		copy_pathspec(&rev.prune_data, pathspec);
	rev.diffopt.output_format = DIFF_FORMAT_CALLBACK;
	rev.diffopt.format_callback = update_callback;
	rev.diffopt.format_callback_data = &data;
	rev.max_count = 0; /* do not compare unmerged paths with stage #2 */
	run_diff_files(&rev, DIFF_RACY_IS_MODIFIED);
	return !!data.add_errors;
}