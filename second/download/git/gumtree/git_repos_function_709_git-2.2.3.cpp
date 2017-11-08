char *find_hook(const char *name)
{
	char *path = git_path("hooks/%s", name);
	if (access(path, X_OK) < 0)
		path = NULL;

	return path;
}