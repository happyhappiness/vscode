int strbuf_reencode(struct strbuf *sb, const char *from, const char *to)
{
	char *out;
	int len;

	if (same_encoding(from, to))
		return 0;

	out = reencode_string_len(sb->buf, sb->len, to, from, &len);
	if (!out)
		return -1;

	strbuf_attach(sb, out, len, len);
	return 0;
}