}

static int write_strbuf(struct strbuf *sb, FILE *out)
{
	if (fwrite(sb->buf, 1, sb->len, out) == sb->len)	/* Success. */
		return 0;
	return error("cannot write delta postimage: %s", strerror(errno));
}

static int error_short_read(struct line_buffer *input)
{
	if (buffer_ferror(input))
		return error("error reading delta: %s", strerror(errno));
	return error("invalid delta: unexpected end of file");
}

static int read_chunk(struct line_buffer *delta, off_t *delta_len,
		      struct strbuf *buf, size_t len)
{
