	strbuf_addf(buffer, "%c%d %d\n", 0, it->entry_count, it->subtree_nr);

#if DEBUG
	if (0 <= it->entry_count)
		fprintf(stderr, "cache-tree <%.*s> (%d ent, %d subtree) %s\n",
			pathlen, path, it->entry_count, it->subtree_nr,
			sha1_to_hex(it->sha1));
	else
		fprintf(stderr, "cache-tree <%.*s> (%d subtree) invalid\n",
			pathlen, path, it->subtree_nr);
#endif

	if (0 <= it->entry_count) {
		strbuf_add(buffer, it->sha1, 20);
	}
	for (i = 0; i < it->subtree_nr; i++) {
		struct cache_tree_sub *down = it->down[i];
		if (i) {
			struct cache_tree_sub *prev = it->down[i-1];
			if (subtree_name_cmp(down->name, down->namelen,
