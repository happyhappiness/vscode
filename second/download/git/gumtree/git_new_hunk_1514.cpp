	int save_errno = 0;
	FILE *out;
	struct ref_iterator *iter;

	files_assert_main_repository(refs, "commit_packed_refs");

	if (!is_lock_file_locked(&refs->packed_refs_lock))
		die("BUG: packed-refs not locked");

	out = fdopen_lock_file(&refs->packed_refs_lock, "w");
	if (!out)
		die_errno("unable to fdopen packed-refs descriptor");

	fprintf_or_die(out, "%s", PACKED_REFS_HEADER);

	iter = cache_ref_iterator_begin(packed_ref_cache->cache, NULL, 0);
