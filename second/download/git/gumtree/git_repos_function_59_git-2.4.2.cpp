static int is_executable(const char *name)
{
	struct stat st;

	if (stat(name, &st) || /* stat, not lstat */
	    !S_ISREG(st.st_mode))
		return 0;

#if defined(GIT_WINDOWS_NATIVE)
{	/* cannot trust the executable bit, peek into the file instead */
	char buf[3] = { 0 };
	int n;
	int fd = open(name, O_RDONLY);
	st.st_mode &= ~S_IXUSR;
	if (fd >= 0) {
		n = read(fd, buf, 2);
		if (n == 2)
			/* DOS executables start with "MZ" */
			if (!strcmp(buf, "#!") || !strcmp(buf, "MZ"))
				st.st_mode |= S_IXUSR;
		close(fd);
	}
}
#endif
	return st.st_mode & S_IXUSR;
}