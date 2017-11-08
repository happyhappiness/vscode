static void cleanup_children_on_signal(int sig)
{
	cleanup_children(sig);
	sigchain_pop(sig);
	raise(sig);
}