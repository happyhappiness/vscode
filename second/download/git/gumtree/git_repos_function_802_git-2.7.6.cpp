static inline void dup_devnull(int to)
{
	int fd = open("/dev/null", O_RDWR);
	if (fd < 0)
		die_errno(_("open /dev/null failed"));
	if (dup2(fd, to) < 0)
		die_errno(_("dup2(%d,%d) failed"), fd, to);
	close(fd);
}