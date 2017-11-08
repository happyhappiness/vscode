int commit_lock_file(struct lock_file *lk)
{
	char *result_path = get_locked_file_path(lk);

	if (commit_lock_file_to(lk, result_path)) {
		int save_errno = errno;
		free(result_path);
		errno = save_errno;
		return -1;
	}
	free(result_path);
	return 0;
}