int refs_delete_refs(struct ref_store *refs, const char *msg,
		     struct string_list *refnames, unsigned int flags)
{
	return refs->be->delete_refs(refs, msg, refnames, flags);
}