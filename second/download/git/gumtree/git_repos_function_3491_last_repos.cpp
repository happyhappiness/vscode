int refs_delete_reflog(struct ref_store *refs, const char *refname)
{
	return refs->be->delete_reflog(refs, refname);
}