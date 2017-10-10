	if (quiet)
		rev->diffopt.output_format |= DIFF_FORMAT_NO_OUTPUT;
	argc = setup_revisions(argc, argv, rev, opt);

	/* Any arguments at this point are not recognized */
	if (argc > 1)
		die("unrecognized argument: %s", argv[1]);

	memset(&w, 0, sizeof(w));
	userformat_find_requirements(NULL, &w);

	if (!rev->show_notes_given && (!rev->pretty_given || w.notes))
		rev->show_notes = 1;
