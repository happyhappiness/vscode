pid_t wait_process(pid_t pid, int *status_ptr, int flags)
{
	pid_t waited_pid;

	do {
		waited_pid = waitpid(pid, status_ptr, flags);
	} while (waited_pid == -1 && errno == EINTR);

	if (waited_pid == -1 && errno == ECHILD) {
		/* Status of requested child no longer available:  check to
		 * see if it was processed by remember_children(). */
		int cnt;
		for (cnt = 0; cnt < MAXCHILDPROCS; cnt++) {
			if (pid == pid_stat_table[cnt].pid) {
				*status_ptr = pid_stat_table[cnt].status;
				pid_stat_table[cnt].pid = 0;
				return pid;
			}
		}
	}

	return waited_pid;
}