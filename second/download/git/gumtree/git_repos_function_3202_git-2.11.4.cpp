int safe_create_reflog(const char *refname, int force_create,
		       struct strbuf *err)
{
	struct ref_store *refs = get_ref_store(NULL);

	return refs->be->create_reflog(refs, refname, force_create, err);
}