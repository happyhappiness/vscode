void parse_pathspec(struct pathspec *pathspec,
		    unsigned magic_mask, unsigned flags,
		    const char *prefix, const char **argv)
{
	struct pathspec_item *item;
	const char *entry = argv ? *argv : NULL;
	int i, n, prefixlen, warn_empty_string, nr_exclude = 0;

	memset(pathspec, 0, sizeof(*pathspec));

	if (flags & PATHSPEC_MAXDEPTH_VALID)
		pathspec->magic |= PATHSPEC_MAXDEPTH;

	/* No arguments, no prefix -> no pathspec */
	if (!entry && !prefix)
		return;

	if ((flags & PATHSPEC_PREFER_CWD) &&
	    (flags & PATHSPEC_PREFER_FULL))
		die("BUG: PATHSPEC_PREFER_CWD and PATHSPEC_PREFER_FULL are incompatible");

	/* No arguments with prefix -> prefix pathspec */
	if (!entry) {
		static const char *raw[2];

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
		pathspec->nr = 1;
		pathspec->_raw = raw;
		return;
	}

	n = 0;
	warn_empty_string = 1;
	while (argv[n]) {
		if (*argv[n] == '\0' && warn_empty_string) {
			warning(_("empty strings as pathspecs will be made invalid in upcoming releases. "
				  "please use . instead if you meant to match all paths"));
			warn_empty_string = 0;
		}
		n++;
	}

	pathspec->nr = n;
	ALLOC_ARRAY(pathspec->items, n);
	item = pathspec->items;
	pathspec->_raw = argv;
	prefixlen = prefix ? strlen(prefix) : 0;

	for (i = 0; i < n; i++) {
		unsigned short_magic;
		entry = argv[i];

		item[i].magic = prefix_pathspec(item + i, &short_magic,
						argv + i, flags,
						prefix, prefixlen, entry);
		if ((flags & PATHSPEC_LITERAL_PATH) &&
		    !(magic_mask & PATHSPEC_LITERAL))
			item[i].magic |= PATHSPEC_LITERAL;
		if (item[i].magic & PATHSPEC_EXCLUDE)
			nr_exclude++;
		if (item[i].magic & magic_mask)
			unsupported_magic(entry,
					  item[i].magic & magic_mask,
					  short_magic);

		if ((flags & PATHSPEC_SYMLINK_LEADING_PATH) &&
		    has_symlink_leading_path(item[i].match, item[i].len)) {
			die(_("pathspec '%s' is beyond a symbolic link"), entry);
		}

		if (item[i].nowildcard_len < item[i].len)
			pathspec->has_wildcard = 1;
		pathspec->magic |= item[i].magic;
	}

	if (nr_exclude == n)
		die(_("There is nothing to exclude from by :(exclude) patterns.\n"
		      "Perhaps you forgot to add either ':/' or '.' ?"));


	if (pathspec->magic & PATHSPEC_MAXDEPTH) {
		if (flags & PATHSPEC_KEEP_ORDER)
			die("BUG: PATHSPEC_MAXDEPTH_VALID and PATHSPEC_KEEP_ORDER are incompatible");
		QSORT(pathspec->items, pathspec->nr, pathspec_item_cmp);
	}
}