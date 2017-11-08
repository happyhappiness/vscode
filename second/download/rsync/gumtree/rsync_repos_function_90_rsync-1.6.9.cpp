void exit_cleanup(int code)
{
	if (cleanup_fname)
		unlink(cleanup_fname);
	signal(SIGUSR1, SIG_IGN);
	if (code) {
#ifdef GETPGRP_VOID
		kill(-getpgrp(), SIGUSR1);
#else
		kill(-getpgrp(getpid()), SIGUSR1);
#endif
	}
	exit(code);
}