static char *git_path_from_env(const char *envvar, const char *git_dir,
			       const char *path, int *fromenv)
{
	const char *value = getenv(envvar);
	if (!value)
		return xstrfmt("%s/%s", git_dir, path);
	if (fromenv)
		*fromenv = 1;
	return xstrdup(value);
}