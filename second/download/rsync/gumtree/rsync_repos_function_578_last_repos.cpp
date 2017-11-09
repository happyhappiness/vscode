static void wait_process_with_flush(pid_t pid, int *exit_code_ptr)
{
	pid_t waited_pid;
	int status;

	while ((waited_pid = wait_process(pid, &status, WNOHANG)) == 0) {
		msleep(20);
		io_flush(FULL_FLUSH);
	}

	/* TODO: If the child exited on a signal, then log an
	 * appropriate error message.  Perhaps we should also accept a
	 * message describing the purpose of the child.  Also indicate
	 * this to the caller so that they know something went wrong. */
	if (waited_pid < 0) {
		rsyserr(FERROR, errno, "waitpid");
		*exit_code_ptr = RERR_WAITCHILD;
	} else if (!WIFEXITED(status)) {
#ifdef WCOREDUMP
		if (WCOREDUMP(status))
			*exit_code_ptr = RERR_CRASHED;
		else
#endif
		if (WIFSIGNALED(status))
			*exit_code_ptr = RERR_TERMINATED;
		else
			*exit_code_ptr = RERR_WAITCHILD;
	} else
		*exit_code_ptr = WEXITSTATUS(status);
}