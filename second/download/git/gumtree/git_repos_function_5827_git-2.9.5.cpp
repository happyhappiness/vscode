static void add_packed_ref(const char *refname, const unsigned char *sha1)
{
	struct packed_ref_cache *packed_ref_cache =
		get_packed_ref_cache(&ref_cache);

	if (!packed_ref_cache->lock)
		die("internal error: packed refs not locked");
	add_ref(get_packed_ref_dir(packed_ref_cache),
		create_ref_entry(refname, sha1, REF_ISPACKED, 1));
}