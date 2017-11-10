static void remove_keep_on_signal(int signo)
{
	remove_keep();
	sigchain_pop(signo);
	raise(signo);
}