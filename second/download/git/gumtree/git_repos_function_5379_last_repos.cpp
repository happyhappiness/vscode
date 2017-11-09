static int keep_entry(struct commit **it, struct object_id *oid)
{
	struct commit *commit;

	if (is_null_oid(oid))
		return 1;
	commit = lookup_commit_reference_gently(oid, 1);
	if (!commit)
		return 0;

	/*
	 * Make sure everything in this commit exists.
	 *
	 * We have walked all the objects reachable from the refs
	 * and cache earlier.  The commits reachable by this commit
	 * must meet SEEN commits -- and then we should mark them as
	 * SEEN as well.
	 */
	if (!commit_is_complete(commit))
		return 0;
	*it = commit;
	return 1;
}