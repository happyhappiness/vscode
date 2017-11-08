static int verify_lock(struct ref_store *ref_store, struct ref_lock *lock,
		       const unsigned char *old_sha1, int mustexist,
		       struct strbuf *err)
{
	assert(err);

	if (refs_read_ref_full(ref_store, lock->ref_name,
			       mustexist ? RESOLVE_REF_READING : 0,
			       lock->old_oid.hash, NULL)) {
		if (old_sha1) {
			int save_errno = errno;
			strbuf_addf(err, "can't verify ref '%s'", lock->ref_name);
			errno = save_errno;
			return -1;
		} else {
			oidclr(&lock->old_oid);
			return 0;
		}
	}
	if (old_sha1 && hashcmp(lock->old_oid.hash, old_sha1)) {
		strbuf_addf(err, "ref '%s' is at %s but expected %s",
			    lock->ref_name,
			    oid_to_hex(&lock->old_oid),
			    sha1_to_hex(old_sha1));
		errno = EBUSY;
		return -1;
	}
	return 0;
}