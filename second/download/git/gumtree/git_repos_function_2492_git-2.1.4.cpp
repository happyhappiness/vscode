static int repack_without_ref(const char *refname)
{
	return repack_without_refs(&refname, 1, NULL);
}