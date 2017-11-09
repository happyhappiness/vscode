static const char *remove_ext_force(const char *url)
{
	if (url) {
		const char *colon = strchr(url, ':');
		if (colon && colon[1] == ':')
			return colon + 2;
	}
	return url;
}