}

long buffer_tmpfile_prepare_to_read(struct line_buffer *buf)
{
	long pos = ftell(buf->infile);
	if (pos < 0)
		return error_errno("ftell error");
	if (fseek(buf->infile, 0, SEEK_SET))
		return error_errno("seek error");
	return pos;
}

int buffer_ferror(struct line_buffer *buf)
{
	return ferror(buf->infile);
