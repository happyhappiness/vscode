static int is_gtfrom(const struct strbuf *buf)
{
	size_t min = strlen(">From ");
	size_t ngt;

	if (buf->len < min)
		return 0;

	ngt = strspn(buf->buf, ">");
	return ngt && starts_with(buf->buf + ngt, "From ");
}