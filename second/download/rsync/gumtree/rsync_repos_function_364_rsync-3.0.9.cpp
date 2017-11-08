int unsafe_symlink(const char *dest, const char *src)
{
	const char *name, *slash;
	int depth = 0;

	/* all absolute and null symlinks are unsafe */
	if (!dest || !*dest || *dest == '/')
		return 1;

	/* find out what our safety margin is */
	for (name = src; (slash = strchr(name, '/')) != 0; name = slash+1) {
		/* ".." segment starts the count over.  "." segment is ignored. */
		if (*name == '.' && (name[1] == '/' || (name[1] == '.' && name[2] == '/'))) {
			if (name[1] == '.')
				depth = 0;
		} else
			depth++;
		while (slash[1] == '/') slash++; /* just in case src isn't clean */
	}
	if (*name == '.' && name[1] == '.' && name[2] == '\0')
		depth = 0;

	for (name = dest; (slash = strchr(name, '/')) != 0; name = slash+1) {
		if (*name == '.' && (name[1] == '/' || (name[1] == '.' && name[2] == '/'))) {
			if (name[1] == '.') {
				/* if at any point we go outside the current directory
				   then stop - it is unsafe */
				if (--depth < 0)
					return 1;
			}
		} else
			depth++;
		while (slash[1] == '/') slash++;
	}
	if (*name == '.' && name[1] == '.' && name[2] == '\0')
		depth--;

	return depth < 0;
}