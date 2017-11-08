void set_error_fd(int fd)
{
	log_error_fd = fd;
	set_nonblocking(log_error_fd);
}