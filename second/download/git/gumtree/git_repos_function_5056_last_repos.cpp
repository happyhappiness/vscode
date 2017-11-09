static void process_log_file_on_signal(int signo)
{
	process_log_file();
	sigchain_pop(signo);
	raise(signo);
}