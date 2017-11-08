void show_progress(OFF_T ofs, OFF_T size)
{
	extern int am_server;
	struct timeval now;

	if (!start_time.tv_sec) {
		gettimeofday(&now, NULL);
		start_time.tv_sec = now.tv_sec;
		start_time.tv_usec = now.tv_usec;
		start_ofs = ofs;
		if (am_server)
			return;
	}
	else {
		if (am_server)
			return;
		gettimeofday(&now, NULL);
	}

	if (ofs > last_ofs + 1000 && msdiff(&print_time, &now) > 250) {
		rprint_progress(ofs, size, &now, False);
		last_ofs = ofs;
		print_time.tv_sec = now.tv_sec;
		print_time.tv_usec = now.tv_usec;
	}
}