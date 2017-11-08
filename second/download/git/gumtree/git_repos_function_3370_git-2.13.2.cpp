int refs_delete_refs(struct ref_store *refs, struct string_list *refnames,
		     unsigned int flags)
{
	return refs->be->delete_refs(refs, refnames, flags);
}