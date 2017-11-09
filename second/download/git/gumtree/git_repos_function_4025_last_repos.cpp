static int read_dir_paths(struct string_list *out, const char *path)
{
	DIR *dh;
	struct dirent *de;

	dh = opendir(path);
	if (!dh)
		return -1;

	while ((de = readdir(dh)))
		if (de->d_name[0] != '.')
			string_list_append(out, de->d_name);

	closedir(dh);
	return 0;
}