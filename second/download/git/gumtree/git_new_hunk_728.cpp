	if ((flags & PATHSPEC_PREFER_CWD) &&
	    (flags & PATHSPEC_PREFER_FULL))
		die("BUG: PATHSPEC_PREFER_CWD and PATHSPEC_PREFER_FULL are incompatible");

	/* No arguments with prefix -> prefix pathspec */
	if (!entry) {
		if (flags & PATHSPEC_PREFER_FULL)
			return;

		if (!(flags & PATHSPEC_PREFER_CWD))
			die("BUG: PATHSPEC_PREFER_CWD requires arguments");

		pathspec->items = item = xcalloc(1, sizeof(*item));
		item->match = xstrdup(prefix);
		item->original = xstrdup(prefix);
		item->nowildcard_len = item->len = strlen(prefix);
		item->prefix = item->len;
		pathspec->nr = 1;
		return;
	}

	n = 0;
	warn_empty_string = 1;
	while (argv[n]) {
