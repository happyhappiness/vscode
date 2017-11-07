static const char *rsync_url(const char *url)
{
	return !starts_with(url, "rsync://") ? skip_prefix(url, "rsync:") : url;
}