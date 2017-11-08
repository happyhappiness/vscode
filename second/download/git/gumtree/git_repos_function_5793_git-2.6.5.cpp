FILE *buffer_tmpfile_rewind(struct line_buffer *buf)
{
	rewind(buf->infile);
	return buf->infile;
}