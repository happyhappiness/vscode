static void remove_lock_file(void)
{
	pid_t me = getpid();

	while (lock_file_list) {
		if (lock_file_list->owner == me &&
		    lock_file_list->filename[0]) {
			if (lock_file_list->fd >= 0)
				close(lock_file_list->fd);
			unlink_or_warn(lock_file_list->filename);
		}
		lock_file_list = lock_file_list->next;
	}
}