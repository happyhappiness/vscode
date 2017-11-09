int interactive_add(int argc, const char **argv, const char *prefix, int patch)
{
	struct pathspec pathspec;

	parse_pathspec(&pathspec, 0,
		       PATHSPEC_PREFER_FULL |
		       PATHSPEC_SYMLINK_LEADING_PATH |
		       PATHSPEC_PREFIX_ORIGIN,
		       prefix, argv);

	return run_add_interactive(NULL,
				   patch ? "--patch" : NULL,
				   &pathspec);
}