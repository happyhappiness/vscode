void line_log_init(struct rev_info *rev, const char *prefix, struct string_list *args)
{
	struct commit *commit = NULL;
	struct line_log_data *range;

	commit = check_single_commit(rev);
	range = parse_lines(commit, prefix, args);
	add_line_range(rev, commit, range);

	if (!rev->diffopt.detect_rename) {
		int i, count = 0;
		struct line_log_data *r = range;
		const char **paths;
		while (r) {
			count++;
			r = r->next;
		}
		paths = xmalloc((count+1)*sizeof(char *));
		r = range;
		for (i = 0; i < count; i++) {
			paths[i] = xstrdup(r->path);
			r = r->next;
		}
		paths[count] = NULL;
		parse_pathspec(&rev->diffopt.pathspec, 0,
			       PATHSPEC_PREFER_FULL, "", paths);
		free(paths);
	}
}