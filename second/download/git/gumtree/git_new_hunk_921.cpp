	struct commit **commit;
	int nr;
	int alloc;
	unsigned int initial : 1;
};

static void add_one_commit(struct object_id *oid, struct rev_collect *revs)
{
	struct commit *commit;

	if (is_null_oid(oid))
		return;

	commit = lookup_commit(oid->hash);
	if (!commit ||
	    (commit->object.flags & TMP_MARK) ||
	    parse_commit(commit))
		return;

	ALLOC_GROW(revs->commit, revs->nr + 1, revs->alloc);
	revs->commit[revs->nr++] = commit;
	commit->object.flags |= TMP_MARK;
}

static int collect_one_reflog_ent(struct object_id *ooid, struct object_id *noid,
				  const char *ident, unsigned long timestamp,
				  int tz, const char *message, void *cbdata)
{
	struct rev_collect *revs = cbdata;

	if (revs->initial) {
		revs->initial = 0;
		add_one_commit(ooid, revs);
	}
	add_one_commit(noid, revs);
	return 0;
}

static int handle_fork_point(int argc, const char **argv)
{
	struct object_id oid;
	char *refname;
	const char *commitname;
	struct rev_collect revs;
	struct commit *derived;
	struct commit_list *bases;
	int i, ret = 0;

	switch (dwim_ref(argv[0], strlen(argv[0]), oid.hash, &refname)) {
	case 0:
		die("No such ref: '%s'", argv[0]);
	case 1:
		break; /* good */
	default:
		die("Ambiguous refname: '%s'", argv[0]);
	}

	commitname = (argc == 2) ? argv[1] : "HEAD";
	if (get_oid(commitname, &oid))
		die("Not a valid object name: '%s'", commitname);

	derived = lookup_commit_reference(oid.hash);
	memset(&revs, 0, sizeof(revs));
	revs.initial = 1;
	for_each_reflog_ent(refname, collect_one_reflog_ent, &revs);

	if (!revs.nr && !get_oid(refname, &oid))
		add_one_commit(&oid, &revs);

	for (i = 0; i < revs.nr; i++)
		revs.commit[i]->object.flags &= ~TMP_MARK;

	bases = get_merge_bases_many_dirty(derived, revs.nr, revs.commit);

