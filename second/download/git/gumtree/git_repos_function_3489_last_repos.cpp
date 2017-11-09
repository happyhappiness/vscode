int refs_create_reflog(struct ref_store *refs, const char *refname,
		       int force_create, struct strbuf *err)
{
	return refs->be->create_reflog(refs, refname, force_create, err);
}