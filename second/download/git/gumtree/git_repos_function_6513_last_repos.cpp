struct ref_iterator *cache_ref_iterator_begin(struct ref_cache *cache,
					      const char *prefix,
					      int prime_dir)
{
	struct ref_dir *dir;
	struct cache_ref_iterator *iter;
	struct ref_iterator *ref_iterator;
	struct cache_ref_iterator_level *level;

	dir = get_ref_dir(cache->root);
	if (prefix && *prefix)
		dir = find_containing_dir(dir, prefix, 0);
	if (!dir)
		/* There's nothing to iterate over. */
		return empty_ref_iterator_begin();

	if (prime_dir)
		prime_ref_dir(dir, prefix);

	iter = xcalloc(1, sizeof(*iter));
	ref_iterator = &iter->base;
	base_ref_iterator_init(ref_iterator, &cache_ref_iterator_vtable);
	ALLOC_GROW(iter->levels, 10, iter->levels_alloc);

	iter->levels_nr = 1;
	level = &iter->levels[0];
	level->index = -1;
	level->dir = dir;

	if (prefix && *prefix) {
		iter->prefix = xstrdup(prefix);
		level->prefix_state = PREFIX_WITHIN_DIR;
	} else {
		level->prefix_state = PREFIX_CONTAINS_DIR;
	}

	return ref_iterator;
}