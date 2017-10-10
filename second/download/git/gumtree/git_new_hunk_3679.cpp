	argc = parse_options(argc, argv, prefix, options,
			     git_notes_merge_usage, 0);

	if (strategy || do_commit + do_abort == 0)
		do_merge = 1;
	if (do_merge + do_commit + do_abort != 1) {
		error(_("cannot mix --commit, --abort or -s/--strategy"));
		usage_with_options(git_notes_merge_usage, options);
	}

	if (do_merge && argc != 1) {
		error(_("Must specify a notes ref to merge"));
		usage_with_options(git_notes_merge_usage, options);
	} else if (!do_merge && argc) {
		error(_("too many parameters"));
		usage_with_options(git_notes_merge_usage, options);
	}

	init_notes_merge_options(&o);
	o.verbosity = verbosity + NOTES_MERGE_VERBOSITY_DEFAULT;

