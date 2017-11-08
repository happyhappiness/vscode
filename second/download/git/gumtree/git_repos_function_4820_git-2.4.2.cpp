static void handle_content_transfer_encoding(const struct strbuf *line)
{
	if (strcasestr(line->buf, "base64"))
		transfer_encoding = TE_BASE64;
	else if (strcasestr(line->buf, "quoted-printable"))
		transfer_encoding = TE_QP;
	else
		transfer_encoding = TE_DONTCARE;
}