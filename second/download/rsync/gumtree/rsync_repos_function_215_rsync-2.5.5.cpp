void show_progress(OFF_T ofs, OFF_T size)
{
	extern int do_progress, am_server;
        struct timeval now;

        gettimeofday(&now, NULL);

        if (!start_time.tv_sec && !start_time.tv_usec) {
        	start_time.tv_sec  = now.tv_sec;
                start_time.tv_usec = now.tv_usec;
                start_ofs          = ofs;
        }

	if (do_progress
            && !am_server
            && ofs > last_ofs + 1000
            && msdiff(&print_time, &now) > 250) {
        	rprint_progress(ofs, size, &now, False);
                last_ofs = ofs;
                print_time.tv_sec  = now.tv_sec;
                print_time.tv_usec = now.tv_usec;
	}
}