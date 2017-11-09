static void add_extra_header(struct strbuf *buffer,
			     struct commit_extra_header *extra)
{
	strbuf_addstr(buffer, extra->key);
	if (extra->len)
		strbuf_add_lines(buffer, " ", extra->value, extra->len);
	else
		strbuf_addch(buffer, '\n');
}