struct ref_iterator *files_ref_iterator_begin(
		const char *submodule,
		const char *prefix, unsigned int flags)
{
	struct ref_cache *refs = get_ref_cache(submodule);
	struct ref_dir *loose_dir, *packed_dir;
	struct ref_iterator *loose_iter, *packed_iter;
	struct files_ref_iterator *iter;
	struct ref_iterator *ref_iterator;

	if (!refs)
		return empty_ref_iterator_begin();

	if (ref_paranoia < 0)
		ref_paranoia = git_env_bool("GIT_REF_PARANOIA", 0);
	if (ref_paranoia)
		flags |= DO_FOR_EACH_INCLUDE_BROKEN;

	iter = xcalloc(1, sizeof(*iter));
	ref_iterator = &iter->base;
	base_ref_iterator_init(ref_iterator, &files_ref_iterator_vtable);

	/*
	 * We must make sure that all loose refs are read before
	 * accessing the packed-refs file; this avoids a race
	 * condition if loose refs are migrated to the packed-refs
	 * file by a simultaneous process, but our in-memory view is
	 * from before the migration. We ensure this as follows:
	 * First, we call prime_ref_dir(), which pre-reads the loose
	 * references for the subtree into the cache. (If they've
	 * already been read, that's OK; we only need to guarantee
	 * that they're read before the packed refs, not *how much*
	 * before.) After that, we call get_packed_ref_cache(), which
	 * internally checks whether the packed-ref cache is up to
	 * date with what is on disk, and re-reads it if not.
	 */

	loose_dir = get_loose_refs(refs);

	if (prefix && *prefix)
		loose_dir = find_containing_dir(loose_dir, prefix, 0);

	if (loose_dir) {
		prime_ref_dir(loose_dir);
		loose_iter = cache_ref_iterator_begin(loose_dir);
	} else {
		/* There's nothing to iterate over. */
		loose_iter = empty_ref_iterator_begin();
	}

	iter->packed_ref_cache = get_packed_ref_cache(refs);
	acquire_packed_ref_cache(iter->packed_ref_cache);
	packed_dir = get_packed_ref_dir(iter->packed_ref_cache);

	if (prefix && *prefix)
		packed_dir = find_containing_dir(packed_dir, prefix, 0);

	if (packed_dir) {
		packed_iter = cache_ref_iterator_begin(packed_dir);
	} else {
		/* There's nothing to iterate over. */
		packed_iter = empty_ref_iterator_begin();
	}

	iter->iter0 = overlay_ref_iterator_begin(loose_iter, packed_iter);
	iter->flags = flags;

	return ref_iterator;
}