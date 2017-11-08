int pack_refs(unsigned int flags)
{
	struct ref_store *refs = get_ref_store(NULL);

	return refs->be->pack_refs(refs, flags);
}