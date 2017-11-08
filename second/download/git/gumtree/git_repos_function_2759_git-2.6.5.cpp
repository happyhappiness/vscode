static struct ref_entry *get_packed_ref(const char *refname)
{
	return find_ref(get_packed_refs(&ref_cache), refname);
}