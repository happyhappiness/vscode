static struct ref_iterator *files_ref_iterator_begin(
		struct ref_store *ref_store,
		const char *prefix, unsigned int flags)
{
	struct files_ref_store *refs;
	struct ref_iterator *loose_iter, *packed_iter;
	struct files_ref_iterator *iter;
	struct ref_iterator *ref_iterator;
	unsigned int required_flags = REF_STORE_READ;

	if (!(flags & DO_FOR_EACH_INCLUDE_BROKEN))
		required_flags |= REF_STORE_ODB;

	refs = files_downcast(ref_store, required_flags, "ref_iterator_begin");

	iter = xcalloc(1, sizeof(*iter));
	ref_iterator = &iter->base;
	base_ref_iterator_init(ref_iterator, &files_ref_iterator_vtable);

	/*
	 * We must make sure that all loose refs are read before
	 * accessing the packed-refs file; this avoids a race
	 * condition if loose refs are migrated to the packed-refs
	 * file by a simultaneous process, but our in-memory view is
	 * from before the migration. We ensure this as follows:
	 * First, we call start the loose refs iteration with its
	 * `prime_ref` argument set to true. This causes the loose
	 * references in the subtree to be pre-read into the cache.
	 * (If they've already been read, that's OK; we only need to
	 * guarantee that they're read before the packed refs, not
	 * *how much* before.) After that, we call
	 * get_packed_ref_cache(), which internally checks whether the
	 * packed-ref cache is up to date with what is on disk, and
	 * re-reads it if not.
	 */

	loose_iter = cache_ref_iterator_begin(get_loose_ref_cache(refs),
					      prefix, 1);

	iter->packed_ref_cache = get_packed_ref_cache(refs);
	acquire_packed_ref_cache(iter->packed_ref_cache);
	packed_iter = cache_ref_iterator_begin(iter->packed_ref_cache->cache,
					       prefix, 0);

	iter->iter0 = overlay_ref_iterator_begin(loose_iter, packed_iter);
	iter->flags = flags;

	return ref_iterator;
}