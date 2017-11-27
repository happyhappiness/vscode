static void sig_int_term_handler (int signo)
{
	++loop;
	return;
}