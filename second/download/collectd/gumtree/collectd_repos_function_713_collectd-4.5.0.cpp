static void sig_hup_handler (int signo)
{
	++restart;
	return;
}