{
	struct combine_diff_path *path = (struct combine_diff_path *)obj;

	return path->path;
}

void diff_tree_combined(const unsigned char *sha1,
			const struct sha1_array *parents,
			int dense,
			struct rev_info *rev)
{
	struct diff_options *opt = &rev->diffopt;
	struct diff_options diffopts;
	struct combine_diff_path *p, *paths = NULL;
	int i, num_paths, needsep, show_log_first, num_parent = parents->nr;

	diffopts = *opt;
	copy_pathspec(&diffopts.pathspec, &opt->pathspec);
	diffopts.output_format = DIFF_FORMAT_NO_OUTPUT;
	DIFF_OPT_SET(&diffopts, RECURSIVE);
	DIFF_OPT_CLR(&diffopts, ALLOW_EXTERNAL);
	/* tell diff_tree to emit paths in sorted (=tree) order */
	diffopts.orderfile = NULL;

	show_log_first = !!rev->loginfo && !rev->no_commit_id;
	needsep = 0;
	/* find set of paths that everybody touches */
	for (i = 0; i < num_parent; i++) {
		/* show stat against the first parent even
		 * when doing combined diff.
		 */
		int stat_opt = (opt->output_format &
				(DIFF_FORMAT_NUMSTAT|DIFF_FORMAT_DIFFSTAT));
		if (i == 0 && stat_opt)
			diffopts.output_format = stat_opt;
		else
			diffopts.output_format = DIFF_FORMAT_NO_OUTPUT;
		diff_tree_sha1(parents->sha1[i], sha1, "", &diffopts);
		diffcore_std(&diffopts);
		paths = intersect_paths(paths, i, num_parent);

		if (show_log_first && i == 0) {
			show_log(rev);

			if (rev->verbose_header && opt->output_format &&
			    opt->output_format != DIFF_FORMAT_NO_OUTPUT)
				printf("%s%c", diff_line_prefix(opt),
				       opt->line_termination);
		}

		/* if showing diff, show it in requested order */
		if (diffopts.output_format != DIFF_FORMAT_NO_OUTPUT &&
		    opt->orderfile) {
			diffcore_order(opt->orderfile);
		}

		diff_flush(&diffopts);
	}

	/* find out number of surviving paths */
	for (num_paths = 0, p = paths; p; p = p->next)
		num_paths++;

