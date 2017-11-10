static void dump_quoted_path(const char *head,
			     const char *prefix,
			     const char *path,
			     const char *line_prefix,
			     const char *c_meta, const char *c_reset)
{
	static struct strbuf buf = STRBUF_INIT;

	strbuf_reset(&buf);
	strbuf_addstr(&buf, line_prefix);
	strbuf_addstr(&buf, c_meta);
	strbuf_addstr(&buf, head);
	quote_two_c_style(&buf, prefix, path, 0);
	strbuf_addstr(&buf, c_reset);
	puts(buf.buf);
}