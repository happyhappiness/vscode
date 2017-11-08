void git_extract_argv0_path(const char *argv0)
{
	const char *slash;

	if (!argv0 || !*argv0)
		return;

	slash = find_last_dir_sep(argv0);

	if (slash)
		argv0_path = xstrndup(argv0, slash - argv0);
}