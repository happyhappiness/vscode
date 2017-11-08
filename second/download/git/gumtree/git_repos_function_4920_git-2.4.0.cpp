int cmd_merge_ours(int argc, const char **argv, const char *prefix)
{
	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage(builtin_merge_ours_usage);

	/*
	 * We need to exit with 2 if the index does not match our HEAD tree,
	 * because the current index is what we will be committing as the
	 * merge result.
	 */
	if (cmd_diff_index(NARGS, diff_index_args, prefix))
		exit(2);
	exit(0);
}