static void write_one(struct strbuf *buffer, struct cache_tree *it,
                      const char *path, int pathlen)
{
	int i;

	/* One "cache-tree" entry consists of the following:
	 * path (NUL terminated)
	 * entry_count, subtree_nr ("%d %d\n")
	 * tree-sha1 (missing if invalid)
	 * subtree_nr "cache-tree" entries for subtrees.
	 */
	strbuf_grow(buffer, pathlen + 100);
	strbuf_add(buffer, path, pathlen);
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
					     prev->name, prev->namelen) <= 0)
				die("fatal - unsorted cache subtree");
		}
		write_one(buffer, down->cache_tree, down->name, down->namelen);
	}
}