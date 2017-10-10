	return;
}

int svndump_init(const char *filename)
{
	if (buffer_init(&input, filename))
		return error("cannot open %s: %s", filename ? filename : "NULL", strerror(errno));
	init(REPORT_FILENO);
	return 0;
}

int svndump_init_fd(int in_fd, int back_fd)
{
	if(buffer_fdinit(&input, xdup(in_fd)))
		return error("cannot open fd %d: %s", in_fd, strerror(errno));
	init(xdup(back_fd));
	return 0;
}

void svndump_deinit(void)
{
