static struct ref_lock *lock_ref_sha1_basic(struct files_ref_store *refs,
					    const char *refname,
					    const unsigned char *old_sha1,
					    const struct string_list *extras,
					    const struct string_list *skip,
					    unsigned int flags, int *type,
					    struct strbuf *err)
{
	struct strbuf ref_file = STRBUF_INIT;
	struct ref_lock *lock;
	int last_errno = 0;
	int mustexist = (old_sha1 && !is_null_sha1(old_sha1));
	int resolve_flags = RESOLVE_REF_NO_RECURSE;
	int resolved;

	files_assert_main_repository(refs, "lock_ref_sha1_basic");
	assert(err);

	lock = xcalloc(1, sizeof(struct ref_lock));

	if (mustexist)
		resolve_flags |= RESOLVE_REF_READING;
	if (flags & REF_DELETING)
		resolve_flags |= RESOLVE_REF_ALLOW_BAD_NAME;

	files_ref_path(refs, &ref_file, refname);
	resolved = !!refs_resolve_ref_unsafe(&refs->base,
					     refname, resolve_flags,
					     lock->old_oid.hash, type);
	if (!resolved && errno == EISDIR) {
		/*
		 * we are trying to lock foo but we used to
		 * have foo/bar which now does not exist;
		 * it is normal for the empty directory 'foo'
		 * to remain.
		 */
		if (remove_empty_directories(&ref_file)) {
			last_errno = errno;
			if (!refs_verify_refname_available(
					    &refs->base,
					    refname, extras, skip, err))
				strbuf_addf(err, "there are still refs under '%s'",
					    refname);
			goto error_return;
		}
		resolved = !!refs_resolve_ref_unsafe(&refs->base,
						     refname, resolve_flags,
						     lock->old_oid.hash, type);
	}
	if (!resolved) {
		last_errno = errno;
		if (last_errno != ENOTDIR ||
		    !refs_verify_refname_available(&refs->base, refname,
						   extras, skip, err))
			strbuf_addf(err, "unable to resolve reference '%s': %s",
				    refname, strerror(last_errno));

		goto error_return;
	}

	/*
	 * If the ref did not exist and we are creating it, make sure
	 * there is no existing packed ref whose name begins with our
	 * refname, nor a packed ref whose name is a proper prefix of
	 * our refname.
	 */
	if (is_null_oid(&lock->old_oid) &&
	    refs_verify_refname_available(&refs->base, refname,
					  extras, skip, err)) {
		last_errno = ENOTDIR;
		goto error_return;
	}

	lock->lk = xcalloc(1, sizeof(struct lock_file));

	lock->ref_name = xstrdup(refname);

	if (raceproof_create_file(ref_file.buf, create_reflock, lock->lk)) {
		last_errno = errno;
		unable_to_lock_message(ref_file.buf, errno, err);
		goto error_return;
	}

	if (verify_lock(&refs->base, lock, old_sha1, mustexist, err)) {
		last_errno = errno;
		goto error_return;
	}
	goto out;

 error_return:
	unlock_ref(lock);
	lock = NULL;

 out:
	strbuf_release(&ref_file);
	errno = last_errno;
	return lock;
}