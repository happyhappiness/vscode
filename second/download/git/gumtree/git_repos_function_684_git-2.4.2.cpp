static inline struct strbuf **strbuf_split_max(const struct strbuf *sb,
						int terminator, int max)
{
	return strbuf_split_buf(sb->buf, sb->len, terminator, max);
}