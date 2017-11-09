static inline struct strbuf **strbuf_split(const struct strbuf *sb,
					   int terminator)
{
	return strbuf_split_max(sb, terminator, 0);
}