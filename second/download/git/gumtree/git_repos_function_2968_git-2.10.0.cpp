int stop_column_filter(void)
{
	if (fd_out == -1)
		return -1;

	fflush(stdout);
	close(1);
	finish_command(&column_process);
	dup2(fd_out, 1);
	close(fd_out);
	fd_out = -1;
	return 0;
}