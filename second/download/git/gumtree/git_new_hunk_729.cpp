		n++;
	}

	pathspec->nr = n;
	ALLOC_ARRAY(pathspec->items, n);
	item = pathspec->items;
	prefixlen = prefix ? strlen(prefix) : 0;

	for (i = 0; i < n; i++) {
		entry = argv[i];

		init_pathspec_item(item + i, flags, prefix, prefixlen, entry);

		if (item[i].magic & PATHSPEC_EXCLUDE)
			nr_exclude++;
		if (item[i].magic & magic_mask)
			unsupported_magic(entry, item[i].magic & magic_mask);

		if ((flags & PATHSPEC_SYMLINK_LEADING_PATH) &&
		    has_symlink_leading_path(item[i].match, item[i].len)) {
			die(_("pathspec '%s' is beyond a symbolic link"), entry);
		}

