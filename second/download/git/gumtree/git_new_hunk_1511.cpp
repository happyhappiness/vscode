		die("BUG: unknown ref type %d of ref %s",
		    ref_type(refname), refname);
	}
}

/*
 * Check that the packed refs cache (if any) still reflects the
 * contents of the file. If not, clear the cache.
 */
static void validate_packed_ref_cache(struct files_ref_store *refs)
{
	if (refs->packed &&
	    !stat_validity_check(&refs->packed->validity,
				 files_packed_refs_path(refs)))
		clear_packed_ref_cache(refs);
}

/*
 * Get the packed_ref_cache for the specified files_ref_store,
 * creating and populating it if it hasn't been read before or if the
 * file has been changed (according to its `validity` field) since it
 * was last read. On the other hand, if we hold the lock, then assume
 * that the file hasn't been changed out from under us, so skip the
 * extra `stat()` call in `stat_validity_check()`.
 */
static struct packed_ref_cache *get_packed_ref_cache(struct files_ref_store *refs)
{
	const char *packed_refs_file = files_packed_refs_path(refs);

	if (!is_lock_file_locked(&refs->packed_refs_lock))
		validate_packed_ref_cache(refs);

	if (!refs->packed)
		refs->packed = read_packed_refs(packed_refs_file);

	return refs->packed;
}

static struct ref_dir *get_packed_ref_dir(struct packed_ref_cache *packed_ref_cache)
{
	return get_ref_dir(packed_ref_cache->cache->root);
