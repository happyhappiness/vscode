	/*
	 * Get the current packed-refs while holding the lock.  If the
	 * packed-refs file has been modified since we last read it,
	 * this will automatically invalidate the cache and re-read
	 * the packed-refs file.
	 */
	packed_ref_cache = get_packed_ref_cache(refs);
	packed_ref_cache->lock = &packlock;
	/* Increment the reference count to prevent it from being freed: */
	acquire_packed_ref_cache(packed_ref_cache);
	return 0;
}

/*
 * Write the current version of the packed refs cache from memory to
 * disk. The packed-refs file must already be locked for writing (see
 * lock_packed_refs()). Return zero on success. On errors, set errno
 * and return a nonzero value
 */
static int commit_packed_refs(struct files_ref_store *refs)
{
	struct packed_ref_cache *packed_ref_cache =
		get_packed_ref_cache(refs);
	int error = 0;
	int save_errno = 0;
	FILE *out;

	assert_main_repository(&refs->base, "commit_packed_refs");

	if (!packed_ref_cache->lock)
		die("internal error: packed-refs not locked");

	out = fdopen_lock_file(packed_ref_cache->lock, "w");
	if (!out)
		die_errno("unable to fdopen packed-refs descriptor");
