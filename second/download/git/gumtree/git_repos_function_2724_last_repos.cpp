void strbuf_addstr_urlencode(struct strbuf *sb, const char *s,
			     int reserved)
{
	strbuf_add_urlencode(sb, s, strlen(s), reserved);
}