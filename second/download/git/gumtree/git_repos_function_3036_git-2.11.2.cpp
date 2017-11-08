void line_log_init(struct rev_info *rev, const char *prefix, struct string_list *args)
{
	struct commit *commit = NULL;
	struct line_log_data *range;

	commit = check_single_commit(rev);
	range = parse_lines(commit, prefix, args);
	add_line_range(rev, commit, range);

	if (!rev->diffopt.detect_rename) {
		struct line_log_data *r;
		struct argv_array array = ARGV_ARRAY_INIT;
		const char **paths;

		for (r = range; r; r = r->next)
			argv_array_push(&array, r->path);
		paths = argv_array_detach(&array);

		parse_pathspec(&rev->diffopt.pathspec, 0,
			       PATHSPEC_PREFER_FULL, "", paths);
		/* strings are now owned by pathspec */
		free(paths);
	}
}