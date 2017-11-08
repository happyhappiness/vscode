static char *git_path_from_env(const char *envvar, const char *git_dir,
			       const char *path, int *fromenv)
{
	const char *value = getenv(envvar);
	if (!value) {
		char *buf = xmalloc(strlen(git_dir) + strlen(path) + 2);
		sprintf(buf, "%s/%s", git_dir, path);
		return buf;
	}
	if (fromenv)
		*fromenv = 1;
	return xstrdup(value);
}