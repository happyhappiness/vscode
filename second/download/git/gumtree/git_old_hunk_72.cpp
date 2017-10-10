
	revs.disable_stdin = 1;
	setup_revisions(argc, argv, &revs, NULL);
	memset(&sb, 0, sizeof(sb));

	sb.revs = &revs;
	if (!reverse)
		final_commit_name = prepare_final(&sb);
	else if (contents_from)
		die("--contents and --children do not blend well.");
	else
		final_commit_name = prepare_initial(&sb);

	if (!sb.final) {
		/*
		 * "--not A B -- path" without anything positive;
		 * do not default to HEAD, but use the working tree
		 * or "--contents".
