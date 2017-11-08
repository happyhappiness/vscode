void append_remote_object_url(struct strbuf *buf, const char *url,
			      const char *hex,
			      int only_two_digit_prefix)
{
	end_url_with_slash(buf, url);

	strbuf_addf(buf, "objects/%.*s/", 2, hex);
	if (!only_two_digit_prefix)
		strbuf_addstr(buf, hex + 2);
}