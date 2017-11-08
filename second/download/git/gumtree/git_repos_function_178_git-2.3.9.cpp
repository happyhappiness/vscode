static void show_combined_header(struct combine_diff_path *elem,
				 int num_parent,
				 int dense,
				 struct rev_info *rev,
				 const char *line_prefix,
				 int mode_differs,
				 int show_file_header)
{
	struct diff_options *opt = &rev->diffopt;
	int abbrev = DIFF_OPT_TST(opt, FULL_INDEX) ? 40 : DEFAULT_ABBREV;
	const char *a_prefix = opt->a_prefix ? opt->a_prefix : "a/";
	const char *b_prefix = opt->b_prefix ? opt->b_prefix : "b/";
	const char *c_meta = diff_get_color_opt(opt, DIFF_METAINFO);
	const char *c_reset = diff_get_color_opt(opt, DIFF_RESET);
	const char *abb;
	int added = 0;
	int deleted = 0;
	int i;

	if (rev->loginfo && !rev->no_commit_id)
		show_log(rev);

	dump_quoted_path(dense ? "diff --cc " : "diff --combined ",
			 "", elem->path, line_prefix, c_meta, c_reset);
	printf("%s%sindex ", line_prefix, c_meta);
	for (i = 0; i < num_parent; i++) {
		abb = find_unique_abbrev(elem->parent[i].sha1,
					 abbrev);
		printf("%s%s", i ? "," : "", abb);
	}
	abb = find_unique_abbrev(elem->sha1, abbrev);
	printf("..%s%s\n", abb, c_reset);

	if (mode_differs) {
		deleted = !elem->mode;

		/* We say it was added if nobody had it */
		added = !deleted;
		for (i = 0; added && i < num_parent; i++)
			if (elem->parent[i].status !=
			    DIFF_STATUS_ADDED)
				added = 0;
		if (added)
			printf("%s%snew file mode %06o",
			       line_prefix, c_meta, elem->mode);
		else {
			if (deleted)
				printf("%s%sdeleted file ",
				       line_prefix, c_meta);
			printf("mode ");
			for (i = 0; i < num_parent; i++) {
				printf("%s%06o", i ? "," : "",
				       elem->parent[i].mode);
			}
			if (elem->mode)
				printf("..%06o", elem->mode);
		}
		printf("%s\n", c_reset);
	}

	if (!show_file_header)
		return;

	if (added)
		dump_quoted_path("--- ", "", "/dev/null",
				 line_prefix, c_meta, c_reset);
	else
		dump_quoted_path("--- ", a_prefix, elem->path,
				 line_prefix, c_meta, c_reset);
	if (deleted)
		dump_quoted_path("+++ ", "", "/dev/null",
				 line_prefix, c_meta, c_reset);
	else
		dump_quoted_path("+++ ", b_prefix, elem->path,
				 line_prefix, c_meta, c_reset);
}