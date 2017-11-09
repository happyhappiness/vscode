static void abort_commit(struct commit_list *remoteheads, const char *err_msg)
{
	if (err_msg)
		error("%s", err_msg);
	fprintf(stderr,
		_("Not committing merge; use 'git commit' to complete the merge.\n"));
	write_merge_state(remoteheads);
	exit(1);
}