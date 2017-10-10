
	if (flag & REF_BAD_NAME) {
		  warning("ignoring ref with broken name %s", refname);
		  return 0;
	}

	if (*cb->grab_pattern) {
		const char **pattern;
		int namelen = strlen(refname);
		for (pattern = cb->grab_pattern; *pattern; pattern++) {
			const char *p = *pattern;
			int plen = strlen(p);
