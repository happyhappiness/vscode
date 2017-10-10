}

static int populate_maildir_list(struct string_list *list, const char *path)
{
	DIR *dir;
	struct dirent *dent;
	char *name = NULL;
	char *subs[] = { "cur", "new", NULL };
	char **sub;
	int ret = -1;

	for (sub = subs; *sub; ++sub) {
		free(name);
		name = xstrfmt("%s/%s", path, *sub);
		if ((dir = opendir(name)) == NULL) {
			if (errno == ENOENT)
				continue;
			error("cannot opendir %s (%s)", name, strerror(errno));
			goto out;
		}

		while ((dent = readdir(dir)) != NULL) {
			if (dent->d_name[0] == '.')
				continue;
			free(name);
			name = xstrfmt("%s/%s", *sub, dent->d_name);
			string_list_insert(list, name);
		}

		closedir(dir);
	}

	ret = 0;

out:
	free(name);
	return ret;
}

static int maildir_filename_cmp(const char *a, const char *b)
{
	while (*a && *b) {
		if (isdigit(*a) && isdigit(*b)) {
