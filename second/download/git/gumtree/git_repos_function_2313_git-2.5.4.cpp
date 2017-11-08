static void cleanup_socket_on_signal(int sig)
{
	cleanup_socket();
	sigchain_pop(sig);
	raise(sig);
}