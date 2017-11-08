char *push_dir(char *dir, int save)
{
	char *ret = curr_dir;
	static int initialised;

	if (!initialised) {
		initialised = 1;
		getcwd(curr_dir, sizeof(curr_dir)-1);
	}

	if (chdir(dir)) return NULL;

	if (save) {
		ret = strdup(curr_dir);
	}

	if (*dir == '/') {
		strlcpy(curr_dir, dir, sizeof(curr_dir)-1);
	} else {
		strlcat(curr_dir,"/", sizeof(curr_dir)-1);
		strlcat(curr_dir,dir, sizeof(curr_dir)-1);
	}

	clean_fname(curr_dir);

	return ret;
}