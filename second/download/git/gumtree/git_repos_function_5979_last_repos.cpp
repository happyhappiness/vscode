static void remove_pack_on_signal(int signo)
{
	remove_temporary_files();
	sigchain_pop(signo);
	raise(signo);
}