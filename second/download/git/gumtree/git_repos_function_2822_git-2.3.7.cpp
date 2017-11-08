static void strbuf_addstr_or_null(struct strbuf *sb, const char *s)
{
	if (s)
		strbuf_addstr(sb, s);
}