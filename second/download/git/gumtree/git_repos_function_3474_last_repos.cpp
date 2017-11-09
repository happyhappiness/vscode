int refs_create_symref(struct ref_store *refs,
		       const char *ref_target,
		       const char *refs_heads_master,
		       const char *logmsg)
{
	return refs->be->create_symref(refs, ref_target,
				       refs_heads_master,
				       logmsg);
}