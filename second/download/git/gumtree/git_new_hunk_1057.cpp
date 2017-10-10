 */
static void rollback_packed_refs(struct files_ref_store *refs)
{
	struct packed_ref_cache *packed_ref_cache =
		get_packed_ref_cache(refs);

	files_assert_main_repository(refs, "rollback_packed_refs");

	if (!packed_ref_cache->lock)
		die("internal error: packed-refs not locked");
	rollback_lock_file(packed_ref_cache->lock);
	packed_ref_cache->lock = NULL;
	release_packed_ref_cache(packed_ref_cache);
