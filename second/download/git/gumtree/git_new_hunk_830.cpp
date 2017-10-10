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
