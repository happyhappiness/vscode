long buffer_tmpfile_prepare_to_read(struct line_buffer *buf)
{
	long pos = ftell(buf->infile);
	if (pos < 0)
		return error("ftell error: %s", strerror(errno));
	if (fseek(buf->infile, 0, SEEK_SET))
		return error("seek error: %s", strerror(errno));
	return pos;
}