static int update_url_from_redirect(struct strbuf *base,
				    const char *asked,
				    const struct strbuf *got)
{
	const char *tail;
	size_t new_len;

	if (!strcmp(asked, got->buf))
		return 0;

	if (!skip_prefix(asked, base->buf, &tail))
		die("BUG: update_url_from_redirect: %s is not a superset of %s",
		    asked, base->buf);

	new_len = got->len;
	if (!strip_suffix_mem(got->buf, &new_len, tail))
		die(_("unable to update url base from redirection:\n"
		      "  asked for: %s\n"
		      "   redirect: %s"),
		    asked, got->buf);

	strbuf_reset(base);
	strbuf_add(base, got->buf, new_len);

	return 1;
}