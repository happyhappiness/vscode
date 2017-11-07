static void assert_split_ident(struct ident_split *id, const struct strbuf *buf)
{
	if (split_ident_line(id, buf->buf, buf->len) || !id->date_begin)
		die("BUG: unable to parse our own ident: %s", buf->buf);
}