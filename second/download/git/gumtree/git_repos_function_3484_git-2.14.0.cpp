int refs_rename_ref(struct ref_store *refs, const char *oldref,
		    const char *newref, const char *logmsg)
{
	return refs->be->rename_ref(refs, oldref, newref, logmsg);
}