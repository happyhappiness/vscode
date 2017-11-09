static void strbuf_append_ext_header(struct strbuf *sb, const char *keyword,
                                     const char *value, unsigned int valuelen)
{
	int len, tmp;

	/* "%u %s=%s\n" */
	len = 1 + 1 + strlen(keyword) + 1 + valuelen + 1;
	for (tmp = len; tmp > 9; tmp /= 10)
		len++;

	strbuf_grow(sb, len);
	strbuf_addf(sb, "%u %s=", len, keyword);
	strbuf_add(sb, value, valuelen);
	strbuf_addch(sb, '\n');
}