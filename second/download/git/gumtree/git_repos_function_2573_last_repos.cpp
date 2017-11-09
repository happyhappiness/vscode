static void handle_content_transfer_encoding(struct mailinfo *mi,
					     const struct strbuf *line)
{
	if (strcasestr(line->buf, "base64"))
		mi->transfer_encoding = TE_BASE64;
	else if (strcasestr(line->buf, "quoted-printable"))
		mi->transfer_encoding = TE_QP;
	else
		mi->transfer_encoding = TE_DONTCARE;
}