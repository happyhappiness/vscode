static void set_progress_signal(void)
{
	struct sigaction sa;
	struct itimerval v;

	progress_update = 0;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = progress_interval;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGALRM, &sa, NULL);

	v.it_interval.tv_sec = 1;
	v.it_interval.tv_usec = 0;
	v.it_value = v.it_interval;
	setitimer(ITIMER_REAL, &v, NULL);
}