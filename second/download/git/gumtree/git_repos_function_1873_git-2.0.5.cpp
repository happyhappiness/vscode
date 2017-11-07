static void strbuf_add_urlencode(struct strbuf *sb, const char *s, size_t len,
				 int reserved)
{
	strbuf_grow(sb, len);
	while (len--) {
		char ch = *s++;
		if (is_rfc3986_unreserved(ch) ||
		    (!reserved && is_rfc3986_reserved(ch)))
			strbuf_addch(sb, ch);
		else
			strbuf_addf(sb, "%%%02x", ch);
	}
}