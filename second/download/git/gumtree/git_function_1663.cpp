int stat_tracking_info(struct branch *branch, int *num_ours, int *num_theirs)
{
	unsigned char sha1[20];
	struct commit *ours, *theirs;
	char symmetric[84];
	struct rev_info revs;
	const char *rev_argv[10], *base;
	int rev_argc;

	/* Cannot stat unless we are marked to build on top of somebody else. */
	if (!branch ||
	    !branch->merge || !branch->merge[0] || !branch->merge[0]->dst)
		return 0;

	/* Cannot stat if what we used to build on no longer exists */
	base = branch->merge[0]->dst;
	if (read_ref(base, sha1))
		return -1;
	theirs = lookup_commit_reference(sha1);
	if (!theirs)
		return -1;

	if (read_ref(branch->refname, sha1))
		return -1;
	ours = lookup_commit_reference(sha1);
	if (!ours)
		return -1;

	/* are we the same? */
	if (theirs == ours) {
		*num_theirs = *num_ours = 0;
		return 1;
	}

	/* Run "rev-list --left-right ours...theirs" internally... */
	rev_argc = 0;
	rev_argv[rev_argc++] = NULL;
	rev_argv[rev_argc++] = "--left-right";
	rev_argv[rev_argc++] = symmetric;
	rev_argv[rev_argc++] = "--";
	rev_argv[rev_argc] = NULL;

	strcpy(symmetric, sha1_to_hex(ours->object.sha1));
	strcpy(symmetric + 40, "...");
	strcpy(symmetric + 43, sha1_to_hex(theirs->object.sha1));

	init_revisions(&revs, NULL);
	setup_revisions(rev_argc, rev_argv, &revs, NULL);
	if (prepare_revision_walk(&revs))
		die("revision walk setup failed");

	/* ... and count the commits on each side. */
	*num_ours = 0;
	*num_theirs = 0;
	while (1) {
		struct commit *c = get_revision(&revs);
		if (!c)
			break;
		if (c->object.flags & SYMMETRIC_LEFT)
			(*num_ours)++;
		else
			(*num_theirs)++;
	}

	/* clear object flags smudged by the above traversal */
	clear_commit_marks(ours, ALL_REV_FLAGS);
	clear_commit_marks(theirs, ALL_REV_FLAGS);
	return 1;
}