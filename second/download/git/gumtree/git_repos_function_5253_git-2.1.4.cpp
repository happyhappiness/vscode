int buffer_tmpfile_init(struct line_buffer *buf)
{
	buf->infile = tmpfile();
	if (!buf->infile)
		return -1;
	return 0;
}