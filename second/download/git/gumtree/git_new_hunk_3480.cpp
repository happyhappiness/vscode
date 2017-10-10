	return;
}

int svndump_init(const char *filename)
{
	if (buffer_init(&input, filename))
		return error_errno("cannot open %s", filename ? filename : "NULL");
	init(REPORT_FILENO);
	return 0;
}

int svndump_init_fd(int in_fd, int back_fd)
{
	if(buffer_fdinit(&input, xdup(in_fd)))
		return error_errno("cannot open fd %d", in_fd);
	init(xdup(back_fd));
	return 0;
}

void svndump_deinit(void)
{
