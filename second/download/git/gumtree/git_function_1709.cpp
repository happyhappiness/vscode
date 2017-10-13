tatic void split_ident_or_die(struct ident_split *id, const struct strbuf *buf)
{
	if (split_ident_line(id, buf->buf, buf->len) ||
	    !sane_ident_split(id))
		die(_("Malformed ident string: '%s'"), buf->buf);
}