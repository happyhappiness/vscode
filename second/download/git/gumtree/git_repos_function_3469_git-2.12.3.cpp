void handle_ignore_submodules_arg(struct diff_options *diffopt,
				  const char *arg)
{
	DIFF_OPT_CLR(diffopt, IGNORE_SUBMODULES);
	DIFF_OPT_CLR(diffopt, IGNORE_UNTRACKED_IN_SUBMODULES);
	DIFF_OPT_CLR(diffopt, IGNORE_DIRTY_SUBMODULES);

	if (!strcmp(arg, "all"))
		DIFF_OPT_SET(diffopt, IGNORE_SUBMODULES);
	else if (!strcmp(arg, "untracked"))
		DIFF_OPT_SET(diffopt, IGNORE_UNTRACKED_IN_SUBMODULES);
	else if (!strcmp(arg, "dirty"))
		DIFF_OPT_SET(diffopt, IGNORE_DIRTY_SUBMODULES);
	else if (strcmp(arg, "none"))
		die("bad --ignore-submodules argument: %s", arg);
}