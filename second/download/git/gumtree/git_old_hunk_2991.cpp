 * Returns -1 if num_ours and num_theirs could not be filled in (e.g., no
 * upstream defined, or ref does not exist), 0 otherwise.
 */
int stat_tracking_info(struct branch *branch, int *num_ours, int *num_theirs,
		       const char **upstream_name)
{
	unsigned char sha1[20];
	struct commit *ours, *theirs;
	char symmetric[84];
	struct rev_info revs;
	const char *rev_argv[10], *base;
	int rev_argc;

	/* Cannot stat unless we are marked to build on top of somebody else. */
	base = branch_get_upstream(branch, NULL);
	if (upstream_name)
		*upstream_name = base;
	if (!base)
		return -1;

	/* Cannot stat if what we used to build on no longer exists */
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
		return 0;
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
