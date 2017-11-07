static int mark_complete(const char *path, const unsigned char *sha1, int flag, void *cb_data)
{
	struct commit *commit = lookup_commit_reference_gently(sha1, 1);
	if (commit) {
		commit->object.flags |= COMPLETE;
		commit_list_insert_by_date(commit, &complete);
	}
	return 0;
}