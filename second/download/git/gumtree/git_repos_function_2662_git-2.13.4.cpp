static int match_urls(const struct url_info *url,
		      const struct url_info *url_prefix,
		      struct urlmatch_item *match)
{
	/*
	 * url_prefix matches url if the scheme, host and port of url_prefix
	 * are the same as those of url and the path portion of url_prefix
	 * is the same as the path portion of url or it is a prefix that
	 * matches at a '/' boundary.  If url_prefix contains a user name,
	 * that must also exactly match the user name in url.
	 *
	 * If the user, host, port and path match in this fashion, the returned
	 * value is the length of the path match including any implicit
	 * final '/'.  For example, "http://me@example.com/path" is matched by
	 * "http://example.com" with a path length of 1.
	 *
	 * If there is a match and exactusermatch is not NULL, then
	 * *exactusermatch will be set to true if both url and url_prefix
	 * contained a user name or false if url_prefix did not have a
	 * user name.  If there is no match *exactusermatch is left untouched.
	 */
	char usermatched = 0;
	size_t pathmatchlen;

	if (!url || !url_prefix || !url->url || !url_prefix->url)
		return 0;

	/* check the scheme */
	if (url_prefix->scheme_len != url->scheme_len ||
	    strncmp(url->url, url_prefix->url, url->scheme_len))
		return 0; /* schemes do not match */

	/* check the user name if url_prefix has one */
	if (url_prefix->user_off) {
		if (!url->user_off || url->user_len != url_prefix->user_len ||
		    strncmp(url->url + url->user_off,
			    url_prefix->url + url_prefix->user_off,
			    url->user_len))
			return 0; /* url_prefix has a user but it's not a match */
		usermatched = 1;
	}

	/* check the host */
	if (!match_host(url, url_prefix))
		return 0; /* host names do not match */

	/* check the port */
	if (url_prefix->port_len != url->port_len ||
	    strncmp(url->url + url->port_off,
		    url_prefix->url + url_prefix->port_off, url->port_len))
		return 0; /* ports do not match */

	/* check the path */
	pathmatchlen = url_match_prefix(
		url->url + url->path_off,
		url_prefix->url + url_prefix->path_off,
		url_prefix->url_len - url_prefix->path_off);
	if (!pathmatchlen)
		return 0; /* paths do not match */

	if (match) {
		match->hostmatch_len = url_prefix->host_len;
		match->pathmatch_len = pathmatchlen;
		match->user_matched = usermatched;
	}

	return 1;
}