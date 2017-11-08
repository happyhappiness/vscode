static int mark_uninteresting(const char *refname, const struct object_id *oid,
			      int flags, void *cb_data)
{
	struct commit *commit = lookup_commit_reference_gently(oid, 1);
	if (!commit)
		return 0;
	commit->object.flags |= UNINTERESTING;
	mark_parents_uninteresting(commit);
	return 0;
}