static int fsck_commit(struct commit *commit, fsck_error error_func)
{
	const char *buffer = get_commit_buffer(commit, NULL);
	int ret = fsck_commit_buffer(commit, buffer, error_func);
	unuse_commit_buffer(commit, buffer);
	return ret;
}