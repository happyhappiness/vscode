		return;
	if (parse_tree_gently(tree, revs->ignore_missing_links) < 0) {
		if (revs->ignore_missing_links)
			return;
		die("bad tree object %s", sha1_to_hex(obj->sha1));
	}

	obj->flags |= SEEN;
	strbuf_addstr(base, name);
	show(obj, base->buf, cb_data);
	if (base->len)
		strbuf_addch(base, '/');

	init_tree_desc(&desc, tree->buffer, tree->size);

	while (tree_entry(&desc, &entry)) {
		if (match != all_entries_interesting) {
			match = tree_entry_interesting(&entry, base, 0,
