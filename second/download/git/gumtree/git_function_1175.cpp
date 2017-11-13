static void atfork_prepare(struct atfork_state *as)
{
	sigset_t all;

	if (sigfillset(&all))
		die_errno("sigfillset");
#ifdef NO_PTHREADS
	if (sigprocmask(SIG_SETMASK, &all, &as->old))
		die_errno("sigprocmask");
#else
	bug_die(pthread_sigmask(SIG_SETMASK, &all, &as->old),
		"blocking all signals");
	bug_die(pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &as->cs),
		"disabling cancellation");
#endif
}