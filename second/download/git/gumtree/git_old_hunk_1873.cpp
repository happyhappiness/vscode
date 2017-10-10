int commit_packed_refs(void)
{
	struct packed_ref_cache *packed_ref_cache =
		get_packed_ref_cache(&ref_cache);
	int error = 0;
	int save_errno = 0;

	if (!packed_ref_cache->lock)
		die("internal error: packed-refs not locked");
	write_or_die(packed_ref_cache->lock->fd,
		     PACKED_REFS_HEADER, strlen(PACKED_REFS_HEADER));

	do_for_each_entry_in_dir(get_packed_ref_dir(packed_ref_cache),
				 0, write_packed_entry_fn,
				 &packed_ref_cache->lock->fd);
	if (commit_lock_file(packed_ref_cache->lock)) {
		save_errno = errno;
		error = -1;
	}
	packed_ref_cache->lock = NULL;
	release_packed_ref_cache(packed_ref_cache);
