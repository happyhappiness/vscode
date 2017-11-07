static void add_url_alias(struct remote *remote, const char *url)
{
	add_url(remote, alias_url(url, &rewrites));
	add_pushurl_alias(remote, url);
}