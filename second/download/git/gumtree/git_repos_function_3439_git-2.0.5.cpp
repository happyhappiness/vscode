static int run_argv(int *argcp, const char ***argv)
{
	int done_alias = 0;

	while (1) {
		/* See if it's a builtin */
		handle_builtin(*argcp, *argv);

		/* .. then try the external ones */
		execv_dashed_external(*argv);

		/* It could be an alias -- this works around the insanity
		 * of overriding "git log" with "git show" by having
		 * alias.log = show
		 */
		if (done_alias || !handle_alias(argcp, argv))
			break;
		done_alias = 1;
	}

	return done_alias;
}