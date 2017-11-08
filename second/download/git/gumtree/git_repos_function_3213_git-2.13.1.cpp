static void end_headers(struct strbuf *hdr)
{
	strbuf_add(hdr, "\r\n", 2);
	write_or_die(1, hdr->buf, hdr->len);
	strbuf_release(hdr);
}