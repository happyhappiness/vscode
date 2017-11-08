void setup_pager(void)
{
	const char *pager = git_pager(isatty(1));

	if (!pager)
		return;

	/*
	 * force computing the width of the terminal before we redirect
	 * the standard output to the pager.
	 */
	(void) term_columns();

	setenv("GIT_PAGER_IN_USE", "true", 1);

	/* spawn the pager */
	pager_argv[0] = pager;
	pager_process.use_shell = 1;
	pager_process.argv = pager_argv;
	pager_process.in = -1;
	if (!getenv("LESS") || !getenv("LV")) {
		static const char *env[3];
		int i = 0;

		if (!getenv("LESS"))
			env[i++] = "LESS=FRX";
		if (!getenv("LV"))
			env[i++] = "LV=-c";
		env[i] = NULL;
		pager_process.env = env;
	}
	if (start_command(&pager_process))
		return;

	/* original process continues, but writes to the pipe */
	dup2(pager_process.in, 1);
	if (isatty(2))
		dup2(pager_process.in, 2);
	close(pager_process.in);

	/* this makes sure that the parent terminates after the pager */
	sigchain_push_common(wait_for_pager_signal);
	atexit(wait_for_pager);
}