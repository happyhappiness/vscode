static struct ref_lock *verify_lock(struct ref_lock *lock,
	const unsigned char *old_sha1, int mustexist)
{
	if (read_ref_full(lock->ref_name,
			  mustexist ? RESOLVE_REF_READING : 0,
			  lock->old_sha1, NULL)) {
		int save_errno = errno;
		error("Can't verify ref %s", lock->ref_name);
		unlock_ref(lock);
		errno = save_errno;
		return NULL;
	}
	if (hashcmp(lock->old_sha1, old_sha1)) {
		error("Ref %s is at %s but expected %s", lock->ref_name,
			sha1_to_hex(lock->old_sha1), sha1_to_hex(old_sha1));
		unlock_ref(lock);
		errno = EBUSY;
		return NULL;
	}
	return lock;
}