static void parse_bogus_from(const struct strbuf *line)
{
	/* John Doe <johndoe> */

	char *bra, *ket;
	/* This is fallback, so do not bother if we already have an
	 * e-mail address.
	 */
	if (email.len)
		return;

	bra = strchr(line->buf, '<');
	if (!bra)
		return;
	ket = strchr(bra, '>');
	if (!ket)
		return;

	strbuf_reset(&email);
	strbuf_add(&email, bra + 1, ket - bra - 1);

	strbuf_reset(&name);
	strbuf_add(&name, line->buf, bra - line->buf);
	strbuf_trim(&name);
	get_sane_name(&name, &name, &email);
}