static void check_signum(int sig)
{
	if (sig < 1 || sig >= SIGCHAIN_MAX_SIGNALS)
		die("BUG: signal out of range: %d", sig);
}