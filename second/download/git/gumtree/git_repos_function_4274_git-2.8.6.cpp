static void process_log_file(void)
{
	struct stat st;
	if (!fstat(get_lock_file_fd(&log_lock), &st) && st.st_size)
		commit_lock_file(&log_lock);
	else
		rollback_lock_file(&log_lock);
}