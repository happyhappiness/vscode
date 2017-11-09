static void unlock_pack_on_signal(int signo)
{
	unlock_pack();
	sigchain_pop(signo);
	raise(signo);
}