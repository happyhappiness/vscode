static inline void strbuf_addstr(struct strbuf *sb, const char *s)
{
	strbuf_add(sb, s, strlen(s));
}