static struct ref_cache *get_ref_cache(const char *submodule)
{
	struct ref_cache *refs = lookup_ref_cache(submodule);
	if (!refs)
		refs = create_ref_cache(submodule);
	return refs;
}