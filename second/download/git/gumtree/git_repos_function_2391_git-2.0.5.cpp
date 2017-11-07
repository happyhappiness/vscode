static struct ref_cache *get_ref_cache(const char *submodule)
{
	struct ref_cache *refs;

	if (!submodule || !*submodule)
		return &ref_cache;

	for (refs = submodule_ref_caches; refs; refs = refs->next)
		if (!strcmp(submodule, refs->name))
			return refs;

	refs = create_ref_cache(submodule);
	refs->next = submodule_ref_caches;
	submodule_ref_caches = refs;
	return refs;
}