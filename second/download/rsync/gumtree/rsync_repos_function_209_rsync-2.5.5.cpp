char *push_dir(char *dir, int save)
{
	char *ret = curr_dir;
	static int initialised;

	if (!initialised) {
		initialised = 1;
		getcwd(curr_dir, sizeof(curr_dir)-1);
	}

	if (!dir) return NULL; /* this call was probably just to initialize */

	if (chdir(dir)) return NULL;

	if (save) {
		ret = strdup(curr_dir);
	}

	if (*dir == '/') {
		strlcpy(curr_dir, dir, sizeof(curr_dir));
	} else {
		strlcat(curr_dir,"/", sizeof(curr_dir));
		strlcat(curr_dir,dir, sizeof(curr_dir));
	}

	clean_fname(curr_dir);

	return ret;
}