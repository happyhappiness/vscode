int delete_ref(const char *msg, const char *refname,
	       const unsigned char *old_sha1, unsigned int flags)
{
	return refs_delete_ref(get_main_ref_store(), msg, refname,
			       old_sha1, flags);
}