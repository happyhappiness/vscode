static void wait_for_pager(void)
{
	fflush(stdout);
	fflush(stderr);
	/* signal EOF to pager */
	close(1);
	close(2);
	finish_command(&pager_process);
}