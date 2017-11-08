int reflog_exists(const char *refname)
{
	return refs_reflog_exists(get_main_ref_store(), refname);
}