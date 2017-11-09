int refs_pack_refs(struct ref_store *refs, unsigned int flags)
{
	return refs->be->pack_refs(refs, flags);
}