void set_msg_fd_out(int fd)
{
	msg_fd_out = fd;
	set_nonblocking(msg_fd_out);
}