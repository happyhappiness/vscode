static int traverse_trees_recursive(int n, unsigned long dirmask,
				    unsigned long df_conflicts,
				    struct name_entry *names,
				    struct traverse_info *info)
{
	int i, ret, bottom;
	struct tree_desc t[MAX_UNPACK_TREES];
	void *buf[MAX_UNPACK_TREES];
	struct traverse_info newinfo;
	struct name_entry *p;

	p = names;
	while (!p->mode)
		p++;

	newinfo = *info;
	newinfo.prev = info;
	newinfo.pathspec = info->pathspec;
	newinfo.name = *p;
	newinfo.pathlen += tree_entry_len(p) + 1;
	newinfo.df_conflicts |= df_conflicts;

	for (i = 0; i < n; i++, dirmask >>= 1) {
		const unsigned char *sha1 = NULL;
		if (dirmask & 1)
			sha1 = names[i].oid->hash;
		buf[i] = fill_tree_descriptor(t+i, sha1);
	}

	bottom = switch_cache_bottom(&newinfo);
	ret = traverse_trees(n, t, &newinfo);
	restore_cache_bottom(&newinfo, bottom);

	for (i = 0; i < n; i++)
		free(buf[i]);

	return ret;
}