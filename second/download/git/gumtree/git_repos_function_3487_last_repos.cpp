int refs_reflog_exists(struct ref_store *refs, const char *refname)
{
	return refs->be->reflog_exists(refs, refname);
}