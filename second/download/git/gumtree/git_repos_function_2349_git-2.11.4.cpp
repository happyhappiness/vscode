static void parse_bogus_from(struct mailinfo *mi, const struct strbuf *line)
{
	/* John Doe <johndoe> */

	char *bra, *ket;
	/* This is fallback, so do not bother if we already have an
	 * e-mail address.
	 */
	if (mi->email.len)
		return;

	bra = strchr(line->buf, '<');
	if (!bra)
		return;
	ket = strchr(bra, '>');
	if (!ket)
		return;

	strbuf_reset(&mi->email);
	strbuf_add(&mi->email, bra + 1, ket - bra - 1);

	strbuf_reset(&mi->name);
	strbuf_add(&mi->name, line->buf, bra - line->buf);
	strbuf_trim(&mi->name);
	get_sane_name(&mi->name, &mi->name, &mi->email);
}