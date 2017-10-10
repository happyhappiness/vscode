
const char *real_path_if_valid(const char *path)
{
	return real_path_internal(path, 0);
}

static const char *get_pwd_cwd(void)
{
	static char cwd[PATH_MAX + 1];
	char *pwd;
	struct stat cwd_stat, pwd_stat;
	if (getcwd(cwd, PATH_MAX) == NULL)
		return NULL;
	pwd = getenv("PWD");
	if (pwd && strcmp(pwd, cwd)) {
		stat(cwd, &cwd_stat);
		if ((cwd_stat.st_dev || cwd_stat.st_ino) &&
		    !stat(pwd, &pwd_stat) &&
		    pwd_stat.st_dev == cwd_stat.st_dev &&
		    pwd_stat.st_ino == cwd_stat.st_ino) {
			strlcpy(cwd, pwd, PATH_MAX);
		}
	}
	return cwd;
}

/*
 * Use this to get an absolute path from a relative one. If you want
 * to resolve links, you should use real_path.
 *
 * If the path is already absolute, then return path. As the user is
 * never meant to free the return value, we're safe.
 */
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

/*
 * Unlike prefix_path, this should be used if the named file does
 * not have to interact with index entry; i.e. name of a random file
 * on the filesystem.
