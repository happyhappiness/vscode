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

	fprintf_or_die(out, "%s", PACKED_REFS_HEADER);
	do_for_each_entry_in_dir(get_packed_ref_dir(packed_ref_cache),
				 0, write_packed_entry_fn, out);

	if (commit_lock_file(packed_ref_cache->lock)) {
		save_errno = errno;
		error = -1;
	}
	packed_ref_cache->lock = NULL;
