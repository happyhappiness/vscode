int delete_ref(const char *refname, const unsigned char *sha1, int delopt)
{
	struct ref_lock *lock;
	int ret = 0, flag = 0;

	lock = lock_ref_sha1_basic(refname, sha1, delopt, &flag);
	if (!lock)
		return 1;
	ret |= delete_ref_loose(lock, flag);

	/* removing the loose one could have resurrected an earlier
	 * packed one.  Also, if it was not loose we need to repack
	 * without it.
	 */
	ret |= repack_without_ref(lock->ref_name);

	unlink_or_warn(git_path("logs/%s", lock->ref_name));
	clear_loose_ref_cache(&ref_cache);
	unlock_ref(lock);
	return ret;
}