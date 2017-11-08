int is_url(const char *url)
{
	/* Is "scheme" part reasonable? */
	if (!url || !is_urlschemechar(1, *url++))
		return 0;
	while (*url && *url != ':') {
		if (!is_urlschemechar(0, *url++))
			return 0;
	}
	/* We've seen "scheme"; we want colon-slash-slash */
	return (url[0] == ':' && url[1] == '/' && url[2] == '/');
}