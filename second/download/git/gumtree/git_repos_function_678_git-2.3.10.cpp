static inline void strbuf_setlen(struct strbuf *sb, size_t len)
{
	if (len > (sb->alloc ? sb->alloc - 1 : 0))
		die("BUG: strbuf_setlen() beyond buffer");
	sb->len = len;
	sb->buf[len] = '\0';
}