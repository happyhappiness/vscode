int commit_lock_file(struct lock_file *lk)
{
	char result_file[PATH_MAX];
	size_t i;
	if (lk->fd >= 0 && close_lock_file(lk))
		return -1;
	strcpy(result_file, lk->filename);
	i = strlen(result_file) - 5; /* .lock */
	result_file[i] = 0;
	if (rename(lk->filename, result_file))
		return -1;
	lk->filename[0] = 0;
	return 0;
}