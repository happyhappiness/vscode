static int update_url_from_redirect(struct strbuf *base,
				    const char *asked,
				    const struct strbuf *got)
{
	const char *tail;
	size_t tail_len;

	if (!strcmp(asked, got->buf))
		return 0;

	if (!skip_prefix(asked, base->buf, &tail))
		die("BUG: update_url_from_redirect: %s is not a superset of %s",
		    asked, base->buf);

	tail_len = strlen(tail);

	if (got->len < tail_len ||
	    strcmp(tail, got->buf + got->len - tail_len))
		return 0; /* insane redirect scheme */

	strbuf_reset(base);
	strbuf_add(base, got->buf, got->len - tail_len);
	return 1;
}