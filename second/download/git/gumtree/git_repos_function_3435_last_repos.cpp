int update_ref(const char *msg, const char *refname,
	       const unsigned char *new_sha1,
	       const unsigned char *old_sha1,
	       unsigned int flags, enum action_on_err onerr)
{
	return refs_update_ref(get_main_ref_store(), msg, refname, new_sha1,
			       old_sha1, flags, onerr);
}