static int diff_tree_commit_sha1(const struct object_id *oid)
{
	struct commit *commit = lookup_commit_reference(oid->hash);
	if (!commit)
		return -1;
	return log_tree_commit(&log_tree_opt, commit);
}