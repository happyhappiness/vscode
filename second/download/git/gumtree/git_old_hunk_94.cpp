	config.cascade_fn = NULL;
	config.cb = &values;

	if (!url_normalize(url, &config.url))
		die("%s", config.url.err);

	config.section = dup_downcase(var);
	section_tail = strchr(config.section, '.');
	if (section_tail) {
		*section_tail = '\0';
		config.key = section_tail + 1;
		show_keys = 0;
	} else {
