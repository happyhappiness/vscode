static void free_path_split(char **path)
{
	char **p = path;

	if (!path)
		return;

	while (*p)
		free(*p++);
	free(path);
}