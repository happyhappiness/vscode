static inline size_t strbuf_avail(const struct strbuf *sb)
{
	return sb->alloc ? sb->alloc - sb->len - 1 : 0;
}