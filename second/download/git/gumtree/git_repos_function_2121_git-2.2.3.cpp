static void check_pipe(int err)
{
	if (err == EPIPE) {
		signal(SIGPIPE, SIG_DFL);
		raise(SIGPIPE);
		/* Should never happen, but just in case... */
		exit(141);
	}
}