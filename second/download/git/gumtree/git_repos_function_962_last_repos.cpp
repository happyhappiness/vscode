static void cleanup_children_on_signal(int sig)
{
	cleanup_children(sig, 1);
	sigchain_pop(sig);
	raise(sig);
}