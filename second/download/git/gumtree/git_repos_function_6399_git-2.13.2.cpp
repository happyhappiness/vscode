struct ref_cache *create_ref_cache(struct ref_store *refs,
				   fill_ref_dir_fn *fill_ref_dir)
{
	struct ref_cache *ret = xcalloc(1, sizeof(*ret));

	ret->ref_store = refs;
	ret->fill_ref_dir = fill_ref_dir;
	ret->root = create_dir_entry(ret, "", 0, 1);
	return ret;
}