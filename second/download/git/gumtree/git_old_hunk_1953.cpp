	if (!delete && !rename && !edit_description && !new_upstream && !unset_upstream && argc == 0)
		list = 1;

	if (with_commit || merge_filter != NO_FILTER)
		list = 1;

	if (!!delete + !!rename + !!force_create + !!new_upstream +
	    list + unset_upstream > 1)
		usage_with_options(builtin_branch_usage, options);

	if (abbrev == -1)
		abbrev = DEFAULT_ABBREV;
	finalize_colopts(&colopts, -1);
	if (verbose) {
		if (explicitly_enable_column(colopts))
			die(_("--column and --verbose are incompatible"));
		colopts = 0;
	}

	if (delete) {
		if (!argc)
			die(_("branch name required"));
		return delete_branches(argc, argv, delete > 1, kinds, quiet);
	} else if (list) {
		int ret = print_ref_list(kinds, detached, verbose, abbrev,
