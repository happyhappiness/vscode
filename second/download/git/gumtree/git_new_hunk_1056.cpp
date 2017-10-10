 * and return a nonzero value
 */
static int commit_packed_refs(struct files_ref_store *refs)
{
	struct packed_ref_cache *packed_ref_cache =
		get_packed_ref_cache(refs);
	int ok, error = 0;
	int save_errno = 0;
	FILE *out;
	struct ref_iterator *iter;

	files_assert_main_repository(refs, "commit_packed_refs");

	if (!packed_ref_cache->lock)
		die("internal error: packed-refs not locked");

	out = fdopen_lock_file(packed_ref_cache->lock, "w");
	if (!out)
		die_errno("unable to fdopen packed-refs descriptor");

	fprintf_or_die(out, "%s", PACKED_REFS_HEADER);

	iter = cache_ref_iterator_begin(packed_ref_cache->cache, NULL, 0);
	while ((ok = ref_iterator_advance(iter)) == ITER_OK) {
		struct object_id peeled;
		int peel_error = ref_iterator_peel(iter, &peeled);

		write_packed_entry(out, iter->refname, iter->oid->hash,
				   peel_error ? NULL : peeled.hash);
	}

	if (ok != ITER_DONE)
		die("error while iterating over references");

	if (commit_lock_file(packed_ref_cache->lock)) {
		save_errno = errno;
		error = -1;
	}
	packed_ref_cache->lock = NULL;
