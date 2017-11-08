static const char *what_fd_is(int fd)
{
	static char buf[20];

	if (fd == sock_f_out)
		return "socket";
	else if (fd == msg_fd_out)
		return "message fd";
	else if (fd == batch_fd)
		return "batch file";
	else {
		snprintf(buf, sizeof buf, "fd %d", fd);
		return buf;
	}
}