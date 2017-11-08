static void remove_temporary_sharedindex_on_signal(int signo)
{
	remove_temporary_sharedindex();
	sigchain_pop(signo);
	raise(signo);
}