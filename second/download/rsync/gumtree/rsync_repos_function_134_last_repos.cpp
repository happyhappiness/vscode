static void handle_kill_signal(BOOL flush_ok)
{
	got_kill_signal = -1;
	flush_ok_after_signal = flush_ok;
	exit_cleanup(RERR_SIGNAL);
}