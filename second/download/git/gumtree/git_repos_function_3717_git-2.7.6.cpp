struct ref *get_remote_ref(const struct ref *remote_refs, const char *name)
{
	const struct ref *ref = find_ref_by_name_abbrev(remote_refs, name);

	if (!ref)
		return NULL;

	return copy_ref(ref);
}