DIR *opendir(const char *name)
{
	DWORD attrs = GetFileAttributesA(name);
	int len;
	DIR *p;

	/* check for valid path */
	if (attrs == INVALID_FILE_ATTRIBUTES) {
		errno = ENOENT;
		return NULL;
	}

	/* check if it's a directory */
	if (!(attrs & FILE_ATTRIBUTE_DIRECTORY)) {
		errno = ENOTDIR;
		return NULL;
	}

	/* check that the pattern won't be too long for FindFirstFileA */
	len = strlen(name);
	if (is_dir_sep(name[len - 1]))
		len--;
	if (len + 2 >= MAX_PATH) {
		errno = ENAMETOOLONG;
		return NULL;
	}

	p = malloc(sizeof(DIR) + len + 2);
	if (!p)
		return NULL;

	memset(p, 0, sizeof(DIR) + len + 2);
	strcpy(p->dd_name, name);
	p->dd_name[len] = '/';
	p->dd_name[len+1] = '*';

	p->dd_handle = INVALID_HANDLE_VALUE;
	return p;
}