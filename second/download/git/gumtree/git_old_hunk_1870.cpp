}

/* This function should make sure errno is meaningful on error */
static struct ref_lock *verify_lock(struct ref_lock *lock,
	const unsigned char *old_sha1, int mustexist)
{
	if (read_ref_full(lock->ref_name, lock->old_sha1, mustexist, NULL)) {
		int save_errno = errno;
		error("Can't verify ref %s", lock->ref_name);
		unlock_ref(lock);
		errno = save_errno;
		return NULL;
	}
