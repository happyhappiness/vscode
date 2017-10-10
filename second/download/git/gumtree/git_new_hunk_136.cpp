
#if DEBUG
	fprintf(stderr, "cache-tree invalidate <%s>\n", path);
#endif

	if (!it)
		return 0;
	slash = strchrnul(path, '/');
	namelen = slash - path;
	it->entry_count = -1;
	if (!*slash) {
		int pos;
		pos = subtree_pos(it, path, namelen);
