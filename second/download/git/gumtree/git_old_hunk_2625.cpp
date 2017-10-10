
static struct ref_dir *get_packed_refs(struct ref_cache *refs)
{
	return get_packed_ref_dir(get_packed_ref_cache(refs));
}

void add_packed_ref(const char *refname, const unsigned char *sha1)
{
	struct packed_ref_cache *packed_ref_cache =
		get_packed_ref_cache(&ref_cache);

	if (!packed_ref_cache->lock)
		die("internal error: packed refs not locked");
