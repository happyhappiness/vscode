char *url_decode_mem(const char *url, int len)
{
	struct strbuf out = STRBUF_INIT;
	const char *colon = memchr(url, ':', len);

	/* Skip protocol part if present */
	if (colon && url < colon) {
		strbuf_add(&out, url, colon - url);
		len -= colon - url;
		url = colon;
	}
	return url_decode_internal(&url, len, NULL, &out, 0);
}