static int lock_packed_refs(struct files_ref_store *refs, int flags)
{
	static int timeout_configured = 0;
	static int timeout_value = 1000;
	struct packed_ref_cache *packed_ref_cache;

	files_assert_main_repository(refs, "lock_packed_refs");

	if (!timeout_configured) {
		git_config_get_int("core.packedrefstimeout", &timeout_value);
		timeout_configured = 1;
	}

	if (hold_lock_file_for_update_timeout(
			    &refs->packed_refs_lock, files_packed_refs_path(refs),
			    flags, timeout_value) < 0)
		return -1;

	/*
	 * Now that we hold the `packed-refs` lock, make sure that our
	 * cache matches the current version of the file. Normally
	 * `get_packed_ref_cache()` does that for us, but that
	 * function assumes that when the file is locked, any existing
	 * cache is still valid. We've just locked the file, but it
	 * might have changed the moment *before* we locked it.
	 */
	validate_packed_ref_cache(refs);

	packed_ref_cache = get_packed_ref_cache(refs);
	/* Increment the reference count to prevent it from being freed: */
	acquire_packed_ref_cache(packed_ref_cache);
	return 0;
}