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

