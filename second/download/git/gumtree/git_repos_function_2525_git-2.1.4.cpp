int update_ref(const char *action, const char *refname,
	       const unsigned char *sha1, const unsigned char *oldval,
	       int flags, enum action_on_err onerr)
{
	struct ref_lock *lock;
	lock = update_ref_lock(refname, oldval, flags, NULL, onerr);
	if (!lock)
		return 1;
	return update_ref_write(action, refname, sha1, lock, NULL, onerr);
}