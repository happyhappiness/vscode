static int commit_locked_index(struct lock_file *lk)
{
	if (alternate_index_output)
		return commit_lock_file_to(lk, alternate_index_output);
	else
		return commit_lock_file(lk);
}