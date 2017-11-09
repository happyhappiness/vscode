void show_progress(OFF_T ofs, OFF_T size)
{
	struct timeval now;
#if defined HAVE_GETPGRP && defined HAVE_TCGETPGRP
	static pid_t pgrp = -1;
	pid_t tc_pgrp;
#endif

	if (am_server)
		return;

#if defined HAVE_GETPGRP && defined HAVE_TCGETPGRP
	if (pgrp == -1)
		pgrp = getpgrp(GETPGRP_ARG);
#endif

	gettimeofday(&now, NULL);

	if (INFO_GTE(PROGRESS, 2)) {
		ofs = stats.total_transferred_size - size + ofs;
		size = stats.total_size;
	}

	if (!ph_start.time.tv_sec) {
		int i;

		/* Try to guess the real starting time when the sender started
		 * to send us data by using the time we last received some data
		 * in the last file (if it was recent enough). */
		if (msdiff(&ph_list[newest_hpos].time, &now) <= 1500) {
			ph_start.time = ph_list[newest_hpos].time;
			ph_start.ofs = 0;
		} else {
			ph_start.time.tv_sec = now.tv_sec;
			ph_start.time.tv_usec = now.tv_usec;
			ph_start.ofs = ofs;
		}

		for (i = 0; i < PROGRESS_HISTORY_SECS; i++)
			ph_list[i] = ph_start;
	}
	else {
		if (msdiff(&ph_list[newest_hpos].time, &now) < 1000)
			return;

		newest_hpos = oldest_hpos;
		oldest_hpos = (oldest_hpos + 1) % PROGRESS_HISTORY_SECS;
		ph_list[newest_hpos].time.tv_sec = now.tv_sec;
		ph_list[newest_hpos].time.tv_usec = now.tv_usec;
		ph_list[newest_hpos].ofs = ofs;
	}

#if defined HAVE_GETPGRP && defined HAVE_TCGETPGRP
	tc_pgrp = tcgetpgrp(STDOUT_FILENO);
	if (tc_pgrp != pgrp && tc_pgrp != -1)
		return;
#endif

	rprint_progress(ofs, size, &now, False);
}