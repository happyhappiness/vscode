int do_mkstemp(char *template, mode_t perms)
{
	RETURN_ERROR_IF(dry_run, 0);
	RETURN_ERROR_IF(read_only, EROFS);
	perms |= S_IWUSR;

#if defined HAVE_SECURE_MKSTEMP && defined HAVE_FCHMOD && (!defined HAVE_OPEN64 || defined HAVE_MKSTEMP64)
	{
		int fd = mkstemp(template);
		if (fd == -1)
			return -1;
		if (fchmod(fd, perms) != 0 && preserve_perms) {
			int errno_save = errno;
			close(fd);
			unlink(template);
			errno = errno_save;
			return -1;
		}
#if defined HAVE_SETMODE && O_BINARY
		setmode(fd, O_BINARY);
#endif
		return fd;
	}
#else
	if (!mktemp(template))
		return -1;
	return do_open(template, O_RDWR|O_EXCL|O_CREAT, perms);
#endif
}