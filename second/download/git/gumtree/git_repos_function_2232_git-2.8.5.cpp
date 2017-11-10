void strbuf_addchars(struct strbuf *sb, int c, size_t n)
{
	strbuf_grow(sb, n);
	memset(sb->buf + sb->len, c, n);
	strbuf_setlen(sb, sb->len + n);
}