static int mark_complete(const char *path, const struct object_id *oid,
			 int flag, void *cb_data)
{
	struct commit *commit = lookup_commit_reference_gently(oid, 1);

	if (commit) {
		commit->object.flags |= COMPLETE;
		commit_list_insert(commit, &complete);
	}
	return 0;
}