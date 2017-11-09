static void strbuf_append_ext_header_uint(struct strbuf *sb,
					  const char *keyword,
					  uintmax_t value)
{
	char buf[40]; /* big enough for 2^128 in decimal, plus NUL */
	int len;

	len = xsnprintf(buf, sizeof(buf), "%"PRIuMAX, value);
	strbuf_append_ext_header(sb, keyword, buf, len);
}