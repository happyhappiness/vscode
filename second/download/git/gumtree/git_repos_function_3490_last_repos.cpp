int safe_create_reflog(const char *refname, int force_create,
		       struct strbuf *err)
{
	return refs_create_reflog(get_main_ref_store(), refname,
				  force_create, err);
}