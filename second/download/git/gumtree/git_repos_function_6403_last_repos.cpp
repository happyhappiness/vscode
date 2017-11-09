static struct ref_entry *get_packed_ref(struct files_ref_store *refs,
					const char *refname)
{
	return find_ref_entry(get_packed_refs(refs), refname);
}