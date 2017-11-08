static void send_strbuf(const char *type, struct strbuf *buf)
{
	hdr_int(content_length, buf->len);
	hdr_str(content_type, type);
	end_headers();
	write_or_die(1, buf->buf, buf->len);
}