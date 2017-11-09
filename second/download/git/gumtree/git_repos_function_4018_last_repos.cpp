static void remove_tmp_objdir_on_signal(int signo)
{
	tmp_objdir_destroy_1(the_tmp_objdir, 1);
	sigchain_pop(signo);
	raise(signo);
}