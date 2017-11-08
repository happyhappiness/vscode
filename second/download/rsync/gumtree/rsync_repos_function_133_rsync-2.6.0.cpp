void end_progress(OFF_T size)
{
	extern int am_server;

	if (!am_server) {
		struct timeval now;
		gettimeofday(&now, NULL);
		rprint_progress(size, size, &now, True);
	}
	last_ofs = 0;
	start_ofs = 0;
	print_time.tv_sec = print_time.tv_usec = 0;
	start_time.tv_sec = start_time.tv_usec = 0;
}