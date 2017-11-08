static void add_pushurl_alias(struct remote *remote, const char *url)
{
	const char *pushurl = alias_url(url, &rewrites_push);
	if (pushurl != url)
		add_pushurl(remote, pushurl);
}