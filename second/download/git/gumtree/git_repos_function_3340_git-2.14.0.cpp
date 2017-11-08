static void send_strbuf(struct strbuf *hdr,
			const char *type, struct strbuf *buf)
{
	hdr_int(hdr, content_length, buf->len);
	hdr_str(hdr, content_type, type);
	end_headers(hdr);
	write_or_die(1, buf->buf, buf->len);
}