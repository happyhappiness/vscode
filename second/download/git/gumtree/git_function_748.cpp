static int is_alternate_allowed(const char *url)
{
	const char *protocols[] = {
		"http", "https", "ftp", "ftps"
	};
	int i;

	if (http_follow_config != HTTP_FOLLOW_ALWAYS) {
		warning("alternate disabled by http.followRedirects: %s", url);
		return 0;
	}

	for (i = 0; i < ARRAY_SIZE(protocols); i++) {
		const char *end;
		if (skip_prefix(url, protocols[i], &end) &&
		    starts_with(end, "://"))
			break;
	}

	if (i >= ARRAY_SIZE(protocols)) {
		warning("ignoring alternate with unknown protocol: %s", url);
		return 0;
	}
	if (!is_transport_allowed(protocols[i], 0)) {
		warning("ignoring alternate with restricted protocol: %s", url);
		return 0;
	}

	return 1;
}