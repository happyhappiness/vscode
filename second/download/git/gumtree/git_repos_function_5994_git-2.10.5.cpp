static int error_short_read(struct line_buffer *input)
{
	if (buffer_ferror(input))
		return error_errno("error reading delta");
	return error("invalid delta: unexpected end of file");
}