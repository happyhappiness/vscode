int do_mkstemp(char *template, mode_t perms)
{
	if (dry_run) return -1;
	if (read_only) {errno = EROFS; return -1;}

#if defined(HAVE_SECURE_MKSTEMP) && defined(HAVE_FCHMOD)
	{
		int fd = mkstemp(template);
		if (fd == -1) return -1;
		if (fchmod(fd, perms) != 0) {
			close(fd);
			unlink(template);
			return -1;
		}
		return fd;
	}
#else
	if (!mktemp(template)) return -1;
	return do_open(template, O_RDWR|O_EXCL|O_CREAT, perms);
#endif
}