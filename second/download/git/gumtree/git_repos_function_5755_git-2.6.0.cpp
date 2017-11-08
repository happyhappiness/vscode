int svndump_init_fd(int in_fd, int back_fd)
{
	if(buffer_fdinit(&input, xdup(in_fd)))
		return error("cannot open fd %d: %s", in_fd, strerror(errno));
	init(xdup(back_fd));
	return 0;
}