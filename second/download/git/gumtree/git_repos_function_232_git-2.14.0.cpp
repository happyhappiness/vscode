static struct combine_diff_path *find_paths_generic(const struct object_id *oid,
	const struct oid_array *parents, struct diff_options *opt)
{
	struct combine_diff_path *paths = NULL;
	int i, num_parent = parents->nr;

	int output_format = opt->output_format;
	const char *orderfile = opt->orderfile;

	opt->output_format = DIFF_FORMAT_NO_OUTPUT;
	/* tell diff_tree to emit paths in sorted (=tree) order */
	opt->orderfile = NULL;

	/* D(A,P1...Pn) = D(A,P1) ^ ... ^ D(A,Pn)  (wrt paths) */
	for (i = 0; i < num_parent; i++) {
		/*
		 * show stat against the first parent even when doing
		 * combined diff.
		 */
		int stat_opt = (output_format &
				(DIFF_FORMAT_NUMSTAT|DIFF_FORMAT_DIFFSTAT));
		if (i == 0 && stat_opt)
			opt->output_format = stat_opt;
		else
			opt->output_format = DIFF_FORMAT_NO_OUTPUT;
		diff_tree_oid(&parents->oid[i], oid, "", opt);
		diffcore_std(opt);
		paths = intersect_paths(paths, i, num_parent);

		/* if showing diff, show it in requested order */
		if (opt->output_format != DIFF_FORMAT_NO_OUTPUT &&
		    orderfile) {
			diffcore_order(orderfile);
		}

		diff_flush(opt);
	}

	opt->output_format = output_format;
	opt->orderfile = orderfile;
	return paths;
}