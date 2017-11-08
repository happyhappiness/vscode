void wait_process(pid_t pid, int *status)
{
	pid_t waited_pid;
	int cnt;

	while ((waited_pid = waitpid(pid, status, WNOHANG)) == 0) {
		msleep(20);
		io_flush(FULL_FLUSH);
	}

	if (waited_pid == -1 && errno == ECHILD) {
		/* status of requested child no longer available.
		 * check to see if it was processed by the sigchld_handler.
		 */
		for (cnt = 0;  cnt < MAXCHILDPROCS; cnt++) {
			if (pid == pid_stat_table[cnt].pid) {
				*status = pid_stat_table[cnt].status;
				pid_stat_table[cnt].pid = 0;
				break;
			}
		}
	}

	/* TODO: If the child exited on a signal, then log an
	 * appropriate error message.  Perhaps we should also accept a
	 * message describing the purpose of the child.  Also indicate
	 * this to the caller so that thhey know something went
	 * wrong.  */
	*status = WEXITSTATUS(*status);
}