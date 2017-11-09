static int read_chunk(struct line_buffer *delta, off_t *delta_len,
		      struct strbuf *buf, size_t len)
{
	assert(*delta_len >= 0);
	strbuf_reset(buf);
	if (len > (uintmax_t) *delta_len ||
	    buffer_read_binary(delta, buf, len) != len)
		return error_short_read(delta);
	*delta_len -= buf->len;
	return 0;
}