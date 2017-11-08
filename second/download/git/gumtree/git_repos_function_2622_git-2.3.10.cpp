struct ref_lock *lock_any_ref_for_update(const char *refname,
					 const unsigned char *old_sha1,
					 int flags, int *type_p)
{
	return lock_ref_sha1_basic(refname, old_sha1, NULL, flags, type_p);
}