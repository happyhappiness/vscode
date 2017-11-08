void sig_int(void)
{
	exit_cleanup(RERR_SIGNAL);
}