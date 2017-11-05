static inline int fcntl(int fd, int cmd, ...)
{
	if (cmd == F_GETFD || cmd == F_SETFD)
		return 0;
	errno = EINVAL;
	return -1;
}