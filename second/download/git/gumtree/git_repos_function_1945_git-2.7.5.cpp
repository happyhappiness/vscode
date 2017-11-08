const char *git_extract_argv0_path(const char *argv0)
{
	const char *slash;

	if (!argv0 || !*argv0)
		return NULL;

	slash = find_last_dir_sep(argv0);

	if (slash) {
		argv0_path = xstrndup(argv0, slash - argv0);
		return slash + 1;
	}

	return argv0;
}