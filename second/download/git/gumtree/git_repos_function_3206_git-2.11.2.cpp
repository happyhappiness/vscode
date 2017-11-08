int rename_ref(const char *oldref, const char *newref, const char *logmsg)
{
	struct ref_store *refs = get_ref_store(NULL);

	return refs->be->rename_ref(refs, oldref, newref, logmsg);
}