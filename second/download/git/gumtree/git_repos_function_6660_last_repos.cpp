int winansi_isatty(int fd)
{
	if (fd >= 0 && fd <= 2)
		return fd_is_interactive[fd] != 0;
	return isatty(fd);
}