	strcpy(symmetric, sha1_to_hex(ours->object.sha1));
	strcpy(symmetric + 40, "...");
	strcpy(symmetric + 43, sha1_to_hex(theirs->object.sha1));

	init_revisions(&revs, NULL);
	setup_revisions(rev_argc, rev_argv, &revs, NULL);
	prepare_revision_walk(&revs);

	/* ... and count the commits on each side. */
	*num_ours = 0;
	*num_theirs = 0;
	while (1) {
		struct commit *c = get_revision(&revs);
