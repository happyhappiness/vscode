static inline void close_pair(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

#ifndef GIT_WINDOWS_NATIVE
static inline void dup_devnull(int to)
{
	int fd = open("/dev/null", O_RDWR);
	if (fd < 0)
		die_errno(_("open /dev/null failed"));
	if (dup2(fd, to) < 0)
		die_errno(_("dup2(%d,%d) failed"), fd, to);
	close(fd);
}
#endif

static char *locate_in_PATH(const char *file)
{
	const char *p = getenv("PATH");
	struct strbuf buf = STRBUF_INIT;

	if (!p || !*p)
