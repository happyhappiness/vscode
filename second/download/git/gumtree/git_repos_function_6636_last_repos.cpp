static void restore_term_on_signal(int sig)
{
	restore_term();
	sigchain_pop(sig);
	raise(sig);
}