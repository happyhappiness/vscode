static int diff_tree_commit_sha1(const unsigned char *sha1)
{
	struct commit *commit = lookup_commit_reference(sha1);
	if (!commit)
		return -1;
	return log_tree_commit(&log_tree_opt, commit);
}