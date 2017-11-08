static int find_cache_pos(struct traverse_info *info,
			  const struct name_entry *p)
{
	int pos;
	struct unpack_trees_options *o = info->data;
	struct index_state *index = o->src_index;
	int pfxlen = info->pathlen;
	int p_len = tree_entry_len(p);

	for (pos = o->cache_bottom; pos < index->cache_nr; pos++) {
		const struct cache_entry *ce = index->cache[pos];
		const char *ce_name, *ce_slash;
		int cmp, ce_len;

		if (ce->ce_flags & CE_UNPACKED) {
			/*
			 * cache_bottom entry is already unpacked, so
			 * we can never match it; don't check it
			 * again.
			 */
			if (pos == o->cache_bottom)
				++o->cache_bottom;
			continue;
		}
		if (!ce_in_traverse_path(ce, info))
			continue;
		ce_name = ce->name + pfxlen;
		ce_slash = strchr(ce_name, '/');
		if (ce_slash)
			ce_len = ce_slash - ce_name;
		else
			ce_len = ce_namelen(ce) - pfxlen;
		cmp = name_compare(p->path, p_len, ce_name, ce_len);
		/*
		 * Exact match; if we have a directory we need to
		 * delay returning it.
		 */
		if (!cmp)
			return ce_slash ? -2 - pos : pos;
		if (0 < cmp)
			continue; /* keep looking */
		/*
		 * ce_name sorts after p->path; could it be that we
		 * have files under p->path directory in the index?
		 * E.g.  ce_name == "t-i", and p->path == "t"; we may
		 * have "t/a" in the index.
		 */
		if (p_len < ce_len && !memcmp(ce_name, p->path, p_len) &&
		    ce_name[p_len] < '/')
			continue; /* keep looking */
		break;
	}
	return -1;
}