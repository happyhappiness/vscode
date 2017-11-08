int stat_tracking_info(struct branch *branch, int *num_ours, int *num_theirs,
		       const char **upstream_name)
{
	struct object_id oid;
	struct commit *ours, *theirs;
	struct rev_info revs;
	const char *base;
	struct argv_array argv = ARGV_ARRAY_INIT;

	/* Cannot stat unless we are marked to build on top of somebody else. */
	base = branch_get_upstream(branch, NULL);
	if (upstream_name)
		*upstream_name = base;
	if (!base)
		return -1;

	/* Cannot stat if what we used to build on no longer exists */
	if (read_ref(base, oid.hash))
		return -1;
	theirs = lookup_commit_reference(oid.hash);
	if (!theirs)
		return -1;

	if (read_ref(branch->refname, oid.hash))
		return -1;
	ours = lookup_commit_reference(oid.hash);
	if (!ours)
		return -1;

	/* are we the same? */
	if (theirs == ours) {
		*num_theirs = *num_ours = 0;
		return 0;
	}

	/* Run "rev-list --left-right ours...theirs" internally... */
	argv_array_push(&argv, ""); /* ignored */
	argv_array_push(&argv, "--left-right");
	argv_array_pushf(&argv, "%s...%s",
			 oid_to_hex(&ours->object.oid),
			 oid_to_hex(&theirs->object.oid));
	argv_array_push(&argv, "--");

	init_revisions(&revs, NULL);
	setup_revisions(argv.argc, argv.argv, &revs, NULL);
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

	argv_array_clear(&argv);
	return 0;
}