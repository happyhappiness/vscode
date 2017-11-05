int check_filename(const char *prefix, const char *arg)
{
	const char *name;
	struct stat st;

	if (starts_with(arg, ":/")) {
		if (arg[2] == '\0') /* ":/" is root dir, always exists */
			return 1;
		name = arg + 2;
	} else if (!no_wildcard(arg))
		return 1;
	else if (prefix)
		name = prefix_filename(prefix, strlen(prefix), arg);
	else
		name = arg;
	if (!lstat(name, &st))
		return 1; /* file exists */
	if (errno == ENOENT || errno == ENOTDIR)
		return 0; /* file does not exist */
	die_errno("failed to stat '%s'", arg);
}