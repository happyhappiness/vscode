static void remove_tempfile_on_signal(int signo)
{
	remove_tempfile();
	sigchain_pop(signo);
	raise(signo);
}