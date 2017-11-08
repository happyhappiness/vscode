static struct packed_ref_cache *get_packed_ref_cache(struct files_ref_store *refs)
{
	const char *packed_refs_file = files_packed_refs_path(refs);

	if (!is_lock_file_locked(&refs->packed_refs_lock))
		validate_packed_ref_cache(refs);

	if (!refs->packed)
		refs->packed = read_packed_refs(packed_refs_file);

	return refs->packed;
}