static const char *rsync_url(const char *url)
{
	if (!starts_with(url, "rsync://"))
		skip_prefix(url, "rsync:", &url);
	return url;
}