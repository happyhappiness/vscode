	if (!fh) {
		if (errno != ENOENT && errno != EACCES)
			die_errno("unable to open %s", fn);
		return found_credential;
	}

	while (strbuf_getline(&line, fh, '\n') != EOF) {
		credential_from_url(&entry, line.buf);
		if (entry.username && entry.password &&
		    credential_match(c, &entry)) {
			found_credential = 1;
			if (match_cb) {
				match_cb(&entry);
