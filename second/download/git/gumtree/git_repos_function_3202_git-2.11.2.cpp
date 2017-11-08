int delete_reflog(const char *refname)
{
	struct ref_store *refs = get_ref_store(NULL);

	return refs->be->delete_reflog(refs, refname);
}