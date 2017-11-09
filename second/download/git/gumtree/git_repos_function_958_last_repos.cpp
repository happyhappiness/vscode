static inline void strbuf_complete_line(struct strbuf *sb)
{
	strbuf_complete(sb, '\n');
}