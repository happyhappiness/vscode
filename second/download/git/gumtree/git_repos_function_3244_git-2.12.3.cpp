int delete_refs(struct string_list *refnames, unsigned int flags)
{
	struct ref_store *refs = get_ref_store(NULL);

	return refs->be->delete_refs(refs, refnames, flags);
}