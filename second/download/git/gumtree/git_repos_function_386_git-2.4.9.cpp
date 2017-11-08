static void print_line(struct strbuf *buf)
{
	strbuf_addch(buf, '\n');
	write_or_die(credential_lock.fd, buf->buf, buf->len);
}