static void add_one_commit(struct object_id *oid, struct rev_collect *revs)
{
	struct commit *commit;

	if (is_null_oid(oid))
		return;

	commit = lookup_commit(oid);
	if (!commit ||
	    (commit->object.flags & TMP_MARK) ||
	    parse_commit(commit))
		return;

	ALLOC_GROW(revs->commit, revs->nr + 1, revs->alloc);
	revs->commit[revs->nr++] = commit;
	commit->object.flags |= TMP_MARK;
}