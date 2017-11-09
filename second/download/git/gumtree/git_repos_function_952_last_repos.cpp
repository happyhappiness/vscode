static inline void stripspace(struct strbuf *buf, int skip_comments)
{
	strbuf_stripspace(buf, skip_comments);
}