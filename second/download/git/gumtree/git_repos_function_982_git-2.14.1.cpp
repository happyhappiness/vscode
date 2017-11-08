static void atfork_parent(struct atfork_state *as)
{
#ifdef NO_PTHREADS
	if (sigprocmask(SIG_SETMASK, &as->old, NULL))
		die_errno("sigprocmask");
#else
	bug_die(pthread_setcancelstate(as->cs, NULL),
		"re-enabling cancellation");
	bug_die(pthread_sigmask(SIG_SETMASK, &as->old, NULL),
		"restoring signal mask");
#endif
}