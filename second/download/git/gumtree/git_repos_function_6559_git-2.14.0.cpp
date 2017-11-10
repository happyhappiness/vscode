static int read_to_fill_or_whine(struct line_buffer *file,
				struct strbuf *buf, size_t width)
{
	buffer_read_binary(file, buf, width - buf->len);
	if (buf->len != width)
		return input_error(file);
	return 0;
}