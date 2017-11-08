static void remove_pidfile_on_signal(int signo)
{
	remove_pidfile();
	sigchain_pop(signo);
	raise(signo);
}