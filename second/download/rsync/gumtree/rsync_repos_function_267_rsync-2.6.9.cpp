int unsafe_symlink(const char *dest, const char *src)
{
	const char *name, *slash;
	int depth = 0;

	/* all absolute and null symlinks are unsafe */
	if (!dest || !*dest || *dest == '/')
		return 1;

	/* find out what our safety margin is */
	for (name = src; (slash = strchr(name, '/')) != 0; name = slash+1) {
		if (strncmp(name, "../", 3) == 0) {
			depth = 0;
		} else if (strncmp(name, "./", 2) == 0) {
			/* nothing */
		} else {
			depth++;
		}
	}
	if (strcmp(name, "..") == 0)
		depth = 0;

	for (name = dest; (slash = strchr(name, '/')) != 0; name = slash+1) {
		if (strncmp(name, "../", 3) == 0) {
			/* if at any point we go outside the current directory
			   then stop - it is unsafe */
			if (--depth < 0)
				return 1;
		} else if (strncmp(name, "./", 2) == 0) {
			/* nothing */
		} else {
			depth++;
		}
	}
	if (strcmp(name, "..") == 0)
		depth--;

	return (depth < 0);
}