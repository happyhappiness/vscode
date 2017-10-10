{
	struct packed_ref_cache *packed_ref_cache =
		get_packed_ref_cache(refs);

	files_assert_main_repository(refs, "rollback_packed_refs");

	if (!is_lock_file_locked(&refs->packed_refs_lock))
		die("BUG: packed-refs not locked");
	rollback_lock_file(&refs->packed_refs_lock);
	release_packed_ref_cache(packed_ref_cache);
	clear_packed_ref_cache(refs);
}

struct ref_to_prune {
	struct ref_to_prune *next;
