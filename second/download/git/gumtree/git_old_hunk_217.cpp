	packed_ref_cache->lock = &packlock;
	/* Increment the reference count to prevent it from being freed: */
	acquire_packed_ref_cache(packed_ref_cache);
	return 0;
}

int commit_packed_refs(void)
{
	struct packed_ref_cache *packed_ref_cache =
		get_packed_ref_cache(&ref_cache);
	int error = 0;

	if (!packed_ref_cache->lock)
		die("internal error: packed-refs not locked");
	write_or_die(packed_ref_cache->lock->fd,
		     PACKED_REFS_HEADER, strlen(PACKED_REFS_HEADER));

	do_for_each_entry_in_dir(get_packed_ref_dir(packed_ref_cache),
				 0, write_packed_entry_fn,
				 &packed_ref_cache->lock->fd);
	if (commit_lock_file(packed_ref_cache->lock))
		error = -1;
	packed_ref_cache->lock = NULL;
	release_packed_ref_cache(packed_ref_cache);
	return error;
}

void rollback_packed_refs(void)
{
	struct packed_ref_cache *packed_ref_cache =
