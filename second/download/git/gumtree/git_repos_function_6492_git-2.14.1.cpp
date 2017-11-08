static int cache_ref_iterator_advance(struct ref_iterator *ref_iterator)
{
	struct cache_ref_iterator *iter =
		(struct cache_ref_iterator *)ref_iterator;

	while (1) {
		struct cache_ref_iterator_level *level =
			&iter->levels[iter->levels_nr - 1];
		struct ref_dir *dir = level->dir;
		struct ref_entry *entry;
		enum prefix_state entry_prefix_state;

		if (level->index == -1)
			sort_ref_dir(dir);

		if (++level->index == level->dir->nr) {
			/* This level is exhausted; pop up a level */
			if (--iter->levels_nr == 0)
				return ref_iterator_abort(ref_iterator);

			continue;
		}

		entry = dir->entries[level->index];

		if (level->prefix_state == PREFIX_WITHIN_DIR) {
			entry_prefix_state = overlaps_prefix(entry->name, iter->prefix);
			if (entry_prefix_state == PREFIX_EXCLUDES_DIR)
				continue;
		} else {
			entry_prefix_state = level->prefix_state;
		}

		if (entry->flag & REF_DIR) {
			/* push down a level */
			ALLOC_GROW(iter->levels, iter->levels_nr + 1,
				   iter->levels_alloc);

			level = &iter->levels[iter->levels_nr++];
			level->dir = get_ref_dir(entry);
			level->prefix_state = entry_prefix_state;
			level->index = -1;
		} else {
			iter->base.refname = entry->name;
			iter->base.oid = &entry->u.value.oid;
			iter->base.flags = entry->flag;
			return ITER_OK;
		}
	}
}