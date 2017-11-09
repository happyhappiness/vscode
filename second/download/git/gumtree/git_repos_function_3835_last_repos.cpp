static int read_directory_contents(const char *path, struct string_list *list)
{
	DIR *dir;
	struct dirent *e;

	if (!(dir = opendir(path)))
		return error("Could not open directory %s", path);

	while ((e = readdir(dir)))
		if (!is_dot_or_dotdot(e->d_name))
			string_list_insert(list, e->d_name);

	closedir(dir);
	return 0;
}