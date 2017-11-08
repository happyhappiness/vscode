static void wait_for_pager_signal(int signo)
{
	wait_for_pager();
	sigchain_pop(signo);
	raise(signo);
}