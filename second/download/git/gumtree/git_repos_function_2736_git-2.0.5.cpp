static char *unique_path(struct merge_options *o, const char *path, const char *branch)
{
	char *newpath = xmalloc(strlen(path) + 1 + strlen(branch) + 8 + 1);
	int suffix = 0;
	struct stat st;
	char *p = newpath + strlen(path);
	strcpy(newpath, path);
	*(p++) = '~';
	strcpy(p, branch);
	for (; *p; ++p)
		if ('/' == *p)
			*p = '_';
	while (string_list_has_string(&o->current_file_set, newpath) ||
	       string_list_has_string(&o->current_directory_set, newpath) ||
	       lstat(newpath, &st) == 0)
		sprintf(p, "_%d", suffix++);

	string_list_insert(&o->current_file_set, newpath);
	return newpath;
}