static void wait_for_pager(int in_signal)
{
	if (!in_signal) {
		fflush(stdout);
		fflush(stderr);
	}
	/* signal EOF to pager */
	close(1);
	close(2);
	if (in_signal)
		finish_command_in_signal(&pager_process);
	else
		finish_command(&pager_process);
}