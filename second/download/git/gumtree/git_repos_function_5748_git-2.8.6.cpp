static struct ref_dir *get_packed_refs(struct ref_cache *refs)
{
	return get_packed_ref_dir(get_packed_ref_cache(refs));
}