static void process_log_file_at_exit(void)
{
	fflush(stderr);
	process_log_file();
}