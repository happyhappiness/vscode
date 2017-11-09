static char *git_path_from_env(const char *envvar, const char *git_dir,
			       const char *path, int fromenv)
{
	if (fromenv) {
		const char *value = getenv(envvar);
		if (value)
			return xstrdup(value);
	}

	return xstrfmt("%s/%s", git_dir, path);
}