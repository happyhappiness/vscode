static void handle_children_on_signal(int signo)
{
	kill_children(pp_for_signal, signo);
	sigchain_pop(signo);
	raise(signo);
}