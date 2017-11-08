static struct ref_cache *create_ref_cache(const char *submodule)
{
	int len;
	struct ref_cache *refs;
	if (!submodule)
		submodule = "";
	len = strlen(submodule) + 1;
	refs = xcalloc(1, sizeof(struct ref_cache) + len);
	memcpy(refs->name, submodule, len);
	return refs;
}