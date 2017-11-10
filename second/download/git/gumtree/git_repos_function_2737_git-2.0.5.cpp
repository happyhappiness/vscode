static int dir_in_way(const char *path, int check_working_copy)
{
	int pos, pathlen = strlen(path);
	char *dirpath = xmalloc(pathlen + 2);
	struct stat st;

	strcpy(dirpath, path);
	dirpath[pathlen] = '/';
	dirpath[pathlen+1] = '\0';

	pos = cache_name_pos(dirpath, pathlen+1);

	if (pos < 0)
		pos = -1 - pos;
	if (pos < active_nr &&
	    !strncmp(dirpath, active_cache[pos]->name, pathlen+1)) {
		free(dirpath);
		return 1;
	}

	free(dirpath);
	return check_working_copy && !lstat(path, &st) && S_ISDIR(st.st_mode);
}