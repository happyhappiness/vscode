int remote_has_url(struct remote *remote, const char *url)
{
	int i;
	for (i = 0; i < remote->url_nr; i++) {
		if (!strcmp(remote->url[i], url))
			return 1;
	}
	return 0;
}