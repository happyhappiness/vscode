	packed_ref_cache->lock = NULL;
	release_packed_ref_cache(packed_ref_cache);
	errno = save_errno;
	return error;
}

void rollback_packed_refs(void)
{
	struct packed_ref_cache *packed_ref_cache =
		get_packed_ref_cache(&ref_cache);

	if (!packed_ref_cache->lock)
		die("internal error: packed-refs not locked");
