void strbuf_attach(struct strbuf *sb, void *buf, size_t len, size_t alloc)
{
	strbuf_release(sb);
	sb->buf   = buf;
	sb->len   = len;
	sb->alloc = alloc;
	strbuf_grow(sb, 0);
	sb->buf[sb->len] = '\0';
}