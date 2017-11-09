int peel_ref(const char *refname, unsigned char *sha1)
{
	return refs_peel_ref(get_main_ref_store(), refname, sha1);
}