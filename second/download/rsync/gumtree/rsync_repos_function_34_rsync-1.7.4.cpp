static void check_timeout(void)
{
	time_t t;
	
	if (!io_timeout) return;

	if (!last_io) {
		last_io = time(NULL);
		return;
	}

	t = time(NULL);

	if (last_io && io_timeout && (t-last_io)>io_timeout) {
		fprintf(FERROR,"read timeout after %d second - exiting\n", 
			(int)(t-last_io));
		exit_cleanup(1);
	}
}