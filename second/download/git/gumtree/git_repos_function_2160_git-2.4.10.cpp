static void remove_lock_files(int skip_fclose)
{
	pid_t me = getpid();

	while (lock_file_list) {
		if (lock_file_list->owner == me) {
			/* fclose() is not safe to call in a signal handler */
			if (skip_fclose)
				lock_file_list->fp = NULL;
			rollback_lock_file(lock_file_list);
		}
		lock_file_list = lock_file_list->next;
	}
}