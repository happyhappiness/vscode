 * and we ask for "http://example.com/foo.git/info/refs", we might end up
 * with "https://other.example.com/foo.git/info/refs". We would want the
 * new URL to become "https://other.example.com/foo.git".
 *
 * Note that this assumes a sane redirect scheme. It's entirely possible
 * in the example above to end up at a URL that does not even end in
 * "info/refs".  In such a case we simply punt, as there is not much we can
 * do (and such a scheme is unlikely to represent a real git repository,
 * which means we are likely about to abort anyway).
 */
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

static int http_request_reauth(const char *url,
			       void *result, int target,
			       struct http_get_options *options)
