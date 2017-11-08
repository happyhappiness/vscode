int reflog_exists(const char *refname)
{
	struct ref_store *refs = get_ref_store(NULL);

	return refs->be->reflog_exists(refs, refname);
}