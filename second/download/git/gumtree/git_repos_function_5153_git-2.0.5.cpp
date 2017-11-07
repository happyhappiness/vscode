int buffer_fdinit(struct line_buffer *buf, int fd)
{
	buf->infile = fdopen(fd, "r");
	if (!buf->infile)
		return -1;
	return 0;
}