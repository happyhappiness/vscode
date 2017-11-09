static void handle_header(struct strbuf **out, const struct strbuf *line)
{
	if (!*out) {
		*out = xmalloc(sizeof(struct strbuf));
		strbuf_init(*out, line->len);
	} else
		strbuf_reset(*out);

	strbuf_addbuf(*out, line);
}