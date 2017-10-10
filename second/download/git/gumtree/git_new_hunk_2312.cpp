		rollback_lock_file(lock->lk);
	free(lock->ref_name);
	free(lock->orig_ref_name);
	free(lock);
}

/*
 * Verify that the reference locked by lock has the value old_sha1.
 * Fail if the reference doesn't exist and mustexist is set. Return 0
 * on success. On error, write an error message to err, set errno, and
 * return a negative value.
 */
static int verify_lock(struct ref_lock *lock,
		       const unsigned char *old_sha1, int mustexist,
		       struct strbuf *err)
{
	assert(err);

	if (read_ref_full(lock->ref_name,
			  mustexist ? RESOLVE_REF_READING : 0,
			  lock->old_oid.hash, NULL)) {
		int save_errno = errno;
		strbuf_addf(err, "can't verify ref %s", lock->ref_name);
		errno = save_errno;
		return -1;
	}
	if (hashcmp(lock->old_oid.hash, old_sha1)) {
		strbuf_addf(err, "ref %s is at %s but expected %s",
			    lock->ref_name,
			    sha1_to_hex(lock->old_oid.hash),
			    sha1_to_hex(old_sha1));
		errno = EBUSY;
		return -1;
	}
	return 0;
}

static int remove_empty_directories(const char *file)
{
	/* we want to create a file but there is a directory there;
	 * if that is an empty directory (or a directory that contains
