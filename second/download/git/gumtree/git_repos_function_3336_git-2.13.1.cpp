int create_symref(const char *ref_target, const char *refs_heads_master,
		  const char *logmsg)
{
	return refs_create_symref(get_main_ref_store(), ref_target,
				  refs_heads_master, logmsg);
}