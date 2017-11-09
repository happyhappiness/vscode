void end_progress(OFF_T size)
{
	if (!am_server) {
		struct timeval now;
		gettimeofday(&now, NULL);
		if (INFO_GTE(PROGRESS, 2)) {
			rprint_progress(stats.total_transferred_size,
					stats.total_size, &now, True);
		} else {
			rprint_progress(size, size, &now, True);
			memset(&ph_start, 0, sizeof ph_start);
		}
	}
}