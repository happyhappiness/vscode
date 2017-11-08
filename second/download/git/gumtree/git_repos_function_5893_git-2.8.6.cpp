int buffer_read_char(struct line_buffer *buf)
{
	return fgetc(buf->infile);
}