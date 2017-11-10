static int handle_range_1(
	struct index_state *istate,
	int k_start,
	int k_end,
	struct dir_entry *parent,
	struct strbuf *prefix,
	struct lazy_entry *lazy_entries)
{
	int input_prefix_len = prefix->len;
	int k = k_start;

	while (k < k_end) {
		struct cache_entry *ce_k = istate->cache[k];
		const char *name, *slash;

		if (prefix->len && strncmp(ce_k->name, prefix->buf, prefix->len))
			break;

		name = ce_k->name + prefix->len;
		slash = strchr(name, '/');

		if (slash) {
			int len = slash - name;
			int processed;
			struct dir_entry *dir_new;

			strbuf_add(prefix, name, len);
			processed = handle_range_dir(istate, k, k_end, parent, prefix, lazy_entries, &dir_new);
			if (processed) {
				k += processed;
				strbuf_setlen(prefix, input_prefix_len);
				continue;
			}

			strbuf_addch(prefix, '/');
			processed = handle_range_1(istate, k, k_end, dir_new, prefix, lazy_entries);
			k += processed;
			strbuf_setlen(prefix, input_prefix_len);
			continue;
		}

		/*
		 * It is too expensive to take a lock to insert "ce_k"
		 * into "istate->name_hash" and increment the ref-count
		 * on the "parent" dir.  So we defer actually updating
		 * permanent data structures until phase 2 (where we
		 * can change the locking requirements) and simply
		 * accumulate our current results into the lazy_entries
		 * data array).
		 *
		 * We do not need to lock the lazy_entries array because
		 * we have exclusive access to the cells in the range
		 * [k_start,k_end) that this thread was given.
		 */
		lazy_entries[k].dir = parent;
		if (parent) {
			lazy_entries[k].hash_name = memihash_cont(
				parent->ent.hash,
				ce_k->name + parent->namelen,
				ce_namelen(ce_k) - parent->namelen);
			lazy_entries[k].hash_dir = parent->ent.hash;
		} else {
			lazy_entries[k].hash_name = memihash(ce_k->name, ce_namelen(ce_k));
		}

		k++;
	}

	return k - k_start;
}