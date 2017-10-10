
	fp = fopen(*paths, "r");
	if (!fp)
		return error(_("could not open '%s' for reading: %s"), *paths,
				strerror(errno));

	while (!strbuf_getline(&sb, fp, '\n')) {
		if (*sb.buf == '#')
			continue; /* skip comment lines */

		argv_array_push(&patches, mkpath("%s/%s", series_dir, sb.buf));
	}

