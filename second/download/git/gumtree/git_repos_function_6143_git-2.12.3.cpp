static struct ref_dir *get_packed_refs(struct files_ref_store *refs)
{
	return get_packed_ref_dir(get_packed_ref_cache(refs));
}