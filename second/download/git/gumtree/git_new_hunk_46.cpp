		if (flags & PATHSPEC_PREFER_FULL)
			return;

		if (!(flags & PATHSPEC_PREFER_CWD))
			die("BUG: PATHSPEC_PREFER_CWD requires arguments");

		pathspec->items = item = xcalloc(1, sizeof(*item));
		item->match = prefix;
		item->original = prefix;
		item->nowildcard_len = item->len = strlen(prefix);
		item->prefix = item->len;
		raw[0] = prefix;
		raw[1] = NULL;
