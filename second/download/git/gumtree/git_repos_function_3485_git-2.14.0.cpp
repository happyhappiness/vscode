int rename_ref(const char *oldref, const char *newref, const char *logmsg)
{
	return refs_rename_ref(get_main_ref_store(), oldref, newref, logmsg);
}