static int run_argv(int *argcp, const char ***argv)
{
	int done_alias = 0;

	while (1) {
		/*
		 * If we tried alias and futzed with our environment,
		 * it no longer is safe to invoke builtins directly in
		 * general.  We have to spawn them as dashed externals.
		 *
		 * NEEDSWORK: if we can figure out cases
		 * where it is safe to do, we can avoid spawning a new
		 * process.
		 */
		if (!done_alias)
			handle_builtin(*argcp, *argv);

		/* .. then try the external ones */
		execv_dashed_external(*argv);

		/* It could be an alias -- this works around the insanity
		 * of overriding "git log" with "git show" by having
		 * alias.log = show
		 */
		if (done_alias)
			break;
		if (!handle_alias(argcp, argv))
			break;
		done_alias = 1;
	}

	return done_alias;
}