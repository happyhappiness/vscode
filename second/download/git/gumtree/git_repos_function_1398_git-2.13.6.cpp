int http_fetch_ref(const char *base, struct ref *ref)
{
	struct http_get_options options = {0};
	char *url;
	struct strbuf buffer = STRBUF_INIT;
	int ret = -1;

	options.no_cache = 1;

	url = quote_ref_url(base, ref->name);
	if (http_get_strbuf(url, &buffer, &options) == HTTP_OK) {
		strbuf_rtrim(&buffer);
		if (buffer.len == 40)
			ret = get_oid_hex(buffer.buf, &ref->old_oid);
		else if (starts_with(buffer.buf, "ref: ")) {
			ref->symref = xstrdup(buffer.buf + 5);
			ret = 0;
		}
	}

	strbuf_release(&buffer);
	free(url);
	return ret;
}