static void remove_lock_file_on_signal(int signo)
{
	remove_lock_file();
	sigchain_pop(signo);
	raise(signo);
}