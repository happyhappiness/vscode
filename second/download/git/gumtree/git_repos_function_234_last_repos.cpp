void diff_tree_combined(const struct object_id *oid,
			const struct oid_array *parents,
			int dense,
			struct rev_info *rev)
{
	struct diff_options *opt = &rev->diffopt;
	struct diff_options diffopts;
	struct combine_diff_path *p, *paths;
	int i, num_paths, needsep, show_log_first, num_parent = parents->nr;
	int need_generic_pathscan;

	/* nothing to do, if no parents */
	if (!num_parent)
		return;

	show_log_first = !!rev->loginfo && !rev->no_commit_id;
	needsep = 0;
	if (show_log_first) {
		show_log(rev);

		if (rev->verbose_header && opt->output_format &&
		    opt->output_format != DIFF_FORMAT_NO_OUTPUT &&
		    !commit_format_is_empty(rev->commit_format))
			printf("%s%c", diff_line_prefix(opt),
			       opt->line_termination);
	}

	diffopts = *opt;
	copy_pathspec(&diffopts.pathspec, &opt->pathspec);
	DIFF_OPT_SET(&diffopts, RECURSIVE);
	DIFF_OPT_CLR(&diffopts, ALLOW_EXTERNAL);

	/* find set of paths that everybody touches
	 *
	 * NOTE
	 *
	 * Diffcore transformations are bound to diff_filespec and logic
	 * comparing two entries - i.e. they do not apply directly to combine
	 * diff.
	 *
	 * If some of such transformations is requested - we launch generic
	 * path scanning, which works significantly slower compared to
	 * simultaneous all-trees-in-one-go scan in find_paths_multitree().
	 *
	 * TODO some of the filters could be ported to work on
	 * combine_diff_paths - i.e. all functionality that skips paths, so in
	 * theory, we could end up having only multitree path scanning.
	 *
	 * NOTE please keep this semantically in sync with diffcore_std()
	 */
	need_generic_pathscan = opt->skip_stat_unmatch	||
			DIFF_OPT_TST(opt, FOLLOW_RENAMES)	||
			opt->break_opt != -1	||
			opt->detect_rename	||
			opt->pickaxe		||
			opt->filter;


	if (need_generic_pathscan) {
		/*
		 * NOTE generic case also handles --stat, as it computes
		 * diff(sha1,parent_i) for all i to do the job, specifically
		 * for parent0.
		 */
		paths = find_paths_generic(oid, parents, &diffopts);
	}
	else {
		int stat_opt;
		paths = find_paths_multitree(oid, parents, &diffopts);

		/*
		 * show stat against the first parent even
		 * when doing combined diff.
		 */
		stat_opt = (opt->output_format &
				(DIFF_FORMAT_NUMSTAT|DIFF_FORMAT_DIFFSTAT));
		if (stat_opt) {
			diffopts.output_format = stat_opt;

			diff_tree_oid(&parents->oid[0], oid, "", &diffopts);
			diffcore_std(&diffopts);
			if (opt->orderfile)
				diffcore_order(opt->orderfile);
			diff_flush(&diffopts);
		}
	}

	/* find out number of surviving paths */
	for (num_paths = 0, p = paths; p; p = p->next)
		num_paths++;

	/* order paths according to diffcore_order */
	if (opt->orderfile && num_paths) {
		struct obj_order *o;

		ALLOC_ARRAY(o, num_paths);
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

	clear_pathspec(&diffopts.pathspec);
}