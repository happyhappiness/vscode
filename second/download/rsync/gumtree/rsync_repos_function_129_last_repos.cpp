static const char *what_fd_is(int fd)
{
	static char buf[20];

	if (fd == sock_f_out)
		return "socket";
	else if (fd == iobuf.out_fd)
		return "message fd";
	else if (fd == batch_fd)
		return "batch file";
	else {
		snprintf(buf, sizeof buf, "fd %d", fd);
		return buf;
	}
}