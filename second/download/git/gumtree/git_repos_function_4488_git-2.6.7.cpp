static int handle_fork_point(int argc, const char **argv)
{
	unsigned char sha1[20];
	char *refname;
	const char *commitname;
	struct rev_collect revs;
	struct commit *derived;
	struct commit_list *bases;
	int i, ret = 0;

	switch (dwim_ref(argv[0], strlen(argv[0]), sha1, &refname)) {
	case 0:
		die("No such ref: '%s'", argv[0]);
	case 1:
		break; /* good */
	default:
		die("Ambiguous refname: '%s'", argv[0]);
	}

	commitname = (argc == 2) ? argv[1] : "HEAD";
	if (get_sha1(commitname, sha1))
		die("Not a valid object name: '%s'", commitname);

	derived = lookup_commit_reference(sha1);
	memset(&revs, 0, sizeof(revs));
	revs.initial = 1;
	for_each_reflog_ent(refname, collect_one_reflog_ent, &revs);

	for (i = 0; i < revs.nr; i++)
		revs.commit[i]->object.flags &= ~TMP_MARK;

	bases = get_merge_bases_many_dirty(derived, revs.nr, revs.commit);

	/*
	 * There should be one and only one merge base, when we found
	 * a common ancestor among reflog entries.
	 */
	if (!bases || bases->next) {
		ret = 1;
		goto cleanup_return;
	}

	/* And the found one must be one of the reflog entries */
	for (i = 0; i < revs.nr; i++)
		if (&bases->item->object == &revs.commit[i]->object)
			break; /* found */
	if (revs.nr <= i) {
		ret = 1; /* not found */
		goto cleanup_return;
	}

	printf("%s\n", sha1_to_hex(bases->item->object.sha1));

cleanup_return:
	free_commit_list(bases);
	return ret;
}