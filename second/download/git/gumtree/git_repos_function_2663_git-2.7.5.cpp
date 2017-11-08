static int unpack_callback(int n, unsigned long mask, unsigned long dirmask, struct name_entry *names, struct traverse_info *info)
{
	struct cache_entry *src[MAX_UNPACK_TREES + 1] = { NULL, };
	struct unpack_trees_options *o = info->data;
	const struct name_entry *p = names;

	/* Find first entry with a real name (we could use "mask" too) */
	while (!p->mode)
		p++;

	if (o->debug_unpack)
		debug_unpack_callback(n, mask, dirmask, names, info);

	/* Are we supposed to look at the index too? */
	if (o->merge) {
		while (1) {
			int cmp;
			struct cache_entry *ce;

			if (o->diff_index_cached)
				ce = next_cache_entry(o);
			else
				ce = find_cache_entry(info, p);

			if (!ce)
				break;
			cmp = compare_entry(ce, info, p);
			if (cmp < 0) {
				if (unpack_index_entry(ce, o) < 0)
					return unpack_failed(o, NULL);
				continue;
			}
			if (!cmp) {
				if (ce_stage(ce)) {
					/*
					 * If we skip unmerged index
					 * entries, we'll skip this
					 * entry *and* the tree
					 * entries associated with it!
					 */
					if (o->skip_unmerged) {
						add_same_unmerged(ce, o);
						return mask;
					}
				}
				src[0] = ce;
			}
			break;
		}
	}

	if (unpack_nondirectories(n, mask, dirmask, src, names, info) < 0)
		return -1;

	if (o->merge && src[0]) {
		if (ce_stage(src[0]))
			mark_ce_used_same_name(src[0], o);
		else
			mark_ce_used(src[0], o);
	}

	/* Now handle any directories.. */
	if (dirmask) {
		/* special case: "diff-index --cached" looking at a tree */
		if (o->diff_index_cached &&
		    n == 1 && dirmask == 1 && S_ISDIR(names->mode)) {
			int matches;
			matches = cache_tree_matches_traversal(o->src_index->cache_tree,
							       names, info);
			/*
			 * Everything under the name matches; skip the
			 * entire hierarchy.  diff_index_cached codepath
			 * special cases D/F conflicts in such a way that
			 * it does not do any look-ahead, so this is safe.
			 */
			if (matches) {
				o->cache_bottom += matches;
				return mask;
			}
		}

		if (traverse_trees_recursive(n, dirmask, mask & ~dirmask,
					     names, info) < 0)
			return -1;
		return mask;
	}

	return mask;
}