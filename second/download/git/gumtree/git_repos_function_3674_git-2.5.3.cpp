static void remove_temporary_shallow_on_signal(int signo)
{
	remove_temporary_shallow();
	sigchain_pop(signo);
	raise(signo);
}