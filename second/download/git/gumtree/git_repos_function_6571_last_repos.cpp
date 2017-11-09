int svndump_init_fd(int in_fd, int back_fd)
{
	if(buffer_fdinit(&input, xdup(in_fd)))
		return error_errno("cannot open fd %d", in_fd);
	init(xdup(back_fd));
	return 0;
}