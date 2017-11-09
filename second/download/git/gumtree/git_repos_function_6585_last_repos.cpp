int buffer_ferror(struct line_buffer *buf)
{
	return ferror(buf->infile);
}