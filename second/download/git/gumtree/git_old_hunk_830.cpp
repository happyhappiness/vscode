{
	const char *protocols[] = {
		"http", "https", "ftp", "ftps"
	};
	int i;

	for (i = 0; i < ARRAY_SIZE(protocols); i++) {
		const char *end;
		if (skip_prefix(url, protocols[i], &end) &&
		    starts_with(end, "://"))
			break;
	}
