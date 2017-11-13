const char *absolute_path(const char *path)
{
	static char buf[PATH_MAX + 1];

	if (!*path) {
		die("The empty string is not a valid path");
	} else if (is_absolute_path(path)) {
		if (strlcpy(buf, path, PATH_MAX) >= PATH_MAX)
			die("Too long path: %.*s", 60, path);
	} else {
		size_t len;
		const char *fmt;
		const char *cwd = get_pwd_cwd();
		if (!cwd)
			die_errno("Cannot determine the current working directory");
		len = strlen(cwd);
		fmt = (len > 0 && is_dir_sep(cwd[len - 1])) ? "%s%s" : "%s/%s";
		if (snprintf(buf, PATH_MAX, fmt, cwd, path) >= PATH_MAX)
			die("Too long path: %.*s", 60, path);
	}
	return buf;
}