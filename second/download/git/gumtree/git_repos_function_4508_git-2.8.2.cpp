static void add_one_commit(unsigned char *sha1, struct rev_collect *revs)
{
	struct commit *commit;

	if (is_null_sha1(sha1))
		return;

	commit = lookup_commit(sha1);
	if (!commit ||
	    (commit->object.flags & TMP_MARK) ||
	    parse_commit(commit))
		return;

	ALLOC_GROW(revs->commit, revs->nr + 1, revs->alloc);
	revs->commit[revs->nr++] = commit;
	commit->object.flags |= TMP_MARK;
}