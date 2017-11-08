char *strbuf_detach(struct strbuf *sb, size_t *sz)
{
	char *res;
	strbuf_grow(sb, 0);
	res = sb->buf;
	if (sz)
		*sz = sb->len;
	strbuf_init(sb, 0);
	return res;
}