	char *url;
	const char *filename = dry_run ? "/dev/null" : git_path_fetch_head();
	int want_status;

	fp = fopen(filename, "a");
	if (!fp)
		return error_errno(_("cannot open %s"), filename);

	if (raw_url)
		url = transport_anonymize_url(raw_url);
	else
		url = xstrdup("foreign");

