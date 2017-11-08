size_t buffer_read_binary(struct line_buffer *buf,
				struct strbuf *sb, size_t size)
{
	return strbuf_fread(sb, size, buf->infile);
}