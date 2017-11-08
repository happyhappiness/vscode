static struct ref_cache *create_ref_cache(const char *submodule)
{
	struct ref_cache *refs;
	if (!submodule)
		submodule = "";
	FLEX_ALLOC_STR(refs, name, submodule);
	refs->next = submodule_ref_caches;
	submodule_ref_caches = refs;
	return refs;
}