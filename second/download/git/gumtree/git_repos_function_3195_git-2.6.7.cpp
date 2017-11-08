static void remove_tempfiles(int skip_fclose)
{
	pid_t me = getpid();

	while (tempfile_list) {
		if (tempfile_list->owner == me) {
			/* fclose() is not safe to call in a signal handler */
			if (skip_fclose)
				tempfile_list->fp = NULL;
			delete_tempfile(tempfile_list);
		}
		tempfile_list = tempfile_list->next;
	}
}