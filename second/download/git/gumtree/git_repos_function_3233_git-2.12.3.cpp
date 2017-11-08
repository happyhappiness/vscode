int create_symref(const char *ref_target, const char *refs_heads_master,
		  const char *logmsg)
{
	struct ref_store *refs = get_ref_store(NULL);

	return refs->be->create_symref(refs, ref_target, refs_heads_master,
				       logmsg);
}