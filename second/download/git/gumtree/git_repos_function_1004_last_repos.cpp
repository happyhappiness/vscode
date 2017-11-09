void check_pipe(int err)
{
	if (err == EPIPE) {
		if (in_async())
			async_exit(141);

		signal(SIGPIPE, SIG_DFL);
		raise(SIGPIPE);
		/* Should never happen, but just in case... */
		exit(141);
	}
}