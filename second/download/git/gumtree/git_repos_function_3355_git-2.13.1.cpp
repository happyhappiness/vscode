int delete_refs(struct string_list *refnames, unsigned int flags)
{
	return refs_delete_refs(get_main_ref_store(), refnames, flags);
}