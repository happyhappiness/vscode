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

	/* order paths according to diffcore_order */
	if (opt->orderfile && num_paths) {
		struct obj_order *o;

		o = xmalloc(sizeof(*o) * num_paths);
		for (i = 0, p = paths; p; p = p->next, i++)
			o[i].obj = p;
		order_objects(opt->orderfile, path_path, o, num_paths);
		for (i = 0; i < num_paths - 1; i++) {
			p = o[i].obj;
			p->next = o[i+1].obj;
		}

		p = o[num_paths-1].obj;
		p->next = NULL;
		paths = o[0].obj;
		free(o);
	}


	if (num_paths) {
		if (opt->output_format & (DIFF_FORMAT_RAW |
					  DIFF_FORMAT_NAME |
					  DIFF_FORMAT_NAME_STATUS)) {
			for (p = paths; p; p = p->next)
				show_raw_diff(p, num_parent, rev);
			needsep = 1;
		}
		else if (opt->output_format &
			 (DIFF_FORMAT_NUMSTAT|DIFF_FORMAT_DIFFSTAT))
			needsep = 1;
		else if (opt->output_format & DIFF_FORMAT_CALLBACK)
			handle_combined_callback(opt, paths, num_parent, num_paths);

		if (opt->output_format & DIFF_FORMAT_PATCH) {
			if (needsep)
				printf("%s%c", diff_line_prefix(opt),
				       opt->line_termination);
			for (p = paths; p; p = p->next)
				show_patch_diff(p, num_parent, dense,
						0, rev);
		}
	}

	/* Clean things up */
	while (paths) {
		struct combine_diff_path *tmp = paths;
		paths = paths->next;
		free(tmp);
	}

	free_pathspec(&diffopts.pathspec);
}