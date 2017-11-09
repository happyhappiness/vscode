int delete_refs(const char *msg, struct string_list *refnames,
		unsigned int flags)
{
	return refs_delete_refs(get_main_ref_store(), msg, refnames, flags);
}