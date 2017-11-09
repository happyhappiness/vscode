static int traverse_trees_recursive(int n, unsigned long dirmask,
				    unsigned long df_conflicts,
				    struct name_entry *names,
				    struct traverse_info *info)
{
	int i, ret, bottom;
	int nr_buf = 0;
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

	/*
	 * Fetch the tree from the ODB for each peer directory in the
	 * n commits.
	 *
	 * For 2- and 3-way traversals, we try to avoid hitting the
	 * ODB twice for the same OID.  This should yield a nice speed
	 * up in checkouts and merges when the commits are similar.
	 *
	 * We don't bother doing the full O(n^2) search for larger n,
	 * because wider traversals don't happen that often and we
	 * avoid the search setup.
	 *
	 * When 2 peer OIDs are the same, we just copy the tree
	 * descriptor data.  This implicitly borrows the buffer
	 * data from the earlier cell.
	 */
	for (i = 0; i < n; i++, dirmask >>= 1) {
		if (i > 0 && are_same_oid(&names[i], &names[i - 1]))
			t[i] = t[i - 1];
		else if (i > 1 && are_same_oid(&names[i], &names[i - 2]))
			t[i] = t[i - 2];
		else {
			const unsigned char *sha1 = NULL;
			if (dirmask & 1)
				sha1 = names[i].oid->hash;
			buf[nr_buf++] = fill_tree_descriptor(t+i, sha1);
		}
	}

	bottom = switch_cache_bottom(&newinfo);
	ret = traverse_trees(n, t, &newinfo);
	restore_cache_bottom(&newinfo, bottom);

	for (i = 0; i < nr_buf; i++)
		free(buf[i]);

	return ret;
}