static void startup_threads(int number_to_start)
{
    int i;

    for (i = 0; number_to_start && i < ap_thread_limit; ++i) {
	if (ap_scoreboard_image->servers[0][i].tid) {
	    continue;
	}
	if (make_worker(i) < 0) {
	    break;
	}
	--number_to_start;
    }
}