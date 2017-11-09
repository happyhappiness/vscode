int delete_reflog(const char *refname)
{
	return refs_delete_reflog(get_main_ref_store(), refname);
}