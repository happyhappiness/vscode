static void remove_lock_files_on_signal(int signo)
{
	remove_lock_files(1);
	sigchain_pop(signo);
	raise(signo);
}