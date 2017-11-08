static char *git_path_from_env(const char *envvar, const char *path)
{
	const char *value = getenv(envvar);
	return value ? xstrdup(value) : git_pathdup("%s", path);
}