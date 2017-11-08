static void convert_to_utf8(struct strbuf *line, const char *charset)
{
	char *out;

	if (!charset || !*charset)
		return;

	if (same_encoding(metainfo_charset, charset))
		return;
	out = reencode_string(line->buf, metainfo_charset, charset);
	if (!out)
		die("cannot convert from %s to %s",
		    charset, metainfo_charset);
	strbuf_attach(line, out, strlen(out), strlen(out));
}